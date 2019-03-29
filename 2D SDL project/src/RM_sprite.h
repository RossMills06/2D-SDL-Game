#pragma once
#include <iostream>
#include <String>

#include "SDL.h"  //this include sdl into our project
#include "SDL_image.h"

class RM_sprite
{
private:
	
	SDL_Texture* texture;

	unsigned int frameIndex = 0;

public:
	RM_sprite();
	RM_sprite(int x, int y, int frameWidthPixels, int frameHeightPixels, SDL_Renderer* spriteRenderer, int numOfFrames);

	void render();
	void update();
	void load(const char* path);
	void setNumberOfFrames(unsigned int amount);

	int x;
	int y;
	int frameWidthPixels;
	int frameheightPixels;
	unsigned int numberOfFrames;

	int counter = 0;
	bool direction = true;

	SDL_Renderer* spriteRenderer;
};