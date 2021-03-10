#include "StdAfx.h"
#include "Asteroid.h"
#include "Map.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "AsteroidExplosion.h"
#include "Bonus.h"
#include "HealthBonus.h"
#include "PowerBonus.h"
#include "ShieldBonus.h"
#include "Ship.h"
#include "Random.h"
#include "Ammunition.h"

wstring Asteroid::AsteroidPath = L"Asteroid\\";
wstring Asteroid::AsteroidNameArr[] = { L"00.tif", L"01.tif", L"02.tif", L"03.tif",
										L"04.tif", L"05.tif", L"06.tif", L"07.tif", 
										L"08.tif", L"09.tif", L"10.tif", L"11.tif", 
										L"Blue01.tif", L"Blue02.tif", L"Blue03.tif", L"Blue01.tif" };

Asteroid::Asteroid(Map* map, Compositor* compositor) : InteractiveObject(map, compositor), _image(NULL)
{
	wstring name = AsteroidNameArr[Randomizer.Next(0, 16)];

	_image = GDIBitmap::FromFile(ContentPath + AsteroidPath + name);
	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount() - 1;
	health = 20;
	damage = 40;	
	points = 10;

	speed = Randomizer.Next(1, 5);
	direction = Randomizer.Next(0.0f, MaxDirections);

	RectF& rect = Maps->MapRectangle();

	do {
		Rects.X = Randomizer.Next(0.0f, rect.Width + 1.0f);
		Rects.Y = Randomizer.Next(0.0f, rect.Height + 1.0f);
	} while (rect.Contains(MiddlePoint()));

	delete &rect;
}

void Asteroid::Explode() 
{
	CreatePowerup();

	AsteroidExplosion* explosion = new AsteroidExplosion(Maps, Compositors);
	
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

void Asteroid::CreatePowerup() 
{
	int percent = Randomizer.Next(0, 101);

	Bonus* powerup;

	if (80 < percent) {
		powerup = new PowerBonus(Maps, Compositors);
	}
	else if (30 < percent) {
		powerup = new HealthBonus(Maps, Compositors);
	}
	else if (0 < percent) {
		powerup = new ShieldBonus(Maps, Compositors);
	}

	powerup->MiddlePoint(MiddlePoint());
	Compositors->AddGameObject(powerup);

}

void Asteroid::Draw(Graphics* g) 
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}

void Asteroid::CollidedWith(InteractiveObject *const obj) 
{
	Ammunition* ammo = dynamic_cast<Ammunition*>(obj);

	if (ammo != NULL) {
		ammo->CollidedWith(this);
	}

	Ship* ship = dynamic_cast<Ship*>(obj);

	if (ship != NULL || typeid(*obj) == typeid(Asteroid)) {
		obj->LowerHealth(damage);

		LowerHealth(obj->Damage());
	}
}

void Asteroid::LowerHealth(int amount) 
{
	InteractiveObject::LowerHealth(amount);

	if (!IsAlive()) {
		Explode();
	}
}

void Asteroid::Update() 
{
	InteractiveObject::Update();
}

Asteroid::~Asteroid(void)
{
}
