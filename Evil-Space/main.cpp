//
//  main.cpp
//  The main entry point to the program.
//
//  Created by Kirill Bravichev on 03/10/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "EvilSpaceGame.h"
#include "SDL_main.h"


int main(int argc, char* argv[])
{
	EvilSpaceGame Game;

	if (Game.Init())
	{
		return Game.Loop();
	}

	return EXIT_FAILURE;
}
