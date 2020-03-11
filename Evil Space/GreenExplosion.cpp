#include "StdAfx.h"
#include "GreenExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Map.h"

GreenExplosion::GreenExplosion(Map* map, Compositor* compositor): Effect(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + EffectPath + L"W09a_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	rotation = 90;
	frames = _image->GetFrameCount();
}

void GreenExplosion::Draw(Graphics* g) 
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}

GreenExplosion::~GreenExplosion(void)
{
}
