#pragma once

#include "interactiveobject.h"

class Asteroid :
	public InteractiveObject
{
public:
	static wstring AsteroidPath;
	static wstring AsteroidNameArr[];
	Asteroid(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual void CollidedWith(InteractiveObject *const) override;
	virtual void LowerHealth(int) override;
	virtual void Update() override;
	virtual ~Asteroid(void);
private:
	GDIBitmap* _image;

	void Explode();
	void CreatePowerup();
};