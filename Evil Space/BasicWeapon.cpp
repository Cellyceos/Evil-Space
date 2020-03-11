#include "StdAfx.h"
#include "BasicWeapon.h"
#include "GreenMissile.h"
#include "Compositor.h"
#include "Ship.h"

BasicWeapon::BasicWeapon(Ship* ship) : Weapon(ship)
								, DefaultFireRate(15)
								, DefaultMissileDamage(15)
								, DefaultMissileSpeed(20)
								, DefaultMissileDistance(600)
{
	fireRate = DefaultFireRate;
	damage = DefaultMissileDamage;
	speed = DefaultMissileSpeed;
	distance = DefaultMissileDistance;
}

void BasicWeapon::FireMissile() 
{
	GreenMissile* missile = new GreenMissile(ships);
	missile->MiddlePoint(ships->MiddlePoint());
	missile->Direction(ships->Direction());
	missile->Distance(distance);
	missile->Damage(damage);
	missile->Speed(speed);
	missile->MoveOutOfRegion(ships);

	ships->Compositors->AddGameObject(missile);
}

BasicWeapon::~BasicWeapon(void)
{
}
