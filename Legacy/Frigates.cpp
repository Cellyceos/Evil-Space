#include "stdafx.h"
#include "Frigates.h"
#include "GDIBitmap.h"
#include "SmallExplosion.h"
#include "Compositor.h"

Frigates::Frigates(Map* map, Compositor* compositor) : Enemy(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + ShipPath + L"Terron4s.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	speed = MaxSpeed;
	points = 25;
	damage = 10;
	health = 30;
}

void Frigates::Explode() 
{
	SmallExplosion* explosion = new SmallExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

Frigates::~Frigates(void)
{
}
