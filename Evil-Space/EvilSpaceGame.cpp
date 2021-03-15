//
//  EvilSpaceGame.cpp
//  Evil Space Game.
//
//  Created by Kirill Bravichev on 03/10/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "EvilSpaceGame.h"
#include "Game/Screens/FScreensCreator.h"
#include "Game/GameConfig.h"

#include "Engine/Screens/AScreensManager.h"
#include "Engine/FixedFrameRate.h"


EvilSpaceGame::EvilSpaceGame()
{

}

EvilSpaceGame::~EvilSpaceGame()
{
	MainWindow->SetMessageHandler(nullptr);
	MainWindow = nullptr;

	ScreensManager = nullptr;
	LOG("~EvilSpaceGame\n");
}

bool EvilSpaceGame::Init()
{
	MainWindow = std::make_unique<AWindowClass>();
	if (MainWindow->CreateWindow(GameConfig::WindowTitle, GameConfig::WindowWidth, GameConfig::WindowHeight))
	{
		ScreensManager = std::make_shared<AScreensManager>(std::make_unique<FScreensCreator>());
		MainWindow->SetMessageHandler(ScreensManager);

		MainWindow->Show();
		return true;
	}

	return false;
}

int32 EvilSpaceGame::Loop()
{
	AFixedFrameRate FixedFrameRate(60ll);
	while (MainWindow->HandleEvents())
	{
		ScreensManager->Update(FixedFrameRate.GetDeltaTime());
		ScreensManager->Draw(MainWindow->GetRenderer());

		FixedFrameRate.WaitForFixedRate();
	}

	return EXIT_SUCCESS;
}
