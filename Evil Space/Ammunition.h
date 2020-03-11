#pragma once

#include "interactiveobject.h"

class Ship;

class Ammunition abstract:
	public InteractiveObject
{
public:
	static wstring& AmmunitionPath;
	const int DefaultHealth;
	const int DefaultPoints;

	Ammunition(Ship*);
	virtual void Explode() abstract;
	virtual void CollidedWith(InteractiveObject *const) override;
	virtual void LowerHealth(int) override;
	virtual void Update() override;
	virtual Ship* Ships();
	virtual int Distance();
	virtual void Distance(int);
	virtual ~Ammunition(void);
protected:
	enum MissileModes { Hits, Miss } ;
	GDIBitmap* _image;
	MissileModes mode;
	int distanceCount;
	int distance;
	Ship* ship;

	void Hit(InteractiveObject*);
};
