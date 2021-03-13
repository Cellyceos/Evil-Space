#include "stdafx.h"
#include "GameObject.h"
#include "GDIBitmap.h"
#include "Random.h"
#include "Map.h"

Random& GameObject::Randomizer = *new Random(GetTickCount()&2147483647);

wstring& GameObject::ContentPath = *new wstring(L"Assets\\");

GameObject::GameObject(Map *map, Compositor *compositor): MaxDirections(359.99f)
													, Maps(map)
													, Compositors(compositor)
													, direction(0)
													, speed(0)
													, currentFrame(0)
													, frames(0)
													, rotation(0){}

double GameObject::GetXCoordinates(float x, float direction, int distance) 
{
	return x + sin(direction * M_PI / 180.0f) * distance;
}

double GameObject::GetYCoordinates(float y, float direction, int distance) 
{
	return y + cos(direction * M_PI / 180.0f) * distance * (-1);
}

Bitmap* GameObject::RotateImage(Bitmap* src) try
{
	Bitmap* newBitmap = NULL;

	newBitmap = new Bitmap(src->GetWidth()+25, src->GetHeight()+25);
	Graphics m(newBitmap);

	m.TranslateTransform((float)src->GetWidth() / 2, (float)src->GetHeight() / 2);
	m.RotateTransform(rotation + direction);
	m.TranslateTransform(-(float)src->GetWidth() / 2, -(float)src->GetHeight() / 2);
	m.DrawImage(src, 0, 0);

	return newBitmap;
}
catch (...)
{
	return NULL;
};

void GameObject::Draw(Graphics* g, Bitmap* image) try
{
	if (!Maps->CameraRect.IntersectsWith(Rects))
		return;

	g->DrawImage(image, Rects.X, Rects.Y, Rects.Width, Rects.Height);
}
catch (...)
{
	int a;

	a = 5;
	
};

void GameObject::CheckWrap() 
{
 	if (Maps->CameraRect.IntersectsWith(Rects))
 		return;

	if (Rects.Y < -(Rects.Height + speed)) {
		Rects.Y = Maps->GetHeight() - 1;
	}
	else if (Maps->GetHeight() < Rects.Y) {
		Rects.Y = 1.0f - Rects.Height;
	}

	if (Rects.X < -(Rects.Width + speed)) {
		Rects.X = Maps->GetWidth() - 1;
	}
	else if (Maps->GetWidth() < Rects.X) {
		Rects.X = 1.0f - Rects.Width;
	}
}

bool GameObject::MoveRight()
{
	direction += 2.5f;

	if (direction > MaxDirections)
		direction = direction - MaxDirections;

	return true;
}

bool GameObject::MoveLeft()
{
	direction -= 2.5f;

	if (direction < 0.0f)
		direction = direction + MaxDirections;

	return true;
}

bool GameObject::IncreaseSpeed()
{
	speed++;

	return true;
}

bool GameObject::SlowSpeed()
{
	speed--;

	return true;
}

void GameObject::Update() 
{
	Rects.X = (float)GetXCoordinates(Rects.X, direction, speed);
	Rects.Y = (float)GetYCoordinates(Rects.Y, direction, speed);

	CheckWrap();

	currentFrame++;

	if (currentFrame > frames)
		currentFrame = 0;
}

int GameObject::Speed()
{
	return speed;
}

void GameObject::Speed(int obj)
{
	speed = obj;
}

float GameObject::Direction()
{
	return direction;
}

void GameObject::Direction(float obj)
{
	direction = obj;

	if (MaxDirections < direction) {
		direction = 0.0f;
	}
	else if (direction < 0.0f) {
		direction = MaxDirections;
	}
}

int GameObject::Width()
{
	return (int)Rects.Width;
}

int GameObject::Height()
{
	return (int)Rects.Height;
}

float GameObject::X()
{
	return Rects.X;
}

void GameObject::X(float obj)
{
	Rects.X = obj;
}

float GameObject::Y()
{
	return Rects.Y;
}

void GameObject::Y(float obj)
{
	Rects.Y = obj;
}

PointF& GameObject::MiddlePoint()
{
	return *new PointF(Rects.X  + Rects.Width / 2.0f, Rects.Y + Rects.Height / 2.0f);
}

void GameObject::MiddlePoint(PointF& obj)
{
	Rects.X = obj.X - Rects.Width / 2.0f;
	Rects.Y = obj.Y - Rects.Height / 2.0f;

	delete &obj;
}

GameObject::~GameObject()
{

}
