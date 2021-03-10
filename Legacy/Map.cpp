#include "stdafx.h"
#include "Map.h"
#include "Random.h"
#include "GDIBitmap.h"
#include "GameObject.h"

wstring& Map::MapPath = *new wstring(L"Backgraund\\");
RectF& Map::CameraRect = *new RectF(0, 0, 1024, 768);

Map::Map() : rnd(NULL), _image(NULL), AreaPoint(*new PointF(0.0f, 0.0f))
{
	rnd = new Random();
	_image = new GDIBitmap(GameObject::ContentPath + MapPath + L"bg.tif");
	frames = _image->GetFrameCount();
	currentFrame = rnd->Next(1, frames);
}

void Map::Draw(Graphics* g)
{
	g->DrawImage(GetCurrentImage(), CameraRect.X, CameraRect.Y, AreaPoint.X, AreaPoint.Y, CameraRect.Width, CameraRect.Height, UnitPixel);
}

Bitmap* Map::GetCurrentImage()
{
	return _image->GetFrame(currentFrame);
}

float Map::GetHeight()
{
	return _image->GetHeight();
}

float Map::GetWidth()
{
	return _image->GetWidth();
}

RectF& Map::MapRectangle()
{
	RectF& rect = *new RectF(0.0f, 0.0f, GetWidth(), GetHeight());
	return rect;
}

PointF& Map::MiddlePoint()
{
	return *new PointF(0.0f  + _image->GetWidth() / 2, 0.0f + _image->GetHeight() / 2);
}

Map::~Map(void)
{
	if (_image != NULL)
	{
		delete _image;
		_image = NULL;
	}

	if (rnd != NULL)
	{
		delete rnd;
		rnd = NULL;
	}

	delete &CameraRect;
	delete &AreaPoint;
	delete &MapPath;
}