#include "StdAfx.h"
#include "BlueMissile.h"
#include "BlueExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Ship.h"

BlueMissile::BlueMissile(Ship* ship) : Ammunition(ship)
{
	_image = GDIBitmap::FromFile(ContentPath + AmmunitionPath + L"W02_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	direction = ship->Direction() - 90.0f;
	Rects.X = 0;
	Rects.Y = 0;
}

void BlueMissile::Explode() 
{
	BlueExplosion* explosion = new BlueExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

void BlueMissile::Draw(Graphics* g) 
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}


BlueMissile::~BlueMissile(void)
{
}
