#include "StdAfx.h"
#include "InteractiveObject.h"
#include "Compositor.h"

InteractiveObject::InteractiveObject(Map* map, Compositor* compositor) : GameObject(map, compositor)
																	, points(0)
																	, health(0)
																	, damage(0) {}

void InteractiveObject::CheckCollision() 
{
	for (int i = 0; i < Compositors->Objects.Count(); i++)
	{
		InteractiveObject* obj = dynamic_cast<InteractiveObject*>(Compositors->Objects[i]);
		
		if (obj != this && Rects.IntersectsWith(obj->Rects))
		{
			obj->CollidedWith(this);
			return;
		}
	}

}

void InteractiveObject::MoveOutOfRegion(InteractiveObject* obj) 
{
	while (obj->Rects.IntersectsWith(Rects)) {
		Rects.X = (float)GetXCoordinates(Rects.X, direction, speed);
		Rects.Y = (float)GetYCoordinates(Rects.Y, direction, speed);
	}

	Rects.X = (float)GetXCoordinates(Rects.X, direction, obj->speed);
	Rects.Y = (float)GetYCoordinates(Rects.Y, direction, obj->speed);

}

void InteractiveObject::LowerHealth(int amount) 
{
	health -= amount;
}

void InteractiveObject::IncreaseHealth(int amount) 
{
	health += amount;
}

void InteractiveObject::Update() 
{
	if (IsAlive()) {
		GameObject::Update();
		CheckCollision();
	}
}

bool InteractiveObject::IsAlive()
{
	return health > 0;
}

int InteractiveObject::Health()
{
	return health;
}

void InteractiveObject::Health(int obj)
{
	health = obj;
}

int InteractiveObject::Damage()
{
	return damage;
}

void InteractiveObject::Damage(int obj)
{
	damage = obj;
}

int InteractiveObject::Points()
{
	return points;
}

void InteractiveObject::Points(int obj)
{
	points = obj;
}

InteractiveObject::~InteractiveObject(void)
{
}


