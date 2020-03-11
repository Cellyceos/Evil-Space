#include "stdafx.h"
#include "Cruisers.h"
#include "GDIBitmap.h"
#include "DoubleWeapon.h"
#include "MediumExplosion.h"
#include "Compositor.h"

Cruisers::Cruisers(Map* map, Compositor* compositor) : Enemy(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + ShipPath + L"Terron3s.tif");
	points = 50;
	damage = 10;
	health = 100;
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	speed = MaxSpeed - 2;
	Weapons(new DoubleWeapon(this));
}

void Cruisers::Explode() 
{
	MediumExplosion* explosion = new MediumExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

Cruisers::~Cruisers(void)
{
}
