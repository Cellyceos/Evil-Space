#include "StdAfx.h"
#include "HealthBonus.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Player.h"
#include "Map.h"

HealthBonus::HealthBonus(Map* map, Compositor* compositor) : Bonus(map, compositor) 
{
	_image = GDIBitmap::FromFile(ContentPath + BonusPath + L"Health.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;
}

void HealthBonus::GivePowerup(Player* player) 
{
	player->Health(player->Health() + 150);
	Bonus::GivePowerup(player);
}

void HealthBonus::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

HealthBonus::~HealthBonus(void)
{
}
