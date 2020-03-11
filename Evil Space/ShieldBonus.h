#pragma once

#include "Bonus.h"

class ShieldBonus :
	public Bonus
{
public:
	ShieldBonus(Map*, Compositor*);
	int GivenShield();
	void GivenShield(int);
	virtual void GivePowerup(Player*) override;
	virtual void Draw(Graphics*) override;
	virtual ~ShieldBonus(void);
private:
	int shieldProvided;

};