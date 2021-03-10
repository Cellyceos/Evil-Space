#pragma once

#include "weapon.h"

class BigWeapon :
	public Weapon
{
public:
	int DefaultFireRate;
	int DefaultMissileDamage;
	int DefaultMissileSpeed;
	int DefaultMissileDistance;

	BigWeapon(Ship*);
	virtual void FireMissile() override;
	virtual ~BigWeapon(void);
};