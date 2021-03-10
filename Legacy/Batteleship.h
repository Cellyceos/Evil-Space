#pragma once
#include "enemy.h"
class Batteleship :
	public Enemy
{
public:
	Batteleship(Map*, Compositor*);
	~Batteleship(void);
private:
	virtual void Explode() override;
};

