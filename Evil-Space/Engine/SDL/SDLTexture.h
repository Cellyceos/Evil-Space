//
//  SDLTexture.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "SDL/SDLPalette.h"

#include "SDL_pixels.h"


enum class EPixelFormatType
{
    Unknown = SDL_PIXELFORMAT_UNKNOWN,
    Mono = SDL_PIXELFORMAT_INDEX1MSB,
    MonoLSB = SDL_PIXELFORMAT_INDEX1LSB,
    Indexed8 = SDL_PIXELFORMAT_INDEX8,
    RGB32 = SDL_PIXELFORMAT_RGB888,
    ARGB32 = SDL_PIXELFORMAT_ARGB32,
    RGB16 = SDL_PIXELFORMAT_RGB565,
    RGB555 = SDL_PIXELFORMAT_RGB555,
    RGB888 = SDL_PIXELFORMAT_RGB888,
    RGB444 = SDL_PIXELFORMAT_RGB444,
    ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
    RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
    RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
    BGR24 = SDL_PIXELFORMAT_BGR24,
    RGB24 = SDL_PIXELFORMAT_RGB24,
};


class SDLTexture : public std::enable_shared_from_this<SDLTexture>
{
public:
    explicit SDLTexture(struct SDL_Surface* SurfacePtr);
    explicit SDLTexture(struct SDL_Texture* TexturePtr);
    virtual ~SDLTexture();

    int32 GetWidth() const { return Width; }
    int32 GetHeight() const { return Height; }
    EPixelFormatType GetFormat() const { return Format; }

    void SetColorPalette(const TSharedPtr<APaletteClass>& Palette);

    struct SDL_Texture* GetNativeTexture() const { return NativeTexture; }

    static TSharedPtr<SDLTexture> Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth, uint32 RedMask = 0u, uint32 GreenMask = 0u, uint32 BlueMask = 0u, uint32 AlphaMask = 0u);
    static TSharedPtr<SDLTexture> Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, EPixelFormatType PixelFormat);

private:
    friend class SDLRenderer;

    struct SDL_Surface* NativeSurface = nullptr;
    struct SDL_Texture* NativeTexture = nullptr;

    bool bCreatedFromSurface = true;
    bool CreateTextureFromSurface(struct SDL_Renderer* NativeRenderer);

    int32 Width = 0;
    int32 Height = 0;
    EPixelFormatType Format = EPixelFormatType::Unknown;

#ifdef USE_SDL_IMG
public:
    static TSharedPtr<SDLTexture> Construct(const FStringView& ImageName);
#endif
};

using ATextureClass = SDLTexture;
