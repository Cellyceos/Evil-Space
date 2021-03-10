#pragma once

#include "Ammunition.h"

class BlueMissile :
	public Ammunition
{
public:
	BlueMissile(Ship*);
	virtual void Explode() override;
	virtual void Draw(Graphics*) override;
	virtual ~BlueMissile(void);
};