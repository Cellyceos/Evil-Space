#pragma once

class Ship;

class Weapon
{
public:
	Weapon(Ship*);
	virtual void Fire();
	virtual void FireMissile() abstract ;
	virtual void Reload();
	virtual void Damage(int);
	virtual ~Weapon(void);

protected:
	Ship* ships;
	int distance;
	int damage;
	int speed;
	int fireRate;
	int fireCount;
};