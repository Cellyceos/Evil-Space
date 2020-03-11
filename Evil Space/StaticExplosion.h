#pragma once

#include "effect.h"

class StaticExplosion :
	public Effect
{
public:
	StaticExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~StaticExplosion(void);
};