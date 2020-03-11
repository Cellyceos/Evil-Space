#pragma once

#include "interactiveobject.h"

class Player;

class Bonus abstract:
	public InteractiveObject
{
public:
	static wstring& BonusPath;
	const int DefaultHealth;
	const int MaxTime;
	const int DefaultPoints;

	virtual void GivePowerup(Player*);
	virtual void CollidedWith(InteractiveObject *const) override;
	virtual void Update() override;
	virtual ~Bonus(void);
protected:
	GDIBitmap* _image;
	int time;
	Bonus(Map*, Compositor*);
};