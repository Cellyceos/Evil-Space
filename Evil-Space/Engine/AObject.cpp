//
//  AObject.cpp
//  Base Class for All object in the game.
//
//  Created by Kirill Bravichev on 03/01/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "AObject.h"


void AObject::SetSize(const FSize& NewSize) 
{ 
	Rect.size = NewSize; 
	Aabb.Radius = { NewSize.width * 0.5f, NewSize.height * 0.5f };
}

void AObject::SetPosition(const FPoint& NewPos)
{ 
	Rect.point = NewPos; 
	Aabb.Center = { NewPos.x + Aabb.Radius[0], NewPos.y + Aabb.Radius[1] };
}

void AObject::SetCenterPoint(const FPoint& Point)
{
	Rect.point.x = Point.x - Aabb.Radius[0];
	Rect.point.y = Point.y - Aabb.Radius[1];

	Aabb.Center = Point;
}
