#include "stdafx.h"
#include "ImageButton.h"
#include "GDIBitmap.h"
#include "GameObject.h"

using namespace std;
using namespace Gdiplus;

ImageButton::ImageButton(int x, int y, wstring path, int width, int height) : _image(NULL), TargetLocatiaon(NULL), TargetSize(NULL), OnClick(NULL), status(Default), Enabled(false)
{
	_image = new GDIBitmap(GameObject::ContentPath + L"Button\\" + path);

	int nWidth = width > 0 ? width : (int)_image->GetWidth();
	int nHeight = height > 0 ? height : (int)_image->GetHeight();

	TargetSize = new Size(nWidth, nHeight);
	TargetLocatiaon = new Point(x, y);
}

Status ImageButton::OnMauseDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if ( (wParam == MK_LBUTTON) && CheckIntersection(lParam) && Enabled)
	{
		status = Active;

		if (OnClick != NULL)
			OnClick(hWnd, wParam, lParam);

		return Aborted;
	}

	return Ok;
}

void ImageButton::OnMauseUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (CheckIntersection(lParam) && Enabled)
		status = Selected;
	else
		status = Default;
}

bool ImageButton::CheckIntersection(LPARAM lParam)
{
	int x = (int)LOWORD(lParam); 
	int y = (int)HIWORD(lParam);

	return x > TargetLocatiaon->X && x < TargetLocatiaon->X + TargetSize->Width && y > TargetLocatiaon->Y && y < TargetLocatiaon->Y + TargetSize->Height;
}

void ImageButton::OnMauseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (CheckIntersection(lParam))
		OnMouseEnter();
	else
		OnMouseLeave();
}

void ImageButton::OnMouseEnter()
{
	Enabled = true;
	status = Selected;
}

void ImageButton::OnMouseLeave()
{
	Enabled = false;
	status = Default;
}

void ImageButton::Draw(Graphics* g)
{
	if (Visible)
		g->DrawImage(_image->GetFrame(status), TargetLocatiaon->X, TargetLocatiaon->Y, TargetSize->Width, TargetSize->Height);
}

ImageButton::~ImageButton(void)
{
	OnClick = NULL;

	if (TargetLocatiaon != NULL)
	{
		delete TargetLocatiaon;
		TargetLocatiaon = NULL;
	}

	if (TargetSize != NULL)
	{
		delete TargetSize;
		TargetSize = NULL;
	}

	if (_image != NULL)
	{
		delete _image;
		_image = NULL;
	}
}
