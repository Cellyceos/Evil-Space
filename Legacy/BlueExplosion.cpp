#include "StdAfx.h"
#include "BlueExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Map.h"

BlueExplosion::BlueExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"W02a_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();

	frames = _image->GetFrameCount();
}

void BlueExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

BlueExplosion::~BlueExplosion(void)
{
}
