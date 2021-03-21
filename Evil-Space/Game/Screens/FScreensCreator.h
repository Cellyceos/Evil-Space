//
//  FScreensCreator.h
//  Screen Creator for Evil Space Game.
//
//  Created by Kirill Bravichev on 03/14/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Engine/Interfaces/IScreensCreator.h"


struct FScreensCreator : IScreensCreator
{
	FScreensCreator() : IScreensCreator(0) {}
	virtual ~FScreensCreator() = default;

	virtual int32 GetScreensCount() const override;
	virtual TSharedPtr<AScreenState> operator()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const override;
};

