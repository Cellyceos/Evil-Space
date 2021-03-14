//
//  MainScreen.h
//  Main Screen State.
//
//  Created by Kirill Bravichev on 03/14/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "Screens/AScreenState.h"


class AMainScreen : public AScreenState
{
public:
	AMainScreen(const TWeakPtr<class AScreensManager>& InOwner);
	virtual ~AMainScreen();

	virtual void Init() override;
	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<ARendererClass>& Renderer) const override;

	virtual int32 GetId() const override { return 0; }

private:
	void Quit(EInputState KeyEvent);
};
