#pragma once

class GDIBitmap;

class ImageButton
{
	typedef LRESULT (CALLBACK* ONCLICK)(HWND, WPARAM, LPARAM);

public:
	Gdiplus::Point* TargetLocatiaon;
	Gdiplus::Size* TargetSize;
	bool Enabled;
	bool Visible;

	ONCLICK OnClick;
	ImageButton(int, int, std::wstring, int = 0, int = 0);
	virtual Gdiplus::Status OnMauseDown(HWND, WPARAM, LPARAM);
	virtual void OnMauseUp(HWND, WPARAM, LPARAM);
	virtual void OnMauseMove(HWND, WPARAM, LPARAM);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void Draw(Gdiplus::Graphics*);
	virtual ~ImageButton(void);
private:
	enum ImageStatus
	{
		Default,
		Selected,
		Active
	};

	GDIBitmap* _image;
	ImageStatus status;

	bool CheckIntersection(LPARAM);
};
