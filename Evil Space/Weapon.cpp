#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "GameTicks.h"

Weapon::Weapon(Ship* ship): distance(0), damage(0), speed(0), fireRate(5), fireCount(0), ships(ship)
{}

void Weapon::Fire()
{
	fireCount++;
	if (fireCount < fireRate)
		return;

	fireCount = 0;

	FireMissile();

	Player* player = dynamic_cast<Player*>(ships);

	if (player != NULL)
		player->MissilesFired++;
}

void Weapon::Damage(int ammount)
{
	damage += ammount;
}

void Weapon::Reload()
{
	fireCount = fireRate;
}

Weapon::~Weapon(void)
{
}