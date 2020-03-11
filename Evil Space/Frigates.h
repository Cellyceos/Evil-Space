#pragma once

#include "enemy.h"

class Frigates :
	public Enemy
{
public:
	Frigates(Map*, Compositor*);
	virtual ~Frigates(void);
private:
	virtual void Explode() override;
};

