//
//  SDLPalette.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/16/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLPalette.h"
#include "Logging/Macros.h"

#include "SDL_pixels.h"
#include "SDL_error.h"

namespace
{
	static struct FPicelFormatCache
	{
		TMap<uint32, SDL_PixelFormat*> Cache;

		~FPicelFormatCache()
		{
			for (auto& [FormatKey, Format] : Cache)
			{
				SDL_FreeFormat(Format);
				Format = nullptr;
			}

			Cache.clear();
			LOG("~FPicelFormatCache");
		}

		SDL_PixelFormat* CreateOrFindPixelFormat(uint32 FormatKey)
		{
			auto CachedFormat = Cache.find(FormatKey);
			SDL_PixelFormat* Result = nullptr;

			if (CachedFormat == Cache.end())
			{
				Result = SDL_AllocFormat(FormatKey);
				if (!Result)
				{
					LOG_ERROR("SDL ERROR: {:s}", SDL_GetError());
					return nullptr;
				}

				Cache.insert(std::make_pair(FormatKey, Result));
			}
			else
			{
				Result = CachedFormat->second;
			}

			return Result;
		}
	} PicelFormatCache;
}

SDLPalette::SDLPalette(SDL_Palette* PalettePtr) : NativePalette(PalettePtr)
{

}

SDLPalette::~SDLPalette()
{
	if (NativePalette)
	{
		SDL_FreePalette(NativePalette);
		NativePalette = nullptr;
	}

	LOG("~SDLPalette");
}

uint32 SDLPalette::ConvertPixel(uint32 Pixel, EPixelFormatType FromPixelFormatType, EPixelFormatType ToPixelFormatType)
{
	SDL_PixelFormat* FromPixelFormat = PicelFormatCache.CreateOrFindPixelFormat(ConvertPixelFormat(FromPixelFormatType));
	SDL_PixelFormat* ToPixelFormat = PicelFormatCache.CreateOrFindPixelFormat(ConvertPixelFormat(ToPixelFormatType));

	uint8 Red, Green, Blue, Alpha;
	SDL_GetRGBA(Pixel, FromPixelFormat, &Red, &Green, &Blue, &Alpha);
	uint32 NewPixel = SDL_MapRGBA(ToPixelFormat, Red, Green, Blue, Alpha);

	return NewPixel;
}

uint32 SDLPalette::ConvertPixelFormat(EPixelFormatType PixelFormatType)
{
	switch (PixelFormatType)
	{
	case EPixelFormatType::Mono:
		return SDL_PIXELFORMAT_INDEX1MSB;
	case EPixelFormatType::MonoLSB:
		return SDL_PIXELFORMAT_INDEX1LSB;
	case EPixelFormatType::Indexed8:
		return SDL_PIXELFORMAT_INDEX8;
	case EPixelFormatType::RGB32: 
		return SDL_PIXELFORMAT_RGB888;
	case EPixelFormatType::ARGB32: 
		return SDL_PIXELFORMAT_ARGB8888;
	case EPixelFormatType::RGB16: 
		return SDL_PIXELFORMAT_RGB565;
	case EPixelFormatType::RGB555: 
		return SDL_PIXELFORMAT_RGB555;
	case EPixelFormatType::RGB888: 
		return SDL_PIXELFORMAT_RGB888;
	case EPixelFormatType::RGB444: 
		return SDL_PIXELFORMAT_RGB444;
	case EPixelFormatType::ARGB4444: 
		return SDL_PIXELFORMAT_ARGB4444;
	case EPixelFormatType::RGBX8888: 
		return SDL_PIXELFORMAT_RGBX8888;
	case EPixelFormatType::RGBA8888:
		return SDL_PIXELFORMAT_RGBA8888;
	case EPixelFormatType::BGR24: 
		return SDL_PIXELFORMAT_BGR24;
	case EPixelFormatType::RGB24: 
		return SDL_PIXELFORMAT_RGB24;
	case EPixelFormatType::Unknown:
	default:
		return SDL_PIXELFORMAT_UNKNOWN;
	}
}

TSharedPtr<SDLPalette> SDLPalette::Construct(const TArray<uint8>& Colors)
{
	const int32 NumberColors = static_cast<int32>(Colors.size() >> 2);
	if (SDL_Palette* NativePalette = SDL_AllocPalette(NumberColors))
	{
		SDL_SetPaletteColors(NativePalette, reinterpret_cast<const SDL_Color*>(Colors.data()), 0, NumberColors);
		return std::make_shared<SDLPalette>(NativePalette);
	}

	return nullptr;
}