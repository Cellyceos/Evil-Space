//
//  FHAImageFormat.cpp
//  HAImage File Format.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FHAImageFormat.h"
#include "SDL/SDLRenderer.h"


namespace
{
	static constexpr uint32 HAImageFormatSignature{ 0x04210420 };
	struct FHAImageHeader
	{
		uint32 Signature;
		uint32 Width;
		uint32 Height;
		uint32 Pitch;
		uint32 FrameCount;
		uint32 FrameSize;
		uint32 BytesPerPixel;
		uint32 BitsPerPixel;
		Uint32 RedMask;
		Uint32 GreenMask;
		Uint32 BlueMask;
		Uint32 AlphaMask;
		uint32 PalleteSize;
	};
}

FHAImageFormat::~FHAImageFormat()
{

}

TUniquePtr<FHAImageFormat> FHAImageFormat::Load(const FStringView& FileName)
{
	TUniquePtr<FHAImageFormat> HAImageFile = nullptr;
	if (std::filesystem::exists(FileName))
	{
		std::ifstream FileStream(FileName, std::ios::binary);
		if (FileStream.is_open())
		{
			FHAImageHeader FileHeader{ 0 };
			FileStream.read(reinterpret_cast<char*>(&FileHeader), sizeof(FileHeader));

			if (FileHeader.Signature == HAImageFormatSignature)
			{
				HAImageFile = std::make_unique<FHAImageFormat>();
				HAImageFile->Frames.reserve(FileHeader.FrameCount);
				HAImageFile->Height = static_cast<float>(FileHeader.Height);
				HAImageFile->Width = static_cast<float>(FileHeader.Width);
				HAImageFile->FileName = FString(std::filesystem::path(FileName).filename().u8string());

				TArray<uint8> Pixels(FileHeader.FrameSize - FileHeader.PalleteSize);
				TArray<uint8> Colors(FileHeader.PalleteSize);

				for (uint32 Idx = 0u; Idx < FileHeader.FrameCount; Idx++)
				{
					FileStream.read(reinterpret_cast<char*>(Pixels.data()), Pixels.size());
					auto Frame = ATextureClass::Construct(Pixels, FileHeader.Width, FileHeader.Height, FileHeader.BitsPerPixel, FileHeader.RedMask, FileHeader.GreenMask, FileHeader.BlueMask, FileHeader.AlphaMask);
					
					FileStream.read(reinterpret_cast<char*>(Colors.data()), Colors.size());
					auto Palette = APaletteClass::Construct(Colors);
					Frame->SetColorPalette(Palette);

					HAImageFile->Frames.push_back(Frame);
				}
			}

			FileStream.close();
		}
	}

	return std::move(HAImageFile);
}
