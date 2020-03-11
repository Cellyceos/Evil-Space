#include "StdAfx.h"
#include "Bonus.h"
#include "Compositor.h"
#include "Player.h"
#include "Map.h"

wstring& Bonus::BonusPath = *new wstring(L"Bonus\\");

Bonus::Bonus(Map* map, Compositor* compositor) : InteractiveObject(map, compositor), DefaultHealth(1), MaxTime(1000), DefaultPoints(5), time(0), _image(NULL)
{
	health = DefaultHealth;
	points = DefaultPoints;
}

void Bonus::GivePowerup(Player* player) 
{
	player->Points(player->Points() + points);

	health = 0;
}

void Bonus::CollidedWith(InteractiveObject *const obj) 
{
	Player* player = dynamic_cast<Player*>(obj);

	if (player != NULL)
		GivePowerup(player);
}

void Bonus::Update() 
{
	InteractiveObject::Update();

	time++;
	if (MaxTime < time) {
		health = 0;
	}
}

Bonus::~Bonus(void)
{
}
