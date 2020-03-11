#include "StdAfx.h"
#include "InvisibilityBonus.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "BigWeapon.h"
#include "Player.h"
#include "Map.h"

InvisibilityBonus::InvisibilityBonus(Map* map, Compositor* compositor) : Bonus(map, compositor)
{
	_image = GDIBitmap::FromFile(ContentPath + BonusPath + L"Invisibility.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;
}

void InvisibilityBonus::GivePowerup(Player* player) 
{
	//player->Weapons(new BigWeapon(player));

	Bonus::GivePowerup(player);
}

void InvisibilityBonus::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

InvisibilityBonus::~InvisibilityBonus(void)
{
}
