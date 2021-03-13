#include "StdAfx.h"
#include "Ship.h"
#include "Map.h"
#include "Compositor.h"
#include "Asteroid.h"
#include "BasicWeapon.h"
#include "Random.h"
#include "Ammunition.h"

wstring Ship::ShipPath = L"Ships\\";

Ship::Ship(Map* map, Compositor* compositor)
							: InteractiveObject(map,compositor)
							, MaxSpeed(6)
							, MinSpeed(-4)
							, OutOfControlTime(25)
							, ExplosionSpeed(15)
							, ExplosionAmount(75)
							, control(0)
							, weapon(NULL)
{
	weapon = new BasicWeapon(this);
}

void Ship::CollidedWith(InteractiveObject *const obj) 
{
	Ammunition* ammo = dynamic_cast<Ammunition*>(obj);

	if (ammo != NULL) {
		ammo->CollidedWith(this);
	}

}

bool Ship::Fire() 
{
	weapon->Fire();

	return true;
}

void Ship::LowerHealth(int amount) 
{
	InteractiveObject::LowerHealth(amount);

	if (!IsAlive()) {
		Explode();
	}
}

void Ship::Update() 
{
	InteractiveObject::Update();

	if (!InControl())
		control--;
}

bool Ship::IncreaseSpeed() 
{
	InteractiveObject::IncreaseSpeed();

	if (speed > MaxSpeed)
		speed = MaxSpeed;

	return true;
}

bool Ship::SlowSpeed() 
{
	InteractiveObject::SlowSpeed();

	if (speed < MinSpeed)
		speed = MinSpeed;

	return true;
}

bool Ship::MoveRight() 
{
	return InteractiveObject::MoveRight();
}

bool Ship::MoveLeft() 
{
	return InteractiveObject::MoveLeft();
}

bool Ship::InControl() 
{
	return control <= 0;
}

int Ship::Speed() 
{
	return InteractiveObject::Speed();
}

void Ship::Speed(int obj) 
{
	if (MaxSpeed < speed) {
		speed = MaxSpeed;
	}
	else if (speed < MinSpeed) {
		speed = MinSpeed;
	}
}

Weapon* Ship::Weapons() 
{
	return weapon;
}

void Ship::Weapons(Weapon* obj) 
{
	if (weapon != NULL)
	{
		delete weapon;
		weapon = NULL;
	}

	weapon = obj;
}


Ship::~Ship(void)
{
	if (weapon != NULL)
	{
		delete weapon;
		weapon = NULL;
	}
}
