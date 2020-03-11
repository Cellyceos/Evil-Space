#pragma once

class Map
{
public:
	static std::wstring& MapPath;
	Gdiplus::PointF& AreaPoint;
	static Gdiplus::RectF& CameraRect;

	Map();
	Gdiplus::Bitmap* GetCurrentImage();
	Gdiplus::RectF& MapRectangle();
	Gdiplus::PointF& MiddlePoint();
	float GetWidth();
	float GetHeight();
	void Draw(Gdiplus::Graphics*);
	virtual ~Map(void);
private:
	GDIBitmap* _image;
	Random* rnd;
	int frames;
	int currentFrame;
};