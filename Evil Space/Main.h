#pragma once

#define IDT_MAINTIMER	200
#define IDT_MOBTIMER	201
#define IDT_ASTERTIMER	202

namespace Program
{
	LRESULT	CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnCreate(HWND, CREATESTRUCT*);
	LRESULT	CALLBACK	OnKeyDown(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnKeyUp(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnClose(HWND);
	LRESULT	CALLBACK	TimerProc(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	MobSpawn(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	AsterSpawn(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	GameExit(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	GameStart(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	GameAbout(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	GameRecords(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	DrawMainMenu(Gdiplus::Graphics*);
	LRESULT	CALLBACK	OnMouseMove(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnMauseDown(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnMauseUp(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	OnDestroy(HWND, WPARAM, LPARAM);
	LRESULT CALLBACK	GameOver();
};