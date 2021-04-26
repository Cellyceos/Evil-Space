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
	Aabb.radius = { NewSize.width * 0.5f, NewSize.height * 0.5f };
}

void AObject::SetPosition(const FPoint& NewPos)
{ 
	Rect.point = NewPos; 
	Aabb.center = { NewPos.x + Aabb.radius[0], NewPos.y + Aabb.radius[1] };
}

void AObject::SetCenterPoint(const FPoint& Point)
{
	Rect.point.x = Point.x - Aabb.radius[0];
	Rect.point.y = Point.y - Aabb.radius[1];

	Aabb.center = Point;
}
