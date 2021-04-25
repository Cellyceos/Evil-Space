//
//  MainScreen.cpp
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/14/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AMainScreen.h"
#include "Screens/AScreensManager.h"


#include "Formats/FHAImageFormat.h"
#include "Formats/FGImageFormat.h"


AMainScreen::AMainScreen(const TWeakPtr<class AScreensManager>& InOwner) : AScreenState(InOwner)
{

}

AMainScreen::~AMainScreen()
{
	LOG("~AMainScreen");
}

void AMainScreen::Init()
{
	BindKey(EInputKey::Escape, std::bind(&AMainScreen::Quit, this, _1));
	HAImage = FHAImageFormat::Load("Assets/PirateSpecial3.hai");
	GImage = FGImageFormat::Load("Assets/Star00.gi");
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
	static uint32 FrameNum = 0;
	static float Rotation = 0.0f;

	const auto& FrameImage = HAImage->GetFrame(FrameNum);
	Renderer->DrawTexture(FrameImage, { 200.0f, 300.0f }, Rotation);
	Renderer->DrawTexture(FrameImage, { 600.0f, 300.0f }, -Rotation);

	FrameNum = (FrameNum + 1) % HAImage->GetFrameCount();
	Rotation += 1.0f;

	if (Rotation >= 360.0f)
	{
		Rotation = 0.0f;
	}

	Renderer->DrawTexture(GImage->GetFrame(), { 400.0f, 300.0f }, 0.0f);
}
