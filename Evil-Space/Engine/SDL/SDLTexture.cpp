//
//  SDLSurface.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLTexture.h"
#include "Logging/Macros.h"

#include "SDL_surface.h"
#include "SDL_render.h"

SDLTexture::SDLTexture(SDL_Surface* SurfacePtr) : NativeSurface(SurfacePtr)
{
	// Enable Alpha Blending by default
	SDL_SetSurfaceBlendMode(NativeSurface, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceRLE(NativeSurface, true);

	Width = NativeSurface->w;
	Height = NativeSurface->h;
	Format = static_cast<EPixelFormatType>(NativeSurface->format->format);
}

SDLTexture::SDLTexture(struct SDL_Texture* TexturePtr) : NativeTexture(TexturePtr), bCreatedFromSurface(false)
{
	// Enable Alpha Blending by default
	SDL_SetTextureBlendMode(NativeTexture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(NativeTexture, reinterpret_cast<uint32*>(&Format), nullptr, &Width, &Height);
}

void SDLTexture::SetColorPalette(const TSharedPtr<APaletteClass>& Palette)
{
	assert(bCreatedFromSurface);  // Should be called before first draw was call
	SDL_SetSurfacePalette(NativeSurface, Palette->GetNativePalette());
}

SDLTexture::~SDLTexture()
{
	if (NativeSurface)
	{
		SDL_FreeSurface(NativeSurface);
		NativeSurface = nullptr;
	}

	if (NativeTexture)
	{
		SDL_DestroyTexture(NativeTexture);
		NativeTexture = nullptr;
	}

	LOG("~SDLTexture\n");
}

TSharedPtr<SDLTexture> SDLTexture::Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth,
	uint32 RedMask /* = 0u */, uint32 GreenMask /* = 0u */, uint32 BlueMask /* = 0u */, uint32 AlphaMask /* = 0u */)
{
	if (SDL_Surface* NativeSurface = SDL_CreateRGBSurface(0, Width, Height, Depth, RedMask, GreenMask, BlueMask, AlphaMask))
	{
		SDL_LockSurface(NativeSurface);
		std::memcpy(NativeSurface->pixels, Pixels.data(), Pixels.size());
		SDL_UnlockSurface(NativeSurface);

		return std::make_shared<SDLTexture>(NativeSurface);
	}

	LOG_CRITICAL("Unable to create surface, error: %s", SDL_GetError());
	return nullptr;
}

bool SDLTexture::CreateTextureFromSurface(SDL_Renderer* NativeRenderer)
{
	if (bCreatedFromSurface)
	{
		bCreatedFromSurface = false;
		NativeTexture = SDL_CreateTextureFromSurface(NativeRenderer, NativeSurface);

		SDL_FreeSurface(NativeSurface);
		NativeSurface = nullptr;

		return true;
	}

	return false;
}

TSharedPtr<SDLTexture> SDLTexture::Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, EPixelFormatType PixelFormat)
{
	if (SDL_Surface* NativeSurface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 0, static_cast<uint32>(PixelFormat)))
	{
		SDL_LockSurface(NativeSurface);
		std::memcpy(NativeSurface->pixels, Pixels.data(), Pixels.size());
		SDL_UnlockSurface(NativeSurface);

		return std::make_shared<SDLTexture>(NativeSurface);
	}

	LOG_CRITICAL("Unable to create surface, error: %s", SDL_GetError());
	return nullptr;
}

#ifdef USE_SDL_IMG
#include "SDL_image.h"

static TSharedPtr<SDLTexture> SDLTexture::Construct(const FStringView& ImageName)
{
	if (SDL_Surface* NativeSurface = IMG_Load(ImageName.data()))
	{
		return std::make_shared<SDLTexture>(NativeSurface);
	}

	LOG_CRITICAL("Unable to load image, error: %s", SDL_GetError());
	return nullptr;
}
#endif
