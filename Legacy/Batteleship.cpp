#include "stdafx.h"
#include "Batteleship.h"
#include "GDIBitmap.h"
#include "BigWeapon.h"
#include "Compositor.h"
#include "MediumExplosion.h"

Batteleship::Batteleship(Map* map, Compositor* compositor) : Enemy(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + ShipPath + L"Terron1s.tif");
	points = 100;
	damage = 10;
	health = 300;
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	speed = MaxSpeed - 4;
	Weapons(new BigWeapon(this));
}

void Batteleship::Explode() 
{
	MediumExplosion* explosion = new MediumExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

Batteleship::~Batteleship(void)
{
}
