#pragma once

#include "GameObject.h"

class Effect abstract: public GameObject
{
public:
	static wstring EffectPath;

	Effect(Map*, Compositor*);
	bool IsDone();
	virtual void Update();
	virtual ~Effect(void);
protected:
	GDIBitmap* _image;
};