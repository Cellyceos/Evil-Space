#pragma once

using namespace std;
using namespace Gdiplus;

class Compositor;
class GDIBitmap;
class Random;
class Map;

class GameObject abstract
{
public:
	static wstring& ContentPath;
	const float MaxDirections;
	Compositor* Compositors;
	Map* Maps;
	RectF Rects;

	virtual void Draw(Graphics*) abstract;
	virtual bool MoveRight();
	virtual bool MoveLeft();
	virtual bool IncreaseSpeed();
	virtual bool SlowSpeed();
	virtual void Update();
	virtual int Speed();
	virtual void Speed(int);
	virtual float Direction();
	virtual void Direction(float);
	virtual int Width();
	virtual int Height();
	virtual float X();
	virtual void X(float);
	virtual float Y();
	virtual void Y(float);
	virtual PointF& MiddlePoint();
	virtual void MiddlePoint(PointF&);
	virtual ~GameObject();

protected:
	static Random& Randomizer;
	int frames;
	int currentFrame;
	float direction;
	float rotation;
	int speed;

	GameObject(Map*, Compositor*);
	double GetXCoordinates(float, float, int);
	double GetYCoordinates(float, float, int);
	Bitmap* RotateImage(Bitmap*);
	void Draw(Graphics*, Bitmap*);
	virtual void CheckWrap();
};