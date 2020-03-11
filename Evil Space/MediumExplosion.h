#pragma once
#include "effect.h"
class MediumExplosion :
	public Effect
{
public:
	MediumExplosion(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual ~MediumExplosion(void);
};

