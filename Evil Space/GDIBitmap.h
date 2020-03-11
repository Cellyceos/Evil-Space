#pragma once

class GDIBitmap
{
public:
	std::wstring Path;

	GDIBitmap(std::wstring);
	GDIBitmap(int, int);
	static GDIBitmap* FromFile(std::wstring);
	float GetWidth();
	float GetHeight();
	int GetFrameCount();
	Gdiplus::Bitmap* GetFrame(int);
	virtual ~GDIBitmap(void);	
private:
	static GDImageList& BufferedImage;
	Gdiplus::Bitmap* _image;
	Gdiplus::SizeF* size;
	GUID pDimensionIDs;

	void Create();
};