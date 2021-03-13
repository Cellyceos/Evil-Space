//
//  SDLRenderer.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"


#ifdef USE_SDL_TTF
enum class ETextJustify {
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

struct FFontKey
{
	FStringView FontName;
	int32 FontSize;

	friend bool operator <(const FFontKey& Left, const FFontKey& Right)
	{
		if (Left.FontName == Right.FontName)
		{
			return Left.FontSize < Right.FontSize;
		}

		return Left.FontSize > Right.FontSize && Left.FontName < Right.FontName;
	}
};
#endif // USE_SDL_TTF


#ifdef USE_SDL_IMG
enum class EFlipOperation
{
	None,
	Horizontal,
	Vertical
};
#endif // USE_SDL_IMG


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

	virtual struct SDL_Renderer* GetNativeRenderer() const { return NativeRenderer; }

private:
	struct SDL_Renderer* NativeRenderer = nullptr;

#ifdef USE_SDL_TTF
public:
	virtual bool SetFont(const FStringView& FontName, const int32 FontSize);
	virtual void DrawText(const FStringView& Text, const FPoint& Position, ETextJustify Justify, const FColor& Color);

private:
	struct _TTF_Font* CurrentFont = nullptr;
	static TMap <FFontKey, struct _TTF_Font*> FontNameCache;

	void ClearFontResources();
#endif // USE_SDL_TTF

#ifdef USE_SDL_IMG
public:
	virtual void DrawImage(const FStringView& ImageName, const FPoint& Center, const float Rotation, const EFlipOperation Flip = EFlipOperation::None);

private:
	static TMap <FStringView, struct SDL_Texture*> ImageNameCache;

	void ClearImageResources();
#endif // USE_SDL_IMG


#ifdef DEBUG_UI
private:
	static FColor DebugColor;
#endif // _DEBUG
};

using ARendererClass = SDLRenderer;
