//
//  SDLRenderer.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLRenderer.h"

#include "SDL_render.h"
#include "SDL_messagebox.h"


#ifdef DEBUG_UI
FColor SDLRenderer::DebugColor{255, 0, 0, 255};
#endif // _DEBUG


TSharedPtr<SDLRenderer> SDLRenderer::Construct(SDL_Window* Window)
{
	SDL_Renderer* NativeRenderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (!NativeRenderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create renderer. See the log for more info.", NULL);
		LOG_CRITICAL("Unable to create window, error: %s", SDL_GetError());
		return nullptr;
	}

	return std::make_shared<SDLRenderer>(NativeRenderer);
}

SDLRenderer::SDLRenderer(SDL_Renderer* Renderer) : NativeRenderer(Renderer)
{
	// Enable Alpha Blending by default
	SDL_SetRenderDrawBlendMode(NativeRenderer, SDL_BLENDMODE_BLEND);
}

SDLRenderer::~SDLRenderer()
{
	LOG("~SDLRenderer\n");

#ifdef USE_SDL_TTF
	ClearFontResources();
#endif

#ifdef USE_SDL_IMG
	ClearImageResources();
#endif // USE_SDL_IMG

	if (NativeRenderer)
	{
		SDL_DestroyRenderer(NativeRenderer);
		NativeRenderer = nullptr;
	}
}

void SDLRenderer::Clear(const FColor& Color)
{
	SetColor(Color);
	SDL_RenderClear(NativeRenderer);
}

void SDLRenderer::SetColor(const FColor& Color)
{
	SDL_SetRenderDrawColor(NativeRenderer, Color.Red, Color.Green, Color.Blue, Color.Alpha);
}

void SDLRenderer::DrawRect(const FRect& Rect)
{	
	const SDL_FRect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderDrawRectF(NativeRenderer, &NativeRect);
}

void SDLRenderer::FillRect(const FRect& Rect)
{	
	const SDL_FRect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderFillRectF(NativeRenderer, &NativeRect);
}

void SDLRenderer::DrawCircle(const FPoint& Center, float Radius)
{
	float OffsetX = 0.0f;
	float OffsetY = Radius;
	float RadiusError = Radius - 1.0f;

	while (OffsetY >= OffsetX)
	{
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetY, Center.Y - OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2.0f * OffsetX) 
		{
			RadiusError -= 2.0f * OffsetX + 1.0f;
			OffsetX += 1.0f;
		}
		else if (RadiusError < 2.0f * (Radius - OffsetY)) 
		{
			RadiusError += 2.0f * OffsetY - 1.0f;
			OffsetY -= 1.0f;
		}
		else 
		{
			RadiusError += 2.0f * (OffsetY - OffsetX - 1.0f);
			OffsetY -= 1.0f;
			OffsetX += 1.0f;
		}
	}
}

void SDLRenderer::FillCircle(const FPoint& Center, float Radius)
{
	float OffsetX = 0.0f;
	float OffsetY = Radius;
	float RadiusError = Radius - 1.0f;

	while (OffsetY >= OffsetX) 
	{
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX, Center.X + OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2.0f * OffsetX) 
		{
			RadiusError -= 2.0f * OffsetX + 1.0f;
			OffsetX += 1.0f;
		}
		else if (RadiusError < 2.0f * (Radius - OffsetY)) 
		{
			RadiusError += 2.0f * OffsetY - 1.0f;
			OffsetY -= 1.0f;
		}
		else 
		{
			RadiusError += 2.0f * (OffsetY - OffsetX - 1.0f);
			OffsetY -= 1.0f;
			OffsetX += 1.0f;
		}
	}
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(NativeRenderer);
}

#ifdef USE_SDL_TTF
#include "SDL_ttf.h"

TMap <FFontKey, TTF_Font*> SDLRenderer::FontNameCache;

bool SDLRenderer::SetFont(const FStringView& FontName, const int32 FontSize)
{
	const FFontKey FontKey{ FontName, FontSize };
	auto CachedFont = FontNameCache.find(FontKey);

	if (CachedFont == FontNameCache.end())
	{
		CurrentFont = TTF_OpenFont(FontName.data(), FontSize);
		if (!CurrentFont)
		{
			LOG_ERROR("TTF ERROR: %s", SDL_GetError());
			return false;
		}

		FontNameCache.insert(std::make_pair(FontKey, CurrentFont));
	}
	else
	{
		CurrentFont = CachedFont->second;
	}

	return true;
}

void SDLRenderer::DrawText(const FStringView& Text, const FPoint& Position, ETextJustify Justify, const FColor& Color)
{
	SDL_Surface* Surface = TTF_RenderText_Blended(CurrentFont, Text.data(), { Color.Red, Color.Green, Color.Blue, Color.Alpha });
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(NativeRenderer, Surface);

	int32 TextureWidth{ 0 }, TextureHeight{ 0 };
	SDL_QueryTexture(Texture, nullptr, nullptr, &TextureWidth, &TextureHeight);

	SDL_FRect DestRect = { Position.X, Position.Y, static_cast<float>(TextureWidth), static_cast<float>(TextureHeight) };

	switch (Justify)
	{
	case ETextJustify::LeftTop:
		DestRect.x -= TextureWidth;
		break;
	case ETextJustify::LeftMiddle:
		DestRect.x -= TextureWidth;
		DestRect.y -= TextureHeight * 0.5f;
		break;
	case ETextJustify::LeftBottom:
		DestRect.x -= TextureWidth;
		DestRect.y -= TextureHeight;
		break;
	case ETextJustify::CenteredTop:
		DestRect.x -= TextureWidth * 0.5f;
		break;
	case ETextJustify::CenteredMiddle:
		DestRect.x -= TextureWidth * 0.5f;
		DestRect.y -= TextureHeight * 0.5f;
		break;
	case ETextJustify::CenteredBottom:
		DestRect.x -= TextureWidth * 0.5f;
		DestRect.y -= TextureHeight;
		break;
	case ETextJustify::RightTop:
		break;
	case ETextJustify::RightMiddle:
		DestRect.y -= TextureHeight * 0.5f;
		break;
	case ETextJustify::RightBottom:
		DestRect.y -= TextureHeight;
		break;
	}

	SDL_RenderCopyF(NativeRenderer, Texture, nullptr, &DestRect);

#ifdef DEBUG_UI
	SetColor(DebugColor);
	FillRect({ Position.X - 2.0f, Position.Y - 2.0f, 4.0f, 4.0f });
#endif //DEBUG_UI

	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(Texture);
}

void SDLRenderer::ClearFontResources()
{
	for (auto& [FontKey, Font] : FontNameCache)
	{
		TTF_CloseFont(Font);
		Font = nullptr;
	}

	FontNameCache.clear();
}
#endif

#ifdef USE_SDL_IMG
#include "SDL_image.h"

TMap <FStringView, SDL_Texture*> SDLRenderer::ImageNameCache;

void SDLRenderer::DrawImage(const FStringView& ImageName, const FPoint& Center, const float Rotation, const EFlipOperation Flip/* = EFlipOperation::None */)
{
	SDL_Texture* ImageTexture{ nullptr };

	auto CachedImage = ImageNameCache.find(ImageName);

	if (CachedImage == ImageNameCache.end())
	{
		ImageTexture = IMG_LoadTexture(NativeRenderer, ImageName.data());
		if (!ImageTexture)
		{
			LOG_ERROR("IMG ERROR: %s", SDL_GetError());
			return;
		}

		ImageNameCache.insert(std::make_pair(ImageName, ImageTexture));
	}
	else
	{
		ImageTexture = CachedImage->second;
	}

	const SDL_FPoint NativeCenter{ Center.X, Center.Y };
	SDL_RenderCopyExF(NativeRenderer, ImageTexture, nullptr, nullptr, Rotation, &NativeCenter, static_cast<SDL_RendererFlip>(Flip));

#ifdef DEBUG_UI
	SetColor(DebugColor);
	FillRect({ Center.X - 2.0f, Center.Y - 2.0f, 4.0f, 4.0f });
#endif //DEBUG_UI
}

void SDLRenderer::ClearImageResources()
{
	for (auto& [ImageName, ImageTexture] : ImageNameCache)
	{
		SDL_DestroyTexture(ImageTexture);
		ImageTexture = nullptr;
	}

	ImageNameCache.clear();
}
#endif // USE_SDL_IMG
