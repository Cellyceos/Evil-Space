#pragma once

#include "effect.h"

class GreenExplosion :
	public Effect
{
public:
	GreenExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~GreenExplosion(void);
};