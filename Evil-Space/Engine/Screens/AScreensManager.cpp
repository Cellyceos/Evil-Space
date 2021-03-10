//
//  AScreensManager.cpp
//  Screen Manager based on FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AScreensManager.h"


AScreensManager::AScreensManager(const TSharedPtr<IScreensCreator>& InScreensCreator) : ScreensCreator(InScreensCreator)
{
	ActiveScreens.reserve(ScreensCreator->GetScreensCount());
}

AScreensManager::~AScreensManager()
{
	SDL_Log("~AScreensManager\n");
}

void AScreensManager::Update(float DeltaTime)
{
	if (RequestScreenId != IScreensCreator::InvalidRequestId)
	{
		TransitState();
	}

	// Update All States if needed
	for (auto& Screen : ActiveScreens)
	{
		Screen->Update(DeltaTime);

		if (!Screen->ShouldUpdatePrevStates())
			break;
	}
}

void AScreensManager::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	Renderer->Clear(BackgroundColor);

	for (auto Iter = ActiveScreens.rbegin(); Iter != ActiveScreens.rend(); ++Iter)
	{
		auto NextIter = Iter + 1;
		if (NextIter == ActiveScreens.rend() || (*NextIter)->ShouldDrawPrevScreen())
		{
			(*Iter)->Draw(Renderer);
		}
	}

	// Draw All States if needed
	Renderer->Present();
}

void AScreensManager::TransitState()
{
	auto EndIter = ActiveScreens.begin();
	for (; EndIter != ActiveScreens.end(); ++EndIter)
	{
		if (EndIter == ActiveScreens.end() || ((*EndIter)->GetId() == RequestScreenId))
		{
			break;
		}
	}

	if (EndIter == ActiveScreens.end())
	{
		ActiveScreens.insert(ActiveScreens.begin(), (*ScreensCreator)(weak_from_this(), RequestScreenId));
	}
	else
	{
		ActiveScreens.erase(ActiveScreens.begin(), EndIter);
	}

	RequestScreenId = IScreensCreator::InvalidRequestId;
}

void AScreensManager::RequestToQuit()
{
	AWindowClass::SendQuitMessage();
}

/// Begin IMessageHandler
void AScreensManager::OnKeyDown(const FKeyboardEvent& Event)
{
	for (const auto& Screen : ActiveScreens)
	{
		if (Screen->HasBindings())
		{
			if (const auto& KeyDelegate = Screen->GetDelegateBoundToKey(Event.Key))
			{
				KeyDelegate(Event.State);
			}
		}

		if (!Screen->ShouldHandleInputsPrevStates())
			break;
	}
}

void AScreensManager::OnKeyUp(const FKeyboardEvent& Event)
{
	for (const auto& Screen : ActiveScreens)
	{
		if (Screen->HasBindings())
		{
			if (const auto& KeyDelegate = Screen->GetDelegateBoundToKey(Event.Key))
			{
				KeyDelegate(Event.State);
			}
		}

		if (!Screen->ShouldHandleInputsPrevStates())
			break;
	}
}

void AScreensManager::OnMouseButtonDown(const FMouseButtonEvent& Event)
{

}

void AScreensManager::OnMouseButtonUp(const FMouseButtonEvent& Event)
{

}

void AScreensManager::OnMouseMotion(const FMouseMotionEvent& Event)
{

}

void AScreensManager::OnWindowsFocusGained()
{
	if (ActiveScreens.size() > 0)
	{
		if (auto& ActiveScreen = ActiveScreens.front())
		{
			ActiveScreen->OnWindowsGainFocus();
		}
	}

	SDL_Log("Windows Focus Gained");
}

void AScreensManager::OnWindowsFocusLost()
{
	if (ActiveScreens.size() > 0)
	{
		if (auto& ActiveScreen = ActiveScreens.front())
		{
			ActiveScreen->OnWindowsLostFocus();
		}
	}

	SDL_Log("Windows Focus Lost");
}
/// End IMessageHandler
