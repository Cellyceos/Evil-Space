#pragma once

#include "weapon.h"

class BasicWeapon :
	public Weapon
{
public:
	const int DefaultFireRate;
	const int DefaultMissileDamage;
	const int DefaultMissileSpeed;
	const int DefaultMissileDistance;

	BasicWeapon(Ship*);
 	virtual void FireMissile() override;
	virtual ~BasicWeapon(void);
};