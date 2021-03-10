#pragma once

#include "InteractiveObject.h"

class Universe : public InteractiveObject
{
public:
	static wstring& UniversePath;

	Universe(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual void CollidedWith(InteractiveObject *const) override;
	virtual ~Universe();
private:
	GDIBitmap* _image;
	static wstring starNameArr[];
};