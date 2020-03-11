#include "stdafx.h"
#include "AsteroidExplosion.h"
#include "GDIBitmap.h"

AsteroidExplosion::AsteroidExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"des.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
}

void AsteroidExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

AsteroidExplosion::~AsteroidExplosion(void)
{
}
