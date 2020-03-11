#pragma once

#include "effect.h"

class BlueExplosion :
	public Effect
{
public:
	BlueExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~BlueExplosion(void);
};