#include "StdAfx.h"
#include "BigExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Map.h"

BigExplosion::BigExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"W03a_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();

	frames = _image->GetFrameCount();
}

void BigExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

BigExplosion::~BigExplosion(void)
{
}
