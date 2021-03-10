#pragma once

class BufferedGraphics;

class BufferedGraphicsContext 
{
public:
	BufferedGraphicsContext();
	BufferedGraphics* Allocate(Gdiplus::Graphics*, Gdiplus::RectF&);
	BufferedGraphics* Allocate(HDC, Gdiplus::RectF&);
	void Invalidate();
	Gdiplus::Size* MaximumBuffer();
	void MaximumBuffer(Gdiplus::Size*);
	void Dispose();
	void ReleaseBuffer(BufferedGraphics*);
	~BufferedGraphicsContext();

private:
	enum BufferState
	{
		BUFFER_FREE,
		BUFFER_BUSY_PAINTING,
		BUFFER_BUSY_DISPOSING
	};

	BufferedGraphics* buffer;
	Gdiplus::Size* bufferSize;
	BufferState busy;
	HDC compatDC;
	Gdiplus::Graphics* compatGraphics;
	HBITMAP dib;
	bool invalidateWhenFree;
	Gdiplus::Size* maximumBuffer;
	HGDIOBJ oldBitmap;
	Gdiplus::Point* targetLoc;
	Gdiplus::Size* virtualSize;

	BufferedGraphics* AllocBuffer(Gdiplus::Graphics*, HDC, Gdiplus::RectF&);
	BufferedGraphics* AllocBufferInTempManager(Gdiplus::Graphics*, HDC, Gdiplus::RectF&);
	bool bFillBitmapInfo(HDC, HPALETTE, BITMAPINFO*);
	bool bFillColorTable(HDC, HPALETTE, BITMAPINFO*);
	Gdiplus::Graphics* CreateBuffer(HDC, int, int, int, int);
	HBITMAP CreateCompatibleDIB(HDC, HPALETTE, int, int);
	void DisposeBitmap();
	void DisposeDC();
	bool ShouldUseTempManager(Gdiplus::RectF&);
	int CompareExchange(BufferState*, int, int);
};
