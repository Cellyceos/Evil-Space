//
//  EvilSpaceGame.h
//  Evil Space Game.
//
//  Created by Kirill Bravichev on 03/10/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class EvilSpaceGame
{
public:
	EvilSpaceGame();
	~EvilSpaceGame();

	bool Init();
	int32 Loop();

private:
	TSharedPtr<AWindowClass> MainWindow = nullptr;
	TSharedPtr<class AScreensManager> ScreensManager = nullptr;
};
