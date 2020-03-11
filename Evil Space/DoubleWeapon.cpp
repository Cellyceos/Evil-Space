#include "StdAfx.h"
#include "DoubleWeapon.h"
#include "BlueMissile.h"
#include "GameObject.h"
#include "Compositor.h"
#include "Ship.h"

DoubleWeapon::DoubleWeapon(Ship* ship) : Weapon(ship)
{
	fireRate = 12;
	damage = 15;
	speed = 22;
	distance = 250;
}

DoubleWeapon::~DoubleWeapon(void)
{
}

void DoubleWeapon::FireMissile()
{
	CreateMissile(ships->Direction() - 10);
	CreateMissile(ships->Direction());
	CreateMissile(ships->Direction() + 10);
}

void DoubleWeapon::CreateMissile(float direction) 
{
	BlueMissile* missile = new BlueMissile(ships);

	missile->Damage(damage);
	missile->Speed(speed);
	missile->Distance(distance);
	missile->Direction(direction);
	missile->MiddlePoint(ships->MiddlePoint());

	missile->MoveOutOfRegion(ships);

	ships->Compositors->AddGameObject(missile);
}
