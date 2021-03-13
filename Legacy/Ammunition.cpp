#include "StdAfx.h"
#include "Ammunition.h"
#include "Compositor.h"
#include "Map.h"
#include "Bonus.h"
#include "Player.h"
#include "Ship.h"
#include "GDIBitmap.h"

wstring& Ammunition::AmmunitionPath = *new wstring(L"Ammunitions\\");

Ammunition::Ammunition(Ship* aship) : InteractiveObject(aship->Maps, aship->Compositors)
						, DefaultHealth(1)
						, DefaultPoints(2)
						, mode(Miss)
						, distanceCount(0)
						, distance(0)
						, ship(aship)
						, _image(NULL)
{
	health = DefaultHealth;
	points = DefaultPoints;
}

void Ammunition::Hit(InteractiveObject* obj)
{
	if (typeid(*obj) == typeid(Bonus)) {
		return;
	}

	mode = Hits;

	if (obj != ship) {
		obj->LowerHealth(damage);

		LowerHealth(damage);

		Player* player = dynamic_cast<Player*>(ship);
		if (player != NULL && !obj->IsAlive()) {
			player->Points(player->Points() + obj->Points());
		}
	}
}

void Ammunition::CollidedWith(InteractiveObject *const obj) 
{
	Hit(obj);
}

void Ammunition::LowerHealth(int amount) 
{
	InteractiveObject::LowerHealth(amount);

	if (!IsAlive()) {
		Explode();
	}
}

void Ammunition::Update() 
{
	InteractiveObject::Update();

	distanceCount += speed;

	if (distance < distanceCount) {
 		LowerHealth(damage);
	}
}

Ship* Ammunition::Ships() 
{
	return ship;
}

int Ammunition::Distance()
{
	return distance;
}

void Ammunition::Distance(int obj)
{
	distance = obj;
}

Ammunition::~Ammunition(void)
{
}
