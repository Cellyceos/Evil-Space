//
//  MainScreen.cpp
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/14/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AMainScreen.h"
#include "Screens/AScreensManager.h"


#include "Formats/FHAIFormat.h"


AMainScreen::AMainScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

AMainScreen::~AMainScreen()
{
	LOG("~AMainScreen\n");
}

void AMainScreen::Init()
{
	BindKey(EInputKey::Escape, std::bind(&AMainScreen::Quit, this, _1));
	Image = FHAIFormat::Load("Assets/PirateSpecial3.hai");
}

void AMainScreen::Quit(EInputState KeyEvent)
{
	if (KeyEvent == EInputState::Pressed)
	{
		if (!Owner.expired())
		{
			Owner.lock()->RequestToQuit();
		}
	}
}

void AMainScreen::Update(float DeltaTime)
{

}

void AMainScreen::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	Image->Draw(Renderer);
}
