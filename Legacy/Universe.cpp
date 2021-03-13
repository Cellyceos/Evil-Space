#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "Universe.h"
#include "Asteroid.h"
#include "GDIBitmap.h"
#include "Compositor.h"
#include "BigExplosion.h"
#include "GameTicks.h"

wstring& Universe::UniversePath = *new wstring(L"Stars\\");
wstring Universe::starNameArr[] = { L"Star00.tif", L"Star01.tif", L"Star02.tif", 
								L"Star03.tif", L"Star04.tif", L"Star05.tif", 
								L"Star06.tif", L"Star07.tif", L"Star08.tif"};

Universe::Universe(Map* map, Compositor* compositor) : InteractiveObject(map, compositor)
											, _image(NULL)
{
	wstring name = starNameArr[Randomizer.Next(0, 9)];
	_image = new GDIBitmap(ContentPath + UniversePath + name);
	health = 6000;
	damage = 6000;
	frames = _image->GetFrameCount() - 1;
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	Rects.X = 0.0f;
	Rects.Y = 0.0f;
}

void Universe::CollidedWith(InteractiveObject *const obj) 
{
	obj->LowerHealth(damage);
}

void Universe::Draw(Graphics* g)
{
	GameObject::Draw(g, _image->GetFrame(currentFrame));
}

Universe::~Universe(void)
{
	if (_image != NULL)
	{
		delete _image;
		_image = NULL;
	}
}
