#include "StdAfx.h"
#include "GreenMissile.h"
#include "GreenExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Ship.h"

GreenMissile::GreenMissile(Ship* ship) : Ammunition(ship)
{
	_image = GDIBitmap::FromFile(ContentPath + AmmunitionPath + L"W09_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	rotation = 90;
	Rects.X = 0;
	Rects.Y = 0;
}

void GreenMissile::Explode() 
{
	GreenExplosion* explosion = new GreenExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());
	explosion->Direction(direction);
	Compositors->AddGameObject(explosion);
}

void GreenMissile::Draw(Graphics* g) 
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}

GreenMissile::~GreenMissile(void)
{
}
