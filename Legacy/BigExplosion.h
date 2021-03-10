#pragma once

#include "effect.h"

class BigExplosion :
	public Effect
{
public:
	BigExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~BigExplosion(void);
};