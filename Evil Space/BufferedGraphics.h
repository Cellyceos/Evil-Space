#pragma once

class BufferedGraphicsContext;

class BufferedGraphics
{
public:
	Gdiplus::Graphics* GraphicsSurface;
	bool DisposeContext;

	BufferedGraphics(Gdiplus::Graphics*, BufferedGraphicsContext*, Gdiplus::Graphics*, HDC, Gdiplus::Point*, Gdiplus::Size*);
	void Dispose();
	void Render();
	void Render(Gdiplus::Graphics*);
	void Render(HDC);
	~BufferedGraphics(void);
private:
	BufferedGraphicsContext* context;
	HDC targetDC;
	Gdiplus::Graphics* targetGraphics;
	Gdiplus::Point* targetLoc;
	Gdiplus::Size* virtualSize;

	void RenderInternal(HDC, BufferedGraphics*);
};
