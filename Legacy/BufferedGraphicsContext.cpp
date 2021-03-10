#include "stdafx.h"
#include "BufferedGraphics.h"
#include "BufferedGraphicsContext.h"

using namespace Gdiplus;

BufferedGraphicsContext::BufferedGraphicsContext() : busy(BUFFER_FREE)
													, buffer(NULL)
													, compatDC(NULL)
													, compatGraphics(NULL)
													, dib(NULL)
													, oldBitmap(NULL)
													, targetLoc(NULL)
													, virtualSize(NULL)
													, invalidateWhenFree(false)
													, maximumBuffer(NULL)
													, bufferSize(NULL)
{
	maximumBuffer = new Size(75 * 3, 32 * 3);
	bufferSize = new Size();
}

BufferedGraphics* BufferedGraphicsContext::Allocate(Graphics* targetGraphics, RectF& targetRect)
{
	if (ShouldUseTempManager(targetRect))
		return AllocBufferInTempManager(targetGraphics, NULL, targetRect);

	return AllocBuffer(targetGraphics, NULL, targetRect);
}

BufferedGraphics* BufferedGraphicsContext::Allocate(HDC targetDC, RectF& targetRect)
{
	if (ShouldUseTempManager(targetRect))
		return AllocBufferInTempManager(NULL, targetDC, targetRect);
	return AllocBuffer(NULL, targetDC, targetRect);
}

BufferedGraphics* BufferedGraphicsContext::AllocBuffer(Graphics* targetGraphics, HDC targetDC, RectF& targetRect)
{
	if (targetLoc == NULL)
		targetLoc = new Point((int)targetRect.X, (int)targetRect.Y);

	Graphics* graphics = NULL;

	try
	{
		if (targetGraphics != NULL)
		{
			HDC hdc = targetGraphics->GetHDC();
			try
			{
				graphics = CreateBuffer(hdc, -targetLoc->X, -targetLoc->Y, (int)targetRect.Width, (int)targetRect.Height);
			}
			catch (...)
			{}

			targetGraphics->ReleaseHDC(hdc);
		}
		else
			graphics = CreateBuffer(targetDC, -targetLoc->X, -targetLoc->Y, (int)targetRect.Width, (int)targetRect.Height);

		buffer = new BufferedGraphics(graphics, this, targetGraphics, targetDC, targetLoc, virtualSize);
	}
	catch (...)
	{
		busy = BUFFER_FREE;
		throw;
	}

	return buffer;
}

BufferedGraphics* BufferedGraphicsContext::AllocBufferInTempManager(Graphics* targetGraphics, HDC targetDC, RectF& targetRect)
{
	BufferedGraphicsContext* tempContext = NULL;
	BufferedGraphics* tempBuffer = NULL;

	try
	{
		tempContext = new BufferedGraphicsContext();

		if (tempContext != NULL)
		{
			tempBuffer = tempContext->AllocBuffer(targetGraphics, targetDC, targetRect);
			tempBuffer->DisposeContext = true;
		}
	}
	catch (...)
	{}

	if ((tempContext != NULL) && ((tempBuffer == NULL) || ((tempBuffer != NULL) && !tempBuffer->DisposeContext)))
	{
		tempContext->Dispose();
	}

	return tempBuffer;
}

bool BufferedGraphicsContext::bFillBitmapInfo(HDC hdc, HPALETTE hpal, BITMAPINFO* pbmi)
{
	HBITMAP hbm = NULL;
	bool bRet = false;

	try
	{
		hbm = ::CreateCompatibleBitmap(hdc, 1, 1);

		if (hbm == NULL)
			throw;

		pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

		::GetDIBits(hdc, hbm, 0, 0, NULL, pbmi, DIB_RGB_COLORS);

		if (pbmi->bmiHeader.biBitCount <= 8)
			bRet = bFillColorTable(hdc, hpal, pbmi);
		else
		{
			if (pbmi->bmiHeader.biCompression == BI_BITFIELDS)
				::GetDIBits(hdc, hbm, 0, pbmi->bmiHeader.biHeight, NULL, pbmi, DIB_RGB_COLORS);

			bRet = true;
		}

	}
	catch (...)	{}

	if (hbm != NULL)
	{
		::DeleteObject(hbm);
		hbm = NULL;
	}

	return bRet;
}

bool BufferedGraphicsContext::bFillColorTable(HDC hdc, HPALETTE hpal, BITMAPINFO* pbmi)
{
	bool bRet = false;
	PALETTEENTRY aj[256];
	int cColors = 0;

	RGBQUAD* prgb = pbmi->bmiColors;
	PALETTEENTRY* lppe = aj;

	cColors = 1 << pbmi->bmiHeader.biBitCount;

	if (cColors <= 256)
	{
		unsigned int palRet;
		HPALETTE palHalftone = NULL;

		if (hpal == NULL)
		{
			palHalftone = Graphics::GetHalftonePalette();
			palRet = ::GetPaletteEntries(palHalftone,0, cColors, aj);
		}
		else
		{
			palRet = ::GetPaletteEntries(hpal, 0, cColors, aj);
		}

		if (palRet != 0)
		{
			for (int i = 0; i < cColors; i++)
			{
				prgb[i].rgbRed = lppe[i].peRed;
				prgb[i].rgbGreen = lppe[i].peGreen;
				prgb[i].rgbBlue = lppe[i].peBlue;
				prgb[i].rgbReserved = 0;
			}

			bRet = true;
		}
	}
	
	return bRet;
}

Graphics* BufferedGraphicsContext::CreateBuffer(HDC src, int offsetX, int offsetY, int width, int height)
{
	busy = BUFFER_BUSY_DISPOSING;
	DisposeDC();
	busy = BUFFER_BUSY_PAINTING;

	compatDC = ::CreateCompatibleDC(src);

	if((width > bufferSize->Width) || (height > bufferSize->Height))
	{
		int optWidth = max(width, bufferSize->Width);
		int optHeight = max(height, bufferSize->Height);

		busy = BUFFER_BUSY_DISPOSING;
		DisposeBitmap();
		busy = BUFFER_BUSY_PAINTING;

		dib = CreateCompatibleDIB(src, NULL, optWidth, optHeight);

		delete bufferSize;
		bufferSize = new Size(optWidth, optHeight);
	}

	oldBitmap = ::SelectObject(compatDC, dib);

	if (compatGraphics != NULL)
	{
		delete compatGraphics;
		compatGraphics = NULL;
	}

	compatGraphics = Graphics::FromHDC(compatDC);
	compatGraphics->TranslateTransform((float) -targetLoc->X, (float) -targetLoc->Y);

	if (virtualSize == NULL)
		virtualSize = new Size(width, height);

	return compatGraphics;
}

HBITMAP BufferedGraphicsContext::CreateCompatibleDIB(HDC hdc, HPALETTE hpal, int ulWidth, int ulHeight)
{
	if (hdc == NULL)
		throw;

	HBITMAP hbmRet = NULL;
	BITMAPINFO* pbmi = new BITMAPINFO();

	switch (::GetObjectType(hdc))
	{
	case 3:
	case 4:
	case 10:
	case 12:
		break;
	default:
		throw;
	}

	if (bFillBitmapInfo(hdc, hpal, pbmi))
	{
		pbmi->bmiHeader.biWidth = ulWidth;
		pbmi->bmiHeader.biHeight = ulHeight;

		if (pbmi->bmiHeader.biCompression == BI_RGB)
			pbmi->bmiHeader.biSizeImage = 0;
		else if (pbmi->bmiHeader.biBitCount == 16)
			pbmi->bmiHeader.biSizeImage = ulWidth * ulHeight * 2;
		else if (pbmi->bmiHeader.biBitCount == 32)
			pbmi->bmiHeader.biSizeImage = ulWidth * ulHeight * 4;
		else
			pbmi->bmiHeader.biSizeImage = 0;

		pbmi->bmiHeader.biClrUsed = 0;
		pbmi->bmiHeader.biClrImportant = 0;
		hbmRet = ::CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, NULL, NULL, 0);

		if (hbmRet == NULL)
			throw;
	}

	return hbmRet;
}

void BufferedGraphicsContext::DisposeDC()
{
	if ((oldBitmap != NULL) && (compatDC != NULL))
	{
		::SelectObject(compatDC, oldBitmap);
		::DeleteObject(oldBitmap);
		oldBitmap = NULL;
	}
	if (compatDC != NULL)
	{
		::DeleteDC(compatDC);
		compatDC = NULL;
	}
}

void BufferedGraphicsContext::DisposeBitmap()
{
	if (dib != NULL)
	{
		::DeleteObject(dib);
		dib = NULL;
	}
}

void BufferedGraphicsContext::Dispose()
{
	int oldBusy = CompareExchange(&busy, BUFFER_BUSY_DISPOSING, BUFFER_FREE);

	if (compatGraphics != NULL)
	{
		delete compatGraphics;
		compatGraphics = NULL;
	}

	DisposeDC();
	DisposeBitmap();

	if (buffer != NULL)
	{
		delete buffer;
		buffer = NULL;
	}

	delete virtualSize;
	virtualSize = NULL;

	delete maximumBuffer;
	maximumBuffer = NULL;

	delete bufferSize;
	bufferSize = NULL;

	delete targetLoc;
	targetLoc = NULL;
}

void BufferedGraphicsContext::Invalidate()
{
	if (CompareExchange(&busy, BUFFER_BUSY_DISPOSING, BUFFER_FREE) == BUFFER_FREE)
	{
		Dispose();
		busy = BUFFER_FREE;
	}
	else
		invalidateWhenFree = true;
}

void BufferedGraphicsContext::ReleaseBuffer(BufferedGraphics* buffer)
{
	if (this->buffer == buffer)
		this->buffer = NULL;

	if (invalidateWhenFree)
	{
		busy = BUFFER_BUSY_DISPOSING;
		Dispose();
	}
	else
	{
		busy = BUFFER_BUSY_DISPOSING;
		DisposeDC();
	}
	
	busy = BUFFER_FREE;
}


int BufferedGraphicsContext::CompareExchange(BufferState* location1, int val, int comparand)
{
	BufferState old = *location1;
	if (*location1 == comparand)
		*location1 = (BufferState)val;

	return (int)old;
}

bool BufferedGraphicsContext::ShouldUseTempManager(RectF& targetBounds)
{
	return ((targetBounds.Width * targetBounds.Height) > (maximumBuffer->Width * maximumBuffer->Height));
}

Size* BufferedGraphicsContext::MaximumBuffer()
{
	return maximumBuffer;
}

void BufferedGraphicsContext::MaximumBuffer(Size* size)
{
	if ((size->Width <= 0) || (size->Height <= 0))
		throw;

	if ((size->Width * size->Height) < (maximumBuffer->Width * maximumBuffer->Height))
		Invalidate();
	else
		delete maximumBuffer;

	maximumBuffer = size;
}

BufferedGraphicsContext::~BufferedGraphicsContext()
{
	Dispose();
}
