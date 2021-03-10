#include "stdafx.h"
#include "Battlecruiser.h"
#include "GDIBitmap.h"
#include "BigWeapon.h"
#include "Compositor.h"
#include "SmallExplosion.h"


Battlecruiser::Battlecruiser(Map* map, Compositor* compositor) : Enemy(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + ShipPath + L"Terron2s.tif");
	points = 75;
	damage = 10;
	health = 175;
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	speed = MaxSpeed - 3;
}

void Battlecruiser::Explode() 
{
	SmallExplosion* explosion = new SmallExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

Battlecruiser::~Battlecruiser(void)
{
}
