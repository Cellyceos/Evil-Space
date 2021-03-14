//
//  IScreensCreator.h
//  Screen Creator Interfaces.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Screens/AScreenState.h"

struct IScreensCreator
{
    static constexpr int32 InvalidScreenId{ -1 };
    static constexpr int32 DefaultScreenId{ 0 };

    virtual int32 GetScreensCount() const { return 0; }
    virtual TUniquePtr<AScreenState> operator ()(const TWeakPtr<class AScreensManager>& Owner, int32 StateID) const { return nullptr; }
};
