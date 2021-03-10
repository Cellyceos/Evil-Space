#include "stdafx.h"
#include "TextBox.h"

using namespace std;
using namespace Gdiplus;

TextBox::TextBox(int x, int y, int width, int height) : TargetLocatiaon(NULL)
												, TargetSize(NULL)
												, aBrush(NULL)
												, textBrush(NULL)
												, fontName(NULL)
												, aPen(NULL)
{
	int nWidth = width > 0 ? width : 100;
	int nHeight = height > 0 ? height : 20;

	TargetSize = new Size(nWidth, nHeight);
	TargetLocatiaon = new Point(x, y);
	aBrush = new SolidBrush(Color(100, 0, 0, 0));
	textBrush = new SolidBrush(Color::White);
	fontName = new Font(L"Times New Roman", 15);
	aPen = new Pen(Color(255, 0, 0, 0)); 
}

void TextBox::Draw(Graphics* g)
{
	if (Visible)
	{
		g->FillRectangle(aBrush, TargetLocatiaon->X, TargetLocatiaon->Y, TargetSize->Width, TargetSize->Height);
		g->DrawRectangle(aPen, TargetLocatiaon->X, TargetLocatiaon->Y, TargetSize->Width, TargetSize->Height);
		PointF point(/*TargetSize->Width / 2 - (int)(fontName->GetSize() / 2) * Text.length() + */(float)TargetLocatiaon->X, (float)TargetLocatiaon->Y/* + TargetSize->Height / 2 - fontName->GetHeight(1) / 2*/);
		g->DrawString(Text.c_str(), (int)Text.length(), fontName, point,textBrush);
	}
}

void TextBox::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (wParam != Keys::Back)
	{
		WCHAR ch = (WCHAR)wParam;	

		Text.push_back(ch);
	}
	else
	{
		Text.resize(Text.length()-1);
	}
}

TextBox::~TextBox(void)
{
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

	if (aBrush != NULL)
	{
		delete aBrush;
		aBrush = NULL;
	}

	if (textBrush != NULL)
	{
		delete textBrush;
		textBrush = NULL;
	}

	if (fontName != NULL)
	{
		delete fontName;
		fontName = NULL;
	}

	if (aPen != NULL)
	{
		delete aPen;
		aPen = NULL;
	}
}
