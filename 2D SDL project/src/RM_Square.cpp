#include <iostream>
#include <string>

#include "RM_Square.h"


RM_Square::RM_Square(int x, int y, int w, int h, SDL_Renderer* ren)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->ren = ren;

	aSprite.x = x;
	aSprite.y = y;
	aSprite.frameheightPixels = 75;
	aSprite.frameWidthPixels = 75;
	aSprite.numberOfFrames = 4;
	aSprite.spriteRenderer = ren;

	aSprite.load("content/spritesheet_resized.png");
}

void RM_Square::start(int x, int y, int w, int h, SDL_Renderer* ren)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->ren = ren;

	aSprite.x = x;
	aSprite.y = y;
	aSprite.frameheightPixels = 75;
	aSprite.frameWidthPixels = 75;
	aSprite.numberOfFrames = 4;
	aSprite.spriteRenderer = ren;

	aSprite.load("content/spritesheet_resized.png");
	
}

void RM_Square::input()
{

}

void RM_Square::update()
{
	counter++;
	//incriments the counter each frame

	if (counter % 75 == 0)
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


	if (counter % 10000 == 0)
	{
		x -= 75;
	}
	//moves sqaures closer to player after a time period

	if (x < 50)
	{
		x = 800;
		//resets the position of the sqaure
	}

	aSprite.x = x;
	aSprite.y = y;
	aSprite.update();

}

void RM_Square::render()
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	//SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	//SDL_RenderFillRect(ren, rect);

	aSprite.render();
}