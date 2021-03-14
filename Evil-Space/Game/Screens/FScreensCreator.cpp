//
//  FScreensCreator.cpp
//  Screen Creator for Evil Space Game.
//
//  Created by Kirill Bravichev on 03/14/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FScreensCreator.h"
#include "AMainScreen.h"


int32 FScreensCreator::GetScreensCount() const
{
	return 1;
}

TUniquePtr<AScreenState> FScreensCreator::operator()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const
{
	auto NewScreen = std::make_unique<AMainScreen>(Owner);

	if (NewScreen)
	{
		NewScreen->Init();
	}

	return std::move(NewScreen);
}
