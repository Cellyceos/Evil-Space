#pragma once

#include "Bonus.h"

class HealthBonus :
	public Bonus
{
public:
	HealthBonus(Map*, Compositor*);
	virtual void GivePowerup(Player*) override;
	virtual void Draw(Graphics*) override;
	virtual ~HealthBonus(void);
};