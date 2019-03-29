#pragma once

#include <iostream>
#include <string>
#include "RM_sprite.h"

#include "SDL.h"

class RM_Square
{
public:
	int x;
	int y;
	int w;
	int h;

	SDL_Rect* rect = new SDL_Rect();

	RM_Square(int x, int y, int w, int h, SDL_Renderer* ren);

	void start(int x, int y, int w, int h, SDL_Renderer* ren);

	void input();

	void update();

	void render(); 

	SDL_Renderer* ren;

	RM_sprite aSprite;

	int counter = 0;
	bool direction = true;

};

