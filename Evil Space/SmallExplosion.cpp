#include "StdAfx.h"
#include "SmallExplosion.h"
#include "GDIBitmap.h"

SmallExplosion::SmallExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"Expl0.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
}

void SmallExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

SmallExplosion::~SmallExplosion(void)
{
}
