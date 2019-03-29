#pragma once

#ifndef RM_BulletControllerFILE
#define RM_BulletControllerFILE

#include <iostream> // functions for printing things out
#include "SDL.h"  //this include sdl into our project
#include <vector>

#include <string>   // functions for strings

#include <ctime>
#include <fstream>

using namespace std;


#include "SDL_image.h"

#include "RM_bullet.h"
#include "RM_Vector2D.h"
#include "RM_Square.h"



class RM_BulletController
{

public:
	RM_BulletController();
	
	
	void start(int x, int y);

	void add(int x, int y);
		
	void render(SDL_Renderer* ren);

	void update();

	void shoot(RM_Vector2D aVector);

	bool collision(RM_Square aSquare);

	int num = 4;

	int X, Y;

	SDL_Rect* r = new SDL_Rect();

	vector<RM_bullet*> aListofBullets;

	RM_Vector2D velocity;
};

#endif