#pragma once
#include "enemy.h"
class Battlecruiser :
	public Enemy
{
public:
	Battlecruiser(Map*, Compositor*);
	virtual ~Battlecruiser(void);
private:
	virtual void Explode() override;
};

