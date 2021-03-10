#include "stdafx.h"
#include "BufferedGraphics.h"
#include "BufferedGraphicsContext.h"

using namespace Gdiplus;

BufferedGraphics::BufferedGraphics(Graphics* abufferedGraphicsSurface
								   , BufferedGraphicsContext* acontext
								   , Graphics* atargetGraphics
								   , HDC atargetDC
								   , Point* atargetLoc
								   , Size* avirtualSize)
								   : DisposeContext(false)
								   , context(acontext)
								   , GraphicsSurface(abufferedGraphicsSurface)
								   , targetDC(atargetDC)
								   , targetGraphics(atargetGraphics)
								   , targetLoc(atargetLoc)
								   , virtualSize(avirtualSize) {}

void BufferedGraphics::Render()
{
    if (targetGraphics != NULL)
    {
        Render(targetGraphics);
    }
    else
    {
        RenderInternal(targetDC, this);
    }
}

void BufferedGraphics::Render(Graphics* g)
{
    if (g != NULL)
    {
        HDC hdc = g->GetHDC();

		RenderInternal(hdc, this);
		
		g->ReleaseHDC(hdc);
    }
}

void BufferedGraphics::Render(HDC hdc)
{
	RenderInternal(hdc, this);
}

void BufferedGraphics::RenderInternal(HDC refTargetDC, BufferedGraphics* buffer)
{
    HDC hdc = buffer->GraphicsSurface->GetHDC();

	BitBlt(refTargetDC, targetLoc->X, targetLoc->Y, virtualSize->Width, virtualSize->Height, hdc, 0, 0, SRCCOPY);

	buffer->GraphicsSurface->ReleaseHDC(hdc);
}

void BufferedGraphics::Dispose()
{
	if (context != NULL)
	{
		context->ReleaseBuffer(this);
		if (DisposeContext)
		{
			delete context;
			context = NULL;
		}
	}

	if (targetGraphics != NULL)
	{
		delete targetGraphics;
		targetGraphics = NULL;
	}

}

BufferedGraphics::~BufferedGraphics(void)
{
	Dispose();
}
