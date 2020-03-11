#include "stdafx.h"
#include "MediumExplosion.h"
#include "GDIBitmap.h"

MediumExplosion::MediumExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"Expl1.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
}

void MediumExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

MediumExplosion::~MediumExplosion(void)
{
}
