#include "StdAfx.h"
#include "StaticExplosion.h"
#include "GDIBitmap.h"

StaticExplosion::StaticExplosion(Map* map, Compositor* compositor) : Effect(map, compositor)
{
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();

	frames = _image->GetFrameCount();
}

void StaticExplosion::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

StaticExplosion::~StaticExplosion(void)
{
}
