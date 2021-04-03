//
//  FHAIFormat.cpp
//  HAI File Format.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FHAIFormat.h"
#include "SDL/SDLRenderer.h"


namespace
{
	static constexpr uint32 HAIFormatSignature{ 0x04210420 };
	struct FHAIHeader
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

FHAIFormat::~FHAIFormat()
{

}

TUniquePtr<FHAIFormat> FHAIFormat::Load(const FStringView& FileName)
{
	TUniquePtr<FHAIFormat> HAIFile = nullptr;
	if (std::filesystem::exists(FileName))
	{
		std::ifstream FileStream(FileName, std::ios::binary);
		if (FileStream.is_open())
		{
			FHAIHeader FileHeader{ 0 };
			FileStream.read(reinterpret_cast<char*>(&FileHeader), sizeof(FileHeader));

			if (FileHeader.Signature == HAIFormatSignature)
			{
				HAIFile = std::make_unique<FHAIFormat>();
				HAIFile->Frames.reserve(FileHeader.FrameCount);
				HAIFile->Height = static_cast<float>(FileHeader.Height);
				HAIFile->Width = static_cast<float>(FileHeader.Width);
				HAIFile->FileName = FString(std::filesystem::path(FileName).filename().u8string());

				TArray<uint8> Pixels(FileHeader.FrameSize - FileHeader.PalleteSize);
				TArray<uint8> Colors(FileHeader.PalleteSize);

				for (uint32 Idx = 0u; Idx < FileHeader.FrameCount; Idx++)
				{
					FileStream.read(reinterpret_cast<char*>(Pixels.data()), Pixels.size());
					auto Frame = ATextureClass::Construct(Pixels, FileHeader.Width, FileHeader.Height, FileHeader.BitsPerPixel, FileHeader.RedMask, FileHeader.GreenMask, FileHeader.BlueMask, FileHeader.AlphaMask);
					
					FileStream.read(reinterpret_cast<char*>(Colors.data()), Colors.size());
					auto Palette = APaletteClass::Construct(Colors);
					Frame->SetColorPalette(Palette);

					HAIFile->Frames.push_back(Frame);
				}
			}

			FileStream.close();
		}
	}

	return std::move(HAIFile);
}
