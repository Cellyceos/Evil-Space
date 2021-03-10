#pragma once

#include "Ammunition.h"

class BigMissile :
	public Ammunition
{
public:
	const int DefaultWidth;
	const int DefaultHeight;
	const int Radius;

	BigMissile(Ship*);
	virtual void Explode() override;
	virtual void Draw(Graphics*) override;
	virtual ~BigMissile(void);
private:
	void TrackObject();
};