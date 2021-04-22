//
//  SDLRenderer.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "SDL/SDLTexture.h"


enum class EJustify {
	LeftTop,
	LeftMiddle, 
	LeftBottom,
	CenteredTop,
	CenteredMiddle,
	CenteredBottom,
	RightTop,
	RightMiddle,
	RightBottom
};


class SDLRenderer
{
public:
	explicit SDLRenderer(struct SDL_Renderer* RendererPtr);
	virtual ~SDLRenderer();

	static TSharedPtr<SDLRenderer> Construct(struct SDL_Window* Window);

	virtual void Clear(const FColor& Color);
	virtual void Present();

	virtual void SetColor(const FColor& Color);

	// Rectangle
	virtual void DrawRect(const FRect& Rect);
	virtual void FillRect(const FRect& Rect);

	// Circle
	virtual void DrawCircle(const FPoint& Center, float Radius);
	virtual void FillCircle(const FPoint& Center, float Radius);

	virtual void DrawTexture(const TSharedPtr<ATextureClass>& Surface, const FPoint& Position, float Rotation, EJustify Justify = EJustify::CenteredMiddle);

	virtual struct SDL_Renderer* GetNativeRenderer() const { return NativeRenderer; }

private:
	struct SDL_Renderer* NativeRenderer = nullptr;

	void DrawTextureInternal(struct SDL_Texture* Texture, const FPoint& Position, float Rotation, EJustify Justify);

#ifdef USE_SDL_TTF
public:
	virtual bool SetFont(const FStringView& FontName, const int32 FontSize);
	virtual void DrawText(const FStringView& Text, const FPoint& Position, EJustify Justify, const FColor& Color);

private:
	struct _TTF_Font* CurrentFont = nullptr;
	static TUnorderedMap <uint64, struct _TTF_Font*> FontNameCache;

	void ClearFontResources();
#endif // USE_SDL_TTF

#ifdef DEBUG_UI
private:
	static FColor DebugColor;
#endif // _DEBUG
};

using ARendererClass = SDLRenderer;
