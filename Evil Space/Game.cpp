#include "stdafx.h"
#include "Map.h"
#include "GameObject.h"
#include "Game.h"
#include "Compositor.h"
#include "BufferedGraphics.h"
#include "BufferedGraphicsContext.h"
#include "GDIBitmap.h"
#include "ImageButton.h"
#include "Player.h"
#include "Asteroid.h"
#include "Universe.h"
#include "Main.h"
#include "Frigates.h"
#include "Cruisers.h"
#include "Battlecruiser.h"
#include "Batteleship.h"
#include "GameTicks.h"
#include "Random.h"

using namespace std;
using namespace Gdiplus;

wstring Game::strmas[] = {L"New.tif", L"About.tif", L"Exit.tif"};

Game::Game(void) : currentContext(*new BufferedGraphicsContext)
					, bList(*new ButtonList)
					, gameState(GameState::MainMenu)
					, compositor(NULL)
					, maps(NULL)
					, universe(NULL)
					, player(NULL)
					, FPS(0)
					, fps(0)
					, second(0)
					, level(6)
					, score(0)
{
	bgi = new GDIBitmap(GameObject::ContentPath + Map::MapPath + L"IMG.tif");
	semiTransBrush = new SolidBrush(Color::MakeARGB(100, 0, 0, 0));
}

LRESULT CALLBACK Game::MauseDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (gameState == GameState::MainMenu)
	{
		for (int i = 0; i < bList.Count(); i++)
		{
			if (bList[i]->OnMauseDown(hWnd, wParam, lParam) == Aborted)
				break;
		}
	}

	return S_OK;
}

LRESULT CALLBACK Game::MauseUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (gameState == GameState::MainMenu)
	{
		for (int i = 0; i < bList.Count(); i++)
		{
			bList[i]->OnMauseUp(hWnd, wParam, lParam);
		}
	}

	return S_OK;
}

LRESULT CALLBACK Game::Create(HWND hWnd, CREATESTRUCT* cr)
{
	currentContext.MaximumBuffer(new Size((int)Map::CameraRect.Width, (int)Map::CameraRect.Height));

	for (int i = 0; i < 3; i++)
		bList.Add(new ImageButton(354, 262 + 60*i, strmas[i]));

	bList[0]->OnClick = Program::GameStart;
	bList[1]->OnClick = Program::GameAbout;
	bList[2]->OnClick = Program::GameExit;

	return S_OK;
}
LRESULT CALLBACK Game::Start(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	gameState = GameState::NewGame;

	maps = new Map();
	compositor = new Compositor();

	player = new Player(maps, compositor);
	universe = new Universe(maps, compositor);
	universe->MiddlePoint(maps->MiddlePoint());

	compositor->AddGameObject(universe);
	compositor->AddGameObject(player);

	return S_OK;
}

LRESULT CALLBACK Game::Menu(Graphics* g)
{
	g->DrawImage(bgi->GetFrame(0), 0, 0, (int)Map::CameraRect.Width, (int)Map::CameraRect.Height);

	for (int i = 0; i < bList.Count(); i++)
		bList[i]->Draw(g);

	return S_OK;
}

LRESULT CALLBACK Game::Exit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

LRESULT CALLBACK Game::MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (gameState == GameState::MainMenu)
	{
		for (int i = 0; i < bList.Count(); i++)
		{
			bList[i]->OnMauseMove(hWnd, wParam, lParam);
		}
	}

	return S_OK;
}

LRESULT CALLBACK Game::KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (gameState == GameState::NewGame)
	{
		if (wParam == Keys::Left && !player->IsLeft())
			player->IsLeft(player->MoveLeft());

		if (wParam == Keys::Right && !player->IsRight())
			player->IsRight(player->MoveRight());

		if (wParam == Keys::Up && !player->IsUp())
			player->IsUp(player->IncreaseSpeed());

		if (wParam == Keys::Down && !player->IsDown())
			player->IsDown(player->SlowSpeed());

		if (wParam == Keys::Space && !player->IsSpace())
			player->IsSpace(player->Fire());

		if (wParam == Keys::Escape) 
			Over();

	if (wParam == Keys::P)
		gameState = gameState == GameState::Pausegame ? GameState::NewGame : GameState::Pausegame;
	}

	if (gameState != GameState::NewGame)
	{
		if (wParam == Keys::Enter)
			gameState = GameState::MainMenu;
	}


	return S_OK;
}

LRESULT CALLBACK Game::Over()
{
	score = player->Points();
	compositor->Ammunitions.Clear();
	compositor->Effects.Clear();
	compositor->Objects.Clear();
	gameState = GameState::GameOver;
	level = 1;

	return S_OK;
}

LRESULT CALLBACK Game::KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (gameState == GameState::NewGame)
	{
		if (wParam == Keys::Left && player->IsLeft())
			player->IsLeft(false);

		if (wParam == Keys::Right && player->IsRight())
			player->IsRight(false);

		if (wParam == Keys::Up && player->IsUp())
			player->IsUp(false);

		if (wParam == Keys::Down && player->IsDown())
			player->IsDown(false);

		if (wParam == Keys::Space && player->IsSpace())
			player->IsSpace(false);
	}

	return S_OK;
}

LRESULT CALLBACK Game::MobTimer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) 
{
	int points = player->Points() / (500*level);
	if (points == 1 && level < 6)
		level++;	

	if (compositor->Objects.Count() > 5*level)
		return S_OK;

	int rnd = Randomizer.Next(1, 25*level);

	if (rnd < 25)
		compositor->AddGameObject(new Frigates(maps, compositor));
	else if (rnd < 50)
		compositor->AddGameObject(new Cruisers(maps, compositor));
	else if (rnd < 75)
		compositor->AddGameObject(new Battlecruiser(maps, compositor));
	else
		compositor->AddGameObject(new Batteleship(maps, compositor));
	return S_OK;
}

LRESULT CALLBACK Game::AsterTimer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) 
{
	compositor->AddGameObject(new Asteroid(maps, compositor));

	return S_OK;
}

LRESULT CALLBACK Game::DrawGameOver(Graphics* g, HWND hWnd)
{
	KillTimer(hWnd, IDT_MOBTIMER);
	KillTimer(hWnd, IDT_ASTERTIMER);

	RectF rect(20.0f, 20.0f, Map::CameraRect.Width - 20*2, Map::CameraRect.Height - 20*2);
	g->FillRectangle(semiTransBrush, rect);
	Pen* pen = new Pen(Color::White);
	g->DrawRectangle(pen, rect);

	WCHAR name[35];
	Font& TimesFont48 = *new Font(L"Times New Roman", 48);
	Font& TimesFont16 = *new Font(L"Times New Roman", 16);
	SolidBrush& WhiteBrush = *new SolidBrush(Color::AntiqueWhite);
	StringFormat& Format = *new StringFormat();
	Format.SetAlignment(StringAlignmentCenter);
	Format.SetLineAlignment(StringAlignmentCenter);
	int len = swprintf(name, 35, L"Игра окончена!\nВаш счет: %d", score);

	g->DrawString(name, len, &TimesFont48, rect, &Format, &WhiteBrush);

	Format.SetLineAlignment(StringAlignmentFar);

	len = swprintf(name, 35, L"\n\n\nДля продолжения нажмите ввод");
	g->DrawString(name, len, &TimesFont16, rect, &Format, &WhiteBrush);

	delete pen;
	delete &TimesFont48;
	delete &TimesFont16;
	delete &Format;
	delete &WhiteBrush;
	return S_OK;
}
LRESULT CALLBACK Game::About()
{
	gameState = GameState::About;
	return S_OK;
}
LRESULT CALLBACK Game::DrawAbout(Graphics* g)
{
	RectF rect(20.0f, 20.0f, Map::CameraRect.Width - 20*2, Map::CameraRect.Height - 20*2);
	g->FillRectangle(semiTransBrush, rect);
	Pen* pen = new Pen(Color::White);
	g->DrawRectangle(pen, rect);

	WCHAR name[40];
	Font& TimesFont24 = *new Font(L"Times New Roman", 24);
	Font& TimesFont16 = *new Font(L"Times New Roman", 16);
	SolidBrush& WhiteBrush = *new SolidBrush(Color::AntiqueWhite);
	StringFormat& Format = *new StringFormat();
	Format.SetAlignment(StringAlignmentCenter);
	Format.SetLineAlignment(StringAlignmentNear);
	int len = swprintf(name, 40, L"БГТУ \"Военмех\" имени Д.Ф.Устинова");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);

	Format.SetLineAlignment(StringAlignmentCenter);
	len = swprintf(name, 40, L"Группа И581");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);
	len = swprintf(name, 40, L"\n\nБравичев Кирилл");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);
	len = swprintf(name, 40, L"\n\n\n\nКонтент взят из игры");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);
	len = swprintf(name, 40, L"\n\n\n\n\n\nКосмические Рейнджеры 1 и 2");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);

	Format.SetLineAlignment(StringAlignmentFar);
	len = swprintf(name, 35, L"Для продолжения нажмите ввод");
	g->DrawString(name, len, &TimesFont24, rect, &Format, &WhiteBrush);

	delete pen;
	delete &TimesFont24;
	delete &TimesFont16;
	delete &Format;
	delete &WhiteBrush;
	return S_OK;
}

LRESULT CALLBACK Game::MainTimer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) 
{ 
	Graphics* g = Graphics::FromHWND(hwnd);
	BufferedGraphics* bg = currentContext.Allocate(g, Map::CameraRect);
	bg->GraphicsSurface->SetSmoothingMode(SmoothingModeAntiAlias);
	GameTicks::Ticks = dwTime;
	fps++;
	switch(gameState)
	{
	case GameState::MainMenu:
		Menu(bg->GraphicsSurface);
		break;

	case GameState::NewGame:
		maps->Draw(bg->GraphicsSurface);
		compositor->Update();
		compositor->Draw(bg->GraphicsSurface);
		break;
	case GameState::GameOver:
		DrawGameOver(bg->GraphicsSurface, hwnd);
		break;
	case GameState::About:
		DrawAbout(bg->GraphicsSurface);
		break;

	default:
		break;
	}

	WCHAR name[30];
		Font& TimesFont = *new Font(L"Times New Roman", 12);
		SolidBrush& WhiteBrush = *new SolidBrush(Color::AntiqueWhite);
		StringFormat& Format = *new StringFormat();
		Format.SetAlignment(StringAlignmentCenter);
		Format.SetLineAlignment(StringAlignmentNear);
		int len = swprintf(name, 30, L"FPS: %d, Obj: %d", FPS, compositor != NULL ? compositor->Objects.Count() : 0);
	
		bg->GraphicsSurface->DrawString(name, len, &TimesFont, Map::CameraRect, &Format, &WhiteBrush);
	
		if (gameState == GameState::NewGame)
		{
			len = swprintf(name, 30, L"\nСчет: %d", player->Points());
			bg->GraphicsSurface->DrawString(name, len, &TimesFont, Map::CameraRect, &Format, &WhiteBrush);
	
			Format.SetAlignment(StringAlignmentNear);
			Format.SetLineAlignment(StringAlignmentFar);
	
			len = swprintf(name, 30, L"Щиты: %d \nЗдоровье: %d", player->Shild(), player->Health());
			bg->GraphicsSurface->DrawString(name, len, &TimesFont, Map::CameraRect, &Format, &WhiteBrush);
	
			Format.SetAlignment(StringAlignmentFar);
			Format.SetLineAlignment(StringAlignmentFar);
	
			len = swprintf(name, 30, L"Уровень: %d", level);
			bg->GraphicsSurface->DrawString(name, len, &TimesFont, Map::CameraRect, &Format, &WhiteBrush);
		}
	
		if (GameTicks::Ticks > second) 
		{
			second = 1000 + GameTicks::Ticks;
			FPS = fps;
			fps = 0;
	
			if (gameState == GameState::NewGame && level > 2)
				player->Points(player->Points() + 2);
		}



	if (gameState != GameState::Pausegame)
		bg->Render();

	if (bg != NULL)
	{
		delete bg;
		bg = NULL;
	}
	delete &TimesFont;
	delete &Format;
	delete &WhiteBrush;

	return S_OK;
}

Game::~Game(void)
{
	if (compositor != NULL)
	{
		delete compositor;
		compositor = NULL;
	}

	if (maps != NULL)
	{
		delete maps;
		maps = NULL;
	}

	delete &currentContext;
	delete &bList;
}
