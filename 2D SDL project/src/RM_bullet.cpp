#include "RM_bullet.h"

RM_bullet::RM_bullet(float x, float y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}

void RM_bullet::start(float x, float y, int w, int h)
{
	this->x = 50 + x;
	this->y = 20 + y;
	this->width = w;
	this->height = h;
}

void RM_bullet::input()
{

}

void RM_bullet::update()
{
	x = x + velocity.x;
	y = y + velocity.y;

	x = x + (velocity.perp().x * (sin(counter) * 30.0f));
	y = y + (velocity.perp().y * (sin(counter) * 30.0f));
}

void RM_bullet::render(SDL_Renderer * ren)
{
	SDL_Rect* r = new SDL_Rect();
	r->x = 40 + x;
	r->y = 20 + y;
	r->w = width;
	r->h = height;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderFillRect(ren, r);

	//setting values for Bullet rect
}
