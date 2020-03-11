#include "StdAfx.h"
#include "GDIBitmap.h"

using namespace std;
using namespace Gdiplus;

GDImageList& GDIBitmap::BufferedImage = *new GDImageList();

GDIBitmap::GDIBitmap(wstring obj) : _image(NULL), Path(obj)
{
	_image = Bitmap::FromFile(obj.c_str());

	if (_image != NULL)
		Create();
}

GDIBitmap::GDIBitmap(int width, int height) : _image(NULL), Path(NULL)
{
	_image = new Bitmap(width, height);
	Create();
}

void GDIBitmap::Create()
{
	_image->GetFrameDimensionsList(&pDimensionIDs, 1);
	size = new SizeF((float)_image->GetWidth(), (float)_image->GetHeight());
}

GDIBitmap* GDIBitmap::FromFile(wstring obj)
{
	if (BufferedImage.Count() > 0)
		for (int i = 0; i < BufferedImage.Count(); i++)
			if (BufferedImage[i]->Path == obj)
				return BufferedImage[i];

	GDIBitmap* image = new GDIBitmap(obj);

	if (image != NULL)
	{
		int num = BufferedImage.Add(image);
		return BufferedImage[num];
	}

	return NULL;
}

int GDIBitmap::GetFrameCount()
{
	return _image->GetFrameCount(&pDimensionIDs) - 1;
}

Bitmap* GDIBitmap::GetFrame(int frame)
{
	if (_image->SelectActiveFrame(&pDimensionIDs, frame) == Ok)
		return _image;
	
	return NULL;
}

float GDIBitmap::GetWidth()
{
	return size->Width;
}

float GDIBitmap::GetHeight()
{
	return size->Height;
}

GDIBitmap::~GDIBitmap(void)
{
	if (_image != NULL)
	{
		delete _image;
		_image = NULL;
	}

	if (size != NULL)
	{
		delete size;
		size = NULL;
	}
}
