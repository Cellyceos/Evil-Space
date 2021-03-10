#include "StdAfx.h"
#include "PowerBonus.h"
#include "GDIBitmap.h"
#include "Player.h"
#include "Weapon.h"

PowerBonus::PowerBonus(Map* map, Compositor* compositor) : Bonus(map, compositor), powerProvided(5) 
{
	_image = GDIBitmap::FromFile(ContentPath + BonusPath + L"Power.tif");
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;

}

void PowerBonus::GivePowerup(Player* player) {

	player->Weapons()->Damage(powerProvided);

	Bonus::GivePowerup(player);
}

void PowerBonus::Draw(Graphics* g) 
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

int PowerBonus::GivenPower()
{
	return powerProvided;
}

void PowerBonus::GivenPower(int obj)
{
	powerProvided = obj;
}

PowerBonus::~PowerBonus(void)
{
}
