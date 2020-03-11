#pragma once

#include "Bonus.h"

class BatteryBonus :
	public Bonus
{
public:
	BatteryBonus(Map*, Compositor*);
	virtual void GivePowerup(Player*) override;
	virtual void Draw(Graphics*) override;
	virtual ~BatteryBonus(void);
};