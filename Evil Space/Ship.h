#pragma once

#include "InteractiveObject.h"

class Weapon;
class Map;
class Compositor;

class Ship abstract:
	public InteractiveObject
{
public:
	static wstring ShipPath;
	const int MaxSpeed;
	const int MinSpeed;
	const int OutOfControlTime;
	const int ExplosionSpeed;
	const int ExplosionAmount;

	Ship(Map*, Compositor*);
	virtual void CollidedWith(InteractiveObject *const) override;
	virtual void LowerHealth(int) override;
	virtual void Update() override;
	virtual bool IncreaseSpeed() override;
	virtual bool SlowSpeed() override;
	virtual bool MoveRight() override;
	virtual bool MoveLeft() override;
	virtual int Speed() override;
	virtual void Speed(int) override;
	virtual bool Fire();
	virtual bool InControl();
	virtual Weapon* Weapons();
	virtual void Weapons(Weapon*);
	virtual ~Ship(void);
protected:
	int control;
	Weapon* weapon;
	GDIBitmap* _image;

	virtual void Explode() abstract;
};	