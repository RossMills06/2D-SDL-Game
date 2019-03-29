#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "RM_Vector2D.h"
#include "RM_Square.h"
#include "RM_sprite.h"

class RM_GameItem
{
public:
	float x;
	float y;
	int width;
	int height;

	RM_GameItem();

	RM_GameItem(float x, float y, int w, int h, SDL_Renderer* ren);

	void start();

	void input();

	void update(bool gamePad);

	bool collision(RM_Square aSquare);

	void render();

	RM_Vector2D velocity;

	SDL_Renderer* ren;

	RM_sprite playerSprite;

	SDL_Rect* r = new SDL_Rect();

	bool KEY_LEFT = false;
	bool KEY_RIGHT = false;
	bool KEY_UP = false;
	bool KEY_DOWN = false; 

	
};
