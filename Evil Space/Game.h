#pragma once

class Map;
class Compositor;
class Player;
class Universe;
class BufferedGraphicsContext;
class GDIBitmap;
class Random;


class Game
{
public:
	Game(void);
	LRESULT	CALLBACK	KeyDown(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	KeyUp(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	MouseMove(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	MauseDown(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	MauseUp(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	MainTimer(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	MobTimer(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	AsterTimer(HWND, UINT, UINT, DWORD);
	LRESULT	CALLBACK	Exit(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	Start(HWND, WPARAM, LPARAM);
	LRESULT	CALLBACK	Over();
	LRESULT	CALLBACK	About();
	LRESULT	CALLBACK	Menu(Gdiplus::Graphics*);
	LRESULT	CALLBACK	DrawAbout(Gdiplus::Graphics*);
	LRESULT CALLBACK	DrawGameOver(Gdiplus::Graphics*, HWND);
	LRESULT	CALLBACK	Create(HWND, CREATESTRUCT*);
	~Game(void);
private:
	class GameState
	{
	public:
		enum gamestate
		{
			NewGame,
			Pausegame,
			GameOver,
			Settings,
			About,
			Records,
			MainMenu
		};
	};

	int fps;
	DWORD second;
	int FPS;
	Map* maps;
	Compositor* compositor; 
	Player* player;
	Universe* universe;
	BufferedGraphicsContext& currentContext;
	ButtonList& bList;
	int gameState;
	GDIBitmap* bgi;
	static std::wstring strmas[5];
	Random Randomizer;
	int level;
	Gdiplus::SolidBrush* semiTransBrush;
	int score;
};
