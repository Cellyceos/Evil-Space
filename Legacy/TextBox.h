#pragma once

class TextBox
{
public:
	std::wstring Text;
	Gdiplus::Point* TargetLocatiaon;
	Gdiplus::Size* TargetSize;

	bool Enabled;
	bool Visible;
	TextBox(int, int, int = 0, int = 0);
	virtual void Draw(Gdiplus::Graphics*);
	virtual void OnKeyDown(HWND, WPARAM, LPARAM);
	virtual ~TextBox(void);
private:
	Gdiplus::SolidBrush* aBrush;
	Gdiplus::SolidBrush* textBrush;
	Gdiplus::Pen* aPen;
	Gdiplus::Font* fontName;
};
