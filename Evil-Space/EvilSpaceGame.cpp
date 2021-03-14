//
//  EvilSpaceGame.cpp
//  Evil Space Game.
//
//  Created by Kirill Bravichev on 03/10/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "EvilSpaceGame.h"
#include "Game/Screens/FScreensCreator.h"

#include "Engine/Screens/AScreensManager.h"
#include "Engine/FixedFrameRate.h"


EvilSpaceGame::EvilSpaceGame()
{

}

EvilSpaceGame::~EvilSpaceGame()
{
	LOG("~EvilSpaceGame\n");
}

bool EvilSpaceGame::Init()
{
	MainWindow = std::make_unique<AWindowClass>();
	if (MainWindow->CreateWindow("Evil Space Game", 1024, 768))
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
