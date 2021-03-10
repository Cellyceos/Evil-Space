#pragma once

#include "Ammunition.h"

class GreenMissile :
	public Ammunition
{
public:
	GreenMissile(Ship*);
	virtual void Explode() override;
	virtual void Draw(Graphics*) override;
	virtual ~GreenMissile(void);
};
