#pragma once

#include "effect.h"

class SmallExplosion :
	public Effect
{
public:
	SmallExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~SmallExplosion(void);
};