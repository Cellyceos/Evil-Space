#pragma once

#include "Bonus.h"

class InvisibilityBonus :
	public Bonus
{
public:
	InvisibilityBonus(Map*, Compositor*);
	virtual void GivePowerup(Player*) override;
	virtual void Draw(Graphics*) override;
	virtual ~InvisibilityBonus(void);
};