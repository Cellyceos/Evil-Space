#pragma once

#include "Bonus.h"

class PowerBonus :
	public Bonus
{
public:
	PowerBonus(Map*, Compositor*);
	virtual void GivePowerup(Player*) override;
	virtual void Draw(Graphics*) override;
	int GivenPower();
	void GivenPower(int);
	virtual ~PowerBonus(void);
private:
	int powerProvided;
};