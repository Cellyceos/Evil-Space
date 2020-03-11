#pragma once
#include "effect.h"

class AsteroidExplosion :
	public Effect
{
public:
	AsteroidExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~AsteroidExplosion(void);
};
