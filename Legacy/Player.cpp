#include "StdAfx.h"
#include "Player.h"
#include "GameObject.h"
#include "Compositor.h"
#include "GDIBitmap.h"
#include "DoubleWeapon.h"
#include "Weapon.h"
#include "Effect.h"
#include "Main.h"
#include "Map.h"
#include "SmallExplosion.h"

Player::Player(Map* map, Compositor* compositor) : Ship(map, compositor)
										, Hits(0)
										, Misses(0)
										, MissilesFired(0)
										, shild(2000)
										, xOffset(0.0f)
										, yOffset(0.0f)
										, isLeft(false)
										, isRight(false)
										, isUp(false)
										, isDown(false)
										, isSpace(false)
{
	ChangeShip(L"As.tif", false);
	health = 500;
	damage = 20;
	Rects.X = Map::CameraRect.Width / 2 - Rects.Width / 2;;
	Rects.Y = Map::CameraRect.Height / 2 - Rects.Height / 2;
	Weapons(new DoubleWeapon(this));
}

void Player::Draw(Graphics* g) 
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}

void Player::Explode() 
{
	SmallExplosion* explosion = new SmallExplosion(Maps, Compositors);
	explosion->MiddlePoint(MiddlePoint());

	Compositors->AddGameObject(explosion);
}

void Player::LowerHealth(int amount)
{
	if (shild > 0) {
		shild -= amount;

		if (shild < 0){
			Ship::LowerHealth(abs(shild));
			shild = 0;
		}
	}
	else
		Ship::LowerHealth(amount); 

	if (!IsAlive()) 
		Program::GameOver();
}

void Player::UpdateCoordinates(int x, int y, GameList& list)
{
	for (int i = 0; i < list.Count(); i++)
		if (list[i] != this)
		{
			list[i]->Rects.X += x;
			list[i]->Rects.Y += y;
		}
}

void Player::CheckWrap()
{
	int aSpeed = abs(speed);
	int x = 0;
	int y = 0;

	if (Maps->CameraRect.Height <= (Rects.Y + Rects.Height*yOffset)) {
		Maps->AreaPoint.Y += aSpeed;

		y = -aSpeed;

		if (Maps->AreaPoint.Y >= (Maps->GetHeight() - Maps->CameraRect.Height)) {
			Maps->AreaPoint.Y = Maps->GetHeight() - Maps->CameraRect.Height;
			yOffset = yOffset <= 1 ? 1 : yOffset - 0.01f*aSpeed;
			y = 0;
		}

		Rects.Y = Maps->CameraRect.Height - Rects.Height*yOffset;
	}
	else if ((Rects.Y - Rects.Height*yOffset) <= 0) {
		Maps->AreaPoint.Y -= aSpeed;

		y = aSpeed;

		if (Maps->AreaPoint.Y <= 0) {
			Maps->AreaPoint.Y = 0;
			yOffset = yOffset <= 0 ? 0 : yOffset - 0.01f*aSpeed;
			y = 0;
		}

		Rects.Y = Rects.Height*yOffset;
	}
	else
		yOffset = yOffset >= 3 ? 3 : yOffset + 0.01f*aSpeed;

	if (Maps->CameraRect.Width < (Rects.X + Rects.Width*xOffset)) {
		Maps->AreaPoint.X += aSpeed;

		x = -aSpeed;

		if (Maps->AreaPoint.X >= Maps->GetWidth() - Maps->CameraRect.Width) {
			Maps->AreaPoint.X = Maps->GetWidth() - Maps->CameraRect.Width;
			xOffset = xOffset <= 1 ? 1 : xOffset - 0.01f*aSpeed;
			x = 0;
		}

		Rects.X = Maps->CameraRect.Width - Rects.Width*xOffset;
	}
	else if ((Rects.X - Rects.Width*xOffset) < 0) {
		Maps->AreaPoint.X -= aSpeed;

		x = aSpeed;

		if (Maps->AreaPoint.X <= 0){
			Maps->AreaPoint.X = 0;
			xOffset = xOffset <= 0 ? 0 : xOffset - 0.01f*aSpeed;
			x = 0;
		}

		Rects.X = Rects.Width*xOffset;
	}
	else
		xOffset = xOffset >= 3 ? 3 : xOffset + 0.01f*aSpeed;

	if ((x != 0) || (y != 0)) {
		UpdateCoordinates(x, y, Compositors->Ammunitions);
		UpdateCoordinates(x, y, Compositors->Objects);
		UpdateCoordinates(x, y, Compositors->Effects);
	}
}

void Player::Update()
{
	if (isLeft)
		MoveLeft();

	if (isRight)
		MoveRight();

	if (isUp)
		IncreaseSpeed();

	if (isDown)
		SlowSpeed();

	if (isSpace)
		Fire();

	InteractiveObject::Update();
}

bool Player::IsLeft()
{
	return isLeft;
}

bool Player::IsRight()
{
	return isRight;
}

bool Player::IsUp()
{
	return isUp;
}

bool Player::IsDown()
{
	return isDown;
}

bool Player::IsSpace()
{
	return isSpace;
}

void Player::IsLeft(bool obj)
{
	isLeft = obj;
}

void Player::IsRight(bool obj)
{
	isRight = obj;
}

void Player::IsUp(bool obj)
{
	isUp = obj;
}

void Player::IsDown(bool obj)
{
	isDown = obj;
}

void Player::IsSpace(bool obj)
{
	if (!obj)
		weapon->Reload();

	isSpace = obj;
}

void Player::ChangeShip(wstring name, bool delimg)
{
	if (delimg && _image != NULL)
	{
		delete _image;
		_image = NULL;
	}

	_image = new GDIBitmap(ContentPath + ShipPath + name);

	Rects.Width = _image->GetWidth();
	Rects.Height = _image->GetHeight();
	frames = _image->GetFrameCount();
}

int Player::Shild()
{
	return shild;
}

void Player::Shild(int obj)
{
	shild = obj;
}

Player::~Player(void)
{
	if (_image != NULL)
	{
		delete _image;
		_image = NULL;
	}
}
