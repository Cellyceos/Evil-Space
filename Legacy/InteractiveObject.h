#pragma once

#include "GameObject.h"

class InteractiveObject abstract:
	public GameObject
{
public:
	virtual int Health();
	virtual void Health(int);
	virtual int Damage();
	virtual void Damage(int);
	virtual int Points();
	virtual void Points(int);

	InteractiveObject(Map*, Compositor*);
	virtual ~InteractiveObject(void);
	virtual void MoveOutOfRegion(InteractiveObject*);
	virtual void CollidedWith(InteractiveObject *const) abstract;
	virtual void LowerHealth(int);
	virtual void IncreaseHealth(int);
	virtual void Update() override;
	bool IsAlive();
protected:
	int health;
	int damage;
	int points;
	void CheckCollision();
};