#include "StdAfx.h"
#include "BatteryBonus.h"
#include "GDIBitmap.h"
#include "Player.h"

BatteryBonus::BatteryBonus(Map* map, Compositor* compositor) : Bonus(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + BonusPath + L"Battery.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;
}

void BatteryBonus::GivePowerup(Player* player) 
{
	Bonus::GivePowerup(player);
}

void BatteryBonus::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

BatteryBonus::~BatteryBonus(void)
{
}
