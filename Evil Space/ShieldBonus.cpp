#include "StdAfx.h"
#include "ShieldBonus.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "Player.h"
#include "Map.h"

ShieldBonus::ShieldBonus(Map* map, Compositor* compositor) : Bonus(map, compositor), shieldProvided(150)
{
	_image = GDIBitmap::FromFile(ContentPath + BonusPath + L"Shield.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;
}

void ShieldBonus::GivePowerup(Player* player) 
{
	player->Shild(player->Shild() + shieldProvided);

	Bonus::GivePowerup(player);
}

void ShieldBonus::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

int ShieldBonus::GivenShield()
{
	return shieldProvided;
}

void ShieldBonus::GivenShield(int obj)
{
	shieldProvided = obj;
}

ShieldBonus::~ShieldBonus(void)
{
}
