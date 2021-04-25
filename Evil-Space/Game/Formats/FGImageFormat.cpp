//
//  FGImageFormat.cpp
//  GImage File Format.
//
//  Created by Kirill Bravichev on 03/17/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FGImageFormat.h"


namespace
{
	static constexpr uint32 GImageFormatSignature{ 0x00006967 };
    static constexpr uint64 BytePerPixel = sizeof(uint32);
    static constexpr uint64 AlphaByteShift = 3;

    static constexpr uint16 Color16BitMask = 0xFFFFui16;
    static constexpr uint32 Color32BitMask = 0xFFFFFFFFui32;

    struct FGImageLayerInfo
    {
        uint32 Offset;
        uint32 Size;
        uint32 Left;
        uint32 Top;
        uint32 Right;
        uint32 Bottom;
        uint32 Reserved[2];
    };

    struct FGImageLayerHeader
    {
        uint32 Size;
        uint32 Width;
        uint32 Height;
        uint8 Reserved[4];
    };

    enum class EFrameType : uint32
    {
        /*
         * One layer, 16 or 32 bit, depends on mask
         */
        OneLayer_DependsOnMask,
        /*
         * One layer, 16 bit RGB optimized
         */
        OneLayer_RGB16,
        /*
         * Three layers:
         * -- 16 bit RGB optimized - body
         * -- 16 bit RGB optimized - outline
         * -- 6 bit Alpha optimized
         */
        ThreeLayers,
        /*
         * Two layers:
         * -- Indexed RGB colors
         * -- Indexed Alpha
        */
        TwoLayers,
        /*
         * One layer, indexed RGBA colors 
         */
        OneLayer_Indexed8,
        /*
         * Delta frame of GAI animation
         */
        DeltaFrame
    };

    struct FGImageFrameHeader
    {
        uint32 Signature;
        uint32 Version;
        uint32 Left;
        uint32 Top;
        uint32 Right;
        uint32 Bottom;
        uint32 RedMask;
        uint32 GreenMask;
        uint32 BlueMask;
        uint32 AlphaMask;
        EFrameType Type;
        uint32 NumberOfLayers;
        uint32 Reserved[4];
    };

    TSharedPtr<ATextureClass> loadFrameType0(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
        int32 BitsPerPixel{ 0 };
        switch (FileHeader.RedMask | FileHeader.GreenMask | FileHeader.BlueMask | FileHeader.AlphaMask)
        {
        case Color16BitMask:
            BitsPerPixel = 16;
            break;
        case Color32BitMask:
            BitsPerPixel = 32;
            break;
        default:
            break;
        }

        if (BitsPerPixel > 0)
        {
            const FGImageLayerInfo& LayerInfo = LayersInfo.front();
            TArray<uint8> Pixels(LayerInfo.Size);

            FileStream.seekg(BaseOffset + LayerInfo.Offset, FileStream.beg);
            FileStream.read(reinterpret_cast<char*>(Pixels.data()), Pixels.size());

            return ATextureClass::Construct(Pixels, LayerInfo.Right, LayerInfo.Bottom, BitsPerPixel, FileHeader.RedMask, FileHeader.GreenMask, FileHeader.BlueMask, FileHeader.AlphaMask);
        }

        LOG_ERROR("Unknown [RGBA]Mask(s)");
        return nullptr;
   }

    void unpackRGB565(std::ifstream& FileStream, TArray<uint8>& Pixels)
    {
        uint32* Row = reinterpret_cast<uint32*>(Pixels.data());

        FGImageLayerHeader LayerHeader;
        FileStream.read(reinterpret_cast<char*>(&LayerHeader), sizeof(FGImageLayerHeader));

        int64 BytesToRead = LayerHeader.Size;

        while (BytesToRead > 0)
        {
            int8 byte = 0;
            FileStream.read(reinterpret_cast<char*>(&byte), sizeof(byte));
            --BytesToRead;

            if (byte < 0 && byte > TNumericLimits<int8>::lowest())   //Pixels data
            {
                uint16 Pixel;
                uint8 ReadCount = byte & 0x7f;
                BytesToRead -= ReadCount * sizeof(Pixel);

                do
                {
                    FileStream.read(reinterpret_cast<char*>(&Pixel), sizeof(Pixel));

                    *Row = APaletteClass::ConvertPixel(Pixel, EPixelFormatType::RGB16, EPixelFormatType::ARGB32);
                    ++Row;

                    --ReadCount;
                } while (ReadCount > 0);
            }
            else if (byte > 0)//Skip some pixels
            {                
                Row += byte;
            }
        }
    }

    TSharedPtr<ATextureClass> loadFrameType1(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
         const FGImageLayerInfo& LayerInfo = LayersInfo.front();
        TArray<uint8> Pixels(static_cast<uint64>(FileHeader.Right) * static_cast<uint64>(FileHeader.Bottom) * BytePerPixel);

        FileStream.seekg(BaseOffset + LayerInfo.Offset, FileStream.beg);
        unpackRGB565(FileStream, Pixels);

        return ATextureClass::Construct(Pixels, LayerInfo.Right, LayerInfo.Bottom, EPixelFormatType::ARGB32);
    }

    void unpackA6(std::ifstream& FileStream, TArray<uint8>& Pixels)
    {
        /* Lookup tables to expand partial bytes to the full 0..255 range */
        static uint8 LookupTable[] = {
            0, 4, 8, 12, 16, 20, 24, 28, 
            32, 36, 40, 44, 48, 52, 56, 60, 
            64, 68, 72, 76, 80, 85, 89, 93, 
            97, 101, 105, 109, 113, 117, 121, 125, 
            129, 133, 137, 141, 145, 149, 153, 157, 
            161, 165, 170, 174, 178, 182, 186, 190, 
            194, 198, 202, 206, 210, 214, 218, 222, 
            226, 230, 234, 238, 242, 246, 250, 255
        };

        FGImageLayerHeader LayerHeader;
        FileStream.read(reinterpret_cast<char*>(&LayerHeader), sizeof(FGImageLayerHeader));

        uint8* Row = Pixels.data() + AlphaByteShift;
        int64 BytesToRead = LayerHeader.Size;

        while (BytesToRead > 0)
        {
            int8 byte{ 0 };
            FileStream.read(reinterpret_cast<char*>(&byte), sizeof(byte));
            --BytesToRead;

            if (byte < 0 && byte > INT8_MIN)   //Pixels data
            {
                uint8 ReadCount = byte & 0x7f;
                BytesToRead -= ReadCount;

                do
                {
                    uint8 alpha;
                    FileStream.read(reinterpret_cast<char*>(&alpha), sizeof(alpha));

                    *Row = LookupTable[0x3F - alpha];
                    Row += BytePerPixel;

                    --ReadCount;
                } while (ReadCount > 0);                
            }
            else if (byte > 0) //Skip some pixels
            {
                Row += byte * BytePerPixel;
            }
        }
    }

    TSharedPtr<ATextureClass> loadFrameType2(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
        TArray<uint8> Pixels(static_cast<uint64>(FileHeader.Right) * static_cast<uint64>(FileHeader.Bottom) * BytePerPixel);

        FGImageLayerInfo LayerInfo = LayersInfo[0];
        if (LayerInfo.Size > 0u)
        {
            FileStream.seekg(BaseOffset + LayerInfo.Offset, FileStream.beg);
            unpackRGB565(FileStream, Pixels);
        }

        LayerInfo = LayersInfo[1];
        if (LayerInfo.Size > 0u)
        {
            FileStream.seekg(BaseOffset + LayerInfo.Offset, FileStream.beg);
            unpackRGB565(FileStream, Pixels);
        }

        LayerInfo = LayersInfo[2];
        if (LayerInfo.Size > 0u)
        {
            FileStream.seekg(BaseOffset + LayerInfo.Offset, FileStream.beg);
            unpackA6(FileStream, Pixels);
        }

        return ATextureClass::Construct(Pixels, FileHeader.Right, FileHeader.Bottom, EPixelFormatType::ARGB32);
    }

    TSharedPtr<ATextureClass> loadFrameType3(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
        unimplemented();
        return nullptr;
    }

    TSharedPtr<ATextureClass> loadFrameType4(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
        unimplemented();
        return nullptr;
    }

    TSharedPtr<ATextureClass> loadFrameType5(std::ifstream& FileStream, const int64 BaseOffset, const FGImageFrameHeader& FileHeader, const TArray<FGImageLayerInfo>& LayersInfo)
    {
        unimplemented();
        return nullptr;
    }
}

FGImageFormat::~FGImageFormat()
{
    LOG("~FGImageFormat");
}

TUniquePtr<FGImageFormat> FGImageFormat::Load(const FPath& FileName)
{
    TUniquePtr<FGImageFormat> GImageFile = nullptr;
    if (std::filesystem::exists(FileName))
    {
        std::ifstream FileStream(FileName, std::ios::binary);
        if (FileStream.is_open())
        {
            uint32 Signature{ 0 };
            FileStream.read(reinterpret_cast<char*>(&Signature), sizeof(Signature));
            FileStream.seekg(0, FileStream.beg);

            if (Signature == GImageFormatSignature)
            {
                GImageFile = std::make_unique<FGImageFormat>();
                GImageFile->FileName = FileName.filename().string();
                GImageFile->Frame = LoadFrame(FileStream);
            }

            FileStream.close();
        }
    }

    return std::move(GImageFile);
}

TSharedPtr<ATextureClass> FGImageFormat::LoadFrame(std::ifstream& FileStream)
{
    const int64 BaseOffset = FileStream.tellg();

    FGImageFrameHeader FileHeader{ 0 };
    FileStream.read(reinterpret_cast<char*>(&FileHeader), sizeof(FGImageFrameHeader));
    
    if (FileHeader.Signature == GImageFormatSignature)
    {
        TArray<FGImageLayerInfo> LayersInfo(FileHeader.NumberOfLayers);
        FileStream.read(reinterpret_cast<char*>(LayersInfo.data()), sizeof(FGImageLayerInfo) * FileHeader.NumberOfLayers);

        switch (FileHeader.Type)
        {
        case EFrameType::OneLayer_DependsOnMask:
            return loadFrameType0(FileStream, BaseOffset, FileHeader, LayersInfo);
        case EFrameType::OneLayer_RGB16:
            return loadFrameType1(FileStream, BaseOffset, FileHeader, LayersInfo);
        case EFrameType::ThreeLayers:
            return loadFrameType2(FileStream, BaseOffset, FileHeader, LayersInfo);
        case EFrameType::TwoLayers:
            return loadFrameType3(FileStream, BaseOffset, FileHeader, LayersInfo);
        case EFrameType::OneLayer_Indexed8:
            return loadFrameType4(FileStream, BaseOffset, FileHeader, LayersInfo);
        case EFrameType::DeltaFrame:
            return loadFrameType5(FileStream, BaseOffset, FileHeader, LayersInfo);
        default:
            break;
        }
    }

    return nullptr;
}