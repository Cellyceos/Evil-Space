#pragma once
#include "enemy.h"
class Cruisers :
	public Enemy
{
public:
	Cruisers(Map*, Compositor*);
	virtual ~Cruisers(void);
private:
	virtual void Explode() override;
};

