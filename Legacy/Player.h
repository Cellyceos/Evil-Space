#pragma once

#include "ship.h"

class InteractiveObject;
class Compositor;
class GDIBitmap;
class Map;

class Player :
	public Ship
{
public:
	int Hits;
	int Misses;
	int MissilesFired;

	Player(Map*, Compositor*);
	virtual void Draw(Graphics*);
	virtual void Update();
	bool IsLeft();
	bool IsRight();
	bool IsUp();
	bool IsDown();
	bool IsSpace();
	void IsLeft(bool);
	void IsRight(bool);
	void IsUp(bool);
	void IsDown(bool);
	void IsSpace(bool);
	void ChangeShip(wstring, bool = true);
	int Shild();
	void Shild(int);
	virtual ~Player(void);
private:
	int shild;
	float yOffset;
	float xOffset;
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isSpace;

	virtual void CheckWrap() override;
	virtual void Explode() override;
	virtual void LowerHealth(int) override;
	void UpdateCoordinates(int, int, GameList&);
};