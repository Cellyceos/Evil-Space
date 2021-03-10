#include "StdAfx.h"
#include "BigMissile.h"
#include "BigExplosion.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Bonus.h"
#include "Ship.h"


BigMissile::BigMissile(Ship* ship) : Ammunition(ship), DefaultWidth(29), DefaultHeight(29), Radius(50)
{
	_image = GDIBitmap::FromFile(ContentPath + AmmunitionPath + L"W03_F.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
	Rects.X = 0;
	Rects.Y = 0;
}

void BigMissile::Explode() 
{
	BigExplosion* explosion = new BigExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

void BigMissile::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

BigMissile::~BigMissile(void)
{
}
