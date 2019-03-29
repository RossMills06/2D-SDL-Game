#pragma once

#include <iostream>
#include <string>

#include "SDL.h"

#include "RM_Vector2D.h"



class RM_bullet
{
public:
	float x;
	float y;
	int width;
	int height;

	SDL_Rect* rect = new SDL_Rect();

	RM_bullet(float x, float y, int w, int h);

	void start(float x, float y, int w, int h);

	void input();

	void update();

	void render(SDL_Renderer* ren);

	RM_Vector2D velocity;

	int counter = 0;
};
