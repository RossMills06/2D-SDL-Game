#include <iostream>
#include <string>

#include "RM_GameItem.h"


RM_GameItem::RM_GameItem()
{
	
}

RM_GameItem::RM_GameItem(float x, float y, int w, int h, SDL_Renderer* ren)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;

	this->ren = ren;

	playerSprite.x = x;
	playerSprite.y = y;
	playerSprite.frameheightPixels = 50;
	playerSprite.frameWidthPixels = 50;
	playerSprite.numberOfFrames = 1;

	playerSprite.spriteRenderer = ren;

	playerSprite.load("content/ship_resized.png");
}

void RM_GameItem::start()
{
	velocity.x = 0;
	velocity.y = 0;

	playerSprite.x = x;
	playerSprite.y = y;
	playerSprite.frameheightPixels = 50;
	playerSprite.frameWidthPixels = 50;
	playerSprite.numberOfFrames = 1;

	playerSprite.spriteRenderer = ren;

	playerSprite.load("content/ship_resized.png");
}

void RM_GameItem::input()
{

}

void RM_GameItem::update(bool gamePad)
{
	if (gamePad)
	{
		if (y < 0)
		{
			y++;
		}
		else if (y > 550)
		{
			y--;
		}
		//stopping movement when player is out of bounds

		if (x < 0)
		{
			x++;
		}
		else if (x > 500)
		{
			x--;
		}
		//stopping movement when player is out of bounds


		x = x + velocity.x;
		y = y + velocity.y;
	}
	else
	{
		if (KEY_LEFT)
		{
			velocity.x = -0.09;
		}

		if (KEY_RIGHT)
		{
			velocity.x = 0.09;
		}

		if (KEY_LEFT == false && KEY_RIGHT == false)
		{
			velocity.x = 0;
		}

		if (KEY_UP)
		{
			velocity.y = -0.09;
		}

		if (KEY_DOWN)
		{
			velocity.y = 0.09;
		}

		if (KEY_UP == false && KEY_DOWN == false)
		{
			velocity.y = 0;
		}

		if (y < 0)
		{
			y++;
		}
		else if (y > 550)
		{
			y--;
		}
		//stopping movement when player is out of bounds

		if (x < 0)
		{
			x++;
		}
		else if (x > 500)
		{
			x--;
		}
		//stopping movement when player is out of bounds


		x = x + velocity.x;
		y = y + velocity.y;
	}

	playerSprite.x = x;
	playerSprite.y = y;
	playerSprite.update();
	

}

bool RM_GameItem::collision(RM_Square aSquare)
{
	float left1 = x;
	float right1 = x + width;
	float top1 = y;
	float bottom1 = y + height;

	float left2 = aSquare.x;
	float right2 = aSquare.x + aSquare.w;
	float top2 = aSquare.y;
	float bottom2 = aSquare.y + aSquare.h;


	if (left1 > right2)
	{
		return false;
	}

	if (right1 < left2)
	{
		return false;
	}

	if (top1 > bottom2)
	{
		return false;
	}

	if (bottom1 < top2)
	{
		return false;
	}

	return true;
	

}

void RM_GameItem::render()
{
	
	r->x = x;
	r->y = y;
	r->w = width;
	r->h = height;

	/*SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderFillRect(ren, r);*/

	playerSprite.render();
	
}