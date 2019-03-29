

#include "RM_sprite.h"

RM_sprite::RM_sprite()
{

}

RM_sprite::RM_sprite(int x, int y, int frameWidthPixels, int frameHeightPixels, SDL_Renderer* spriteRenderer, int numOfFrames)
{
	this->x = x;
	this->y = y;
	this->frameWidthPixels = frameWidthPixels;
	this->frameheightPixels = frameHeightPixels;

	this->numberOfFrames = numOfFrames;

	this->spriteRenderer = spriteRenderer;
}

void RM_sprite::render()
{
	unsigned int calcX = frameWidthPixels * frameIndex;

	SDL_Rect srcRect = { calcX, 0, frameWidthPixels, frameheightPixels };

	SDL_Rect dstRect = { x, y, frameWidthPixels, frameheightPixels };

	SDL_RenderCopy(spriteRenderer, texture, &srcRect, &dstRect);
}

void RM_sprite::update()
{
	unsigned int ticks = SDL_GetTicks();

	unsigned int changeTimeMS = 200;

	frameIndex = (ticks / changeTimeMS) % numberOfFrames;

	counter++;
	//incriments the counter each frame

	if (counter % 15 == 0)
	{
		if (y < 0)
		{
			direction = true;
		}
		else if (y > 500)
		{
			direction = false;
		}
		//sets the direction of the sprite depending on if its at the top or bottom of the window

		if (direction == true)
		{
			y++;
		}
		else
		{
			y--;
		}
		//updating the y value
	}
	//changing the y value of the sprite every 15 frames
}

void RM_sprite::load(const char* path)
{
	IMG_Init(SDL_INIT_EVERYTHING);
	//Initialise SDL2_Image

	SDL_Surface* surface = IMG_Load(path);
	//Load in png

	texture = SDL_CreateTextureFromSurface(spriteRenderer, surface);
	//Convert to a texture

	SDL_FreeSurface(surface);
	//Free up the surface data from RAM

	IMG_Quit();
	//Quite SDL2_Image

	SDL_Log("Sprite Loaded");
}

void RM_sprite::setNumberOfFrames(unsigned int amount)
{

}
