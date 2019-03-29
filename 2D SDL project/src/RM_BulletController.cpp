#include "RM_BulletController.h"

RM_BulletController::RM_BulletController()
{

}


void RM_BulletController::start(int x, int y)
{
	X = x;
	Y = y;
}

void RM_BulletController::add(int x, int y)
{
	RM_bullet* aBulletItem = new RM_bullet(x, y, 10, 10);
	aBulletItem->velocity.x = 0;
	aBulletItem->velocity.y = 0;
	this->aListofBullets.push_back(aBulletItem);
}

void RM_BulletController::render(SDL_Renderer* aRenderer)
{
	for (auto& element : aListofBullets)
	{
		element->render(aRenderer);
	}

	r->x = 40 + X;
	r->y = 20 + Y;
	r->w = 10;
	r->h = 10;

	SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, r);
}

void RM_BulletController::update()
{
	for (auto& element : aListofBullets)
	{
		element->update();
	
		if (element->velocity.x > 0)
		{
			element->counter++;
		}
		else if (element->velocity.x == 0)
		{
			element->x = X;
			element->y = Y;
		}

		if (element->counter > 10000)
		{
			element->counter = 0;
			element->x = X;
			element->y = Y;
			element->velocity.x = 0;
		}
	}
}

bool RM_BulletController::collision(RM_Square aSquare)
{
	for (auto& element : aListofBullets)
	{
		if ((aSquare.x < element->x) && (element->y > aSquare.y - 10) && (element->y < (aSquare.y + aSquare.h)))
		{
			element->velocity.x = 0;
			return true;
		}
		//returns a collision when the bullet hits square
	}
	return false;
}

void RM_BulletController::shoot(RM_Vector2D aVector)

{
	int i = 0;
	bool notFound = true;
	
	while((i < aListofBullets.size()) && (notFound))
	{
	
		if (aListofBullets[i]->velocity.x == 0)
		{
			aListofBullets[i]->counter = 0;
			aListofBullets[i]->velocity.x = aVector.x;
			aListofBullets[i]->velocity.y = aVector.y;
			notFound = false;
		}
		i++;
	}
}