#pragma once

#include "Weapon.h"

class DoubleWeapon : public Weapon
{
public:
	DoubleWeapon(Ship*);
	virtual ~DoubleWeapon(void);
	virtual void FireMissile();

private:
	void CreateMissile(float);
};