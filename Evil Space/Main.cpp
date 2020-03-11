#include "stdafx.h"
#include "Main.h"
#include "Game.h"
#include "Map.h"

using namespace Gdiplus;
using namespace std;

Game* game = NULL;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) try
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;

   ::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = Program::WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)(COLOR_3DDKSHADOW+1);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("Edge Detection");

   
   ::RegisterClass(&wndClass);

   hWnd = CreateWindow(
      TEXT("Edge Detection"),   // window class name
      TEXT("Edge Detection"),  // window caption
      WS_OVERLAPPED,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
	  (int)Map::CameraRect.Width+6,      // initial x size
	  (int)Map::CameraRect.Height+28,     // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters

   ::ShowWindow(hWnd, SW_SHOWNORMAL);
   ::UpdateWindow(hWnd);

   ::SetTimer(hWnd, IDT_MAINTIMER, 15, (TIMERPROC) Program::TimerProc);

   while(::GetMessage(&msg, NULL, 0, 0))
   {
	   ::TranslateMessage(&msg);
	   ::DispatchMessage(&msg);
   }

   ::GdiplusShutdown(gdiplusToken);
   return (int)msg.wParam;
}  // WinMain
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) try
{
	switch(message)
	{
		case WM_CREATE:
			OnCreate(hWnd, reinterpret_cast<CREATESTRUCT*>(lParam));
			break;
		case WM_KEYDOWN:
			game->KeyDown(hWnd, wParam, lParam);
			break;
		case WM_KEYUP:
			game->KeyUp(hWnd, wParam, lParam);
			break;
		case WM_CLOSE:
			OnClose(hWnd);
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			game->MauseDown(hWnd, wParam, lParam);		
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
	    case WM_MBUTTONUP:
			game->MauseUp(hWnd, wParam, lParam);
			break;
		case WM_MOUSEMOVE:
			game->MouseMove(hWnd, wParam, lParam);
			break;
		case WM_DESTROY:
			OnDestroy(hWnd, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return S_OK;
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::OnCreate(HWND hWnd, CREATESTRUCT* cr)try
{
	game = new Game();

	game->Create(hWnd, cr);
	return S_OK;
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) try
{
	KillTimer(hWnd, IDT_MAINTIMER);

	if (game != NULL)
	{
		delete game;
		game = NULL;
	}

	PostQuitMessage(0);

	return S_OK;
}
catch (...)
{
	return S_FALSE;
};


LRESULT CALLBACK Program::GameStart(HWND hWnd, WPARAM wParam, LPARAM lParam) try
{
	::SetTimer(hWnd, IDT_MOBTIMER, 500, (TIMERPROC) MobSpawn);
	::SetTimer(hWnd, IDT_ASTERTIMER, 15000, (TIMERPROC) AsterSpawn);

	return game->Start(hWnd, wParam, lParam);
}
catch (...)
{
	return S_FALSE;
};


LRESULT CALLBACK Program::GameAbout(HWND hWnd, WPARAM wParam, LPARAM lParam) try
{
	return game->About();
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::GameRecords(HWND hWnd, WPARAM wParam, LPARAM lParam) try
{
	return S_OK;
}
catch (...)
{
	return S_FALSE;
};


LRESULT CALLBACK Program::GameOver() try
{
	return game->Over();
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::GameExit(HWND hWnd, WPARAM wParam, LPARAM lParam) try
{
	game->Exit(hWnd, wParam, lParam);
	OnClose(hWnd);
	return S_OK;
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::OnClose(HWND hWnd) try
{
#if NDEBUG
	if (IDOK == MessageBox(hWnd, L"Вы уверены что хотите выйти", L"Выход", MB_OKCANCEL|MB_ICONQUESTION))
		DestroyWindow(hWnd);
#else
	DestroyWindow(hWnd);
#endif
	return S_OK;
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::MobSpawn(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) try
{
	return game->MobTimer(hwnd, message, idTimer, dwTime);
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::AsterSpawn(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) try
{
	return game->AsterTimer(hwnd, message, idTimer, dwTime);
}
catch (...)
{
	return S_FALSE;
};

LRESULT CALLBACK Program::TimerProc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) try
{ 
	return game->MainTimer(hwnd, message, idTimer, dwTime);
}
catch (...)
{
	return S_FALSE;
};





