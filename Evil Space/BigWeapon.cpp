#include "StdAfx.h"
#include "BigWeapon.h"
#include "BigMissile.h"
#include "Compositor.h"
#include "Ship.h"

BigWeapon::BigWeapon(Ship* ship) : Weapon(ship)
							, DefaultFireRate(30)
							, DefaultMissileDamage(150)
							, DefaultMissileSpeed(10)
							, DefaultMissileDistance(800)
{
	fireRate = DefaultFireRate;
	damage = DefaultMissileDamage;
	speed = DefaultMissileSpeed;
	distance = DefaultMissileDistance;
}

void BigWeapon::FireMissile() 
{
	BigMissile* missile = new BigMissile(ships);
	missile->MiddlePoint(ships->MiddlePoint());
	missile->Direction(ships->Direction());
	missile->Distance(distance);
	missile->Damage(damage);
	missile->Speed(speed);
	missile->MoveOutOfRegion(ships);

	ships->Compositors->AddGameObject(missile);
}

BigWeapon::~BigWeapon(void)
{
}
