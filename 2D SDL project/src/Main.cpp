#include <iostream> // functions for printing things out
#include <string>   // functions for strings
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <SDL_mixer.h>

#include "SDL.h"  //this include sdl into our project
#include "SDL_image.h"

#include "RM_GameItem.h"
#include "RM_sprite.h"
#include "RM_Square.h"
#include "RM_bullet.h"
#include "RM_BulletController.h"

#define STB_TRUETYPE_IMPLEMENTATION

#include "ScreenText.h"
#include "json.hpp"

using json = nlohmann::json;

SDL_Joystick* aGamePad = NULL;
//gamepad controller
RM_Vector2D aJoystick;
//vector for the joystick
bool gamePad = false;

//Alias -- we don't want to type out std:: all the time!
using namespace std;

Mix_Music *SOUND_backmusic = NULL;
Mix_Chunk *SOUND_shot = NULL;

SDL_Event _event;

std::ofstream logFile;
//creating the log file

RM_GameItem aGameItem;
//creating an object for the Game Item (player)

RM_GameItem aGameItemPlayer2;

vector<RM_Square> aSquareList;
//creating a vector for squares (enemies)

RM_BulletController aBulletController;
//creating an object for the Bullet controller

RM_BulletController aBulletControllerPlayer2;

ScreenText* scoreText;

int score = 0;

bool pause = false;

bool running = true;
bool menurunning = true;
bool running2 = false;

void logDataFile(const char* message);
void start(SDL_Renderer* ren, SDL_Window* win);
void input();
void update(SDL_Renderer* ren);
void render(SDL_Renderer* ren);
void quit();

// **************************************

// **************************************

int main(int argc, char *argv[])
{
	logDataFile("game Started");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}

	IMG_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("RM Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_RESIZABLE);
	// creating a window

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// creating a renderer

	vector<ScreenText*> MenuItems;

	ScreenText* player1 = new ScreenText(window, "content/Xcelsion Italic.ttf");
	ScreenText* player2 = new ScreenText(window, "content/Xcelsion Italic.ttf");
	ScreenText* optionsText = new ScreenText(window, "content/Xcelsion Italic.ttf");
	ScreenText* quitText = new ScreenText(window, "content/Xcelsion Italic.ttf");

	player1->setText("1 Player", 300, 100, 48);
	player2->setText("2 Player", 300, 200, 48);
	optionsText->setText("OPTIONS", 300, 300, 48);
	quitText->setText("QUIT", 300, 400, 48);

	MenuItems.push_back(player1);
	MenuItems.push_back(player2);
	MenuItems.push_back(optionsText);
	MenuItems.push_back(quitText);

	int currentMenuIndex = 0;

	start(renderer, window);

	while (running)
	{
		
		while (menurunning)
		{
			SDL_RenderClear(renderer);

			for (int i = 0; i < MenuItems.size(); i++)
			{
				if (i == currentMenuIndex)
				{
					MenuItems[i]->setColor(255, 0, 0);
				}
				else
				{
					MenuItems[i]->setColor(255, 255, 255);
				}
				MenuItems[i]->render();
			}

			SDL_RenderPresent(renderer);

			while (SDL_PollEvent(&_event))
			{
				if (_event.type == SDL_KEYDOWN)
				{
					if (_event.key.keysym.sym == SDLK_DOWN)
					{
						currentMenuIndex = (currentMenuIndex + 1) % MenuItems.size();
					}
					//If the down key is pressed, increment the current index.
					else if (_event.key.keysym.sym == SDLK_UP)
					{
						if ((currentMenuIndex - 1) < 0)
						{
							currentMenuIndex = MenuItems.size() - 1;
						}
						else
						{
							currentMenuIndex--;
						}
					}
					//If the up key is pressed, decrement the current index.
				}

				if (_event.type == SDL_KEYDOWN)
				{
					if (_event.key.keysym.sym == SDLK_RETURN && currentMenuIndex == 3)
					{
						running = false;
						menurunning = false;
						running2 = false;
					}

					if (_event.key.keysym.sym == SDLK_RETURN && currentMenuIndex == 0)
					{
						menurunning = false;
						//exits menu loop when the enter key is pressed on the start menu item
					}

					if (_event.key.keysym.sym == SDLK_RETURN && currentMenuIndex == 1)
					{
						menurunning = false;
						running2 = true;
					}

					
				}


			}
		}
		//runs the menu while the bool is true

		SDL_RenderClear(renderer);

		input();


		update(renderer);

		render(renderer);
		scoreText->render();

		SDL_RenderPresent(renderer);

	}

	logFile.close();
	//closing the log file

	quit();

	logDataFile("Game Ended");

	return 0;
}

// *******************************

void logDataFile(const char* message)
{
	logFile << message << std::endl;
}

void start(SDL_Renderer* ren, SDL_Window* win)
{

	logFile.open("game-log.txt");
	//opening log file

	aGameItem.x = 200;
	aGameItem.y = 300;
	aGameItem.width = 50;
	aGameItem.height = 50;
	aGameItem.ren = ren;
	aGameItem.start();
	//setting values for player item

	aBulletController.start(aGameItem.x, aGameItem.y);
	aBulletController.add(aBulletController.X, aBulletController.Y);
	aBulletController.add(aBulletController.X, aBulletController.Y);
	aBulletController.add(aBulletController.X, aBulletController.Y);
	aBulletController.add(aBulletController.X, aBulletController.Y);
	//adding bullets to the bullet controller

	aGameItemPlayer2.x = 200;
	aGameItemPlayer2.y = 100;
	aGameItemPlayer2.width = 50;
	aGameItemPlayer2.height = 50;
	aGameItemPlayer2.ren = ren;
	aGameItemPlayer2.start();
	//setting values for player 2

	aBulletControllerPlayer2.start(aGameItemPlayer2.x, aGameItemPlayer2.y);
	aBulletControllerPlayer2.add(aBulletControllerPlayer2.X, aBulletControllerPlayer2.Y);
	aBulletControllerPlayer2.add(aBulletControllerPlayer2.X, aBulletControllerPlayer2.Y);
	aBulletControllerPlayer2.add(aBulletControllerPlayer2.X, aBulletControllerPlayer2.Y);
	aBulletControllerPlayer2.add(aBulletControllerPlayer2.X, aBulletControllerPlayer2.Y);
	//adding bullet to player 2 bullet controller


	aSquareList.push_back(RM_Square(600, 100, 75, 75, ren));
	aSquareList.push_back(RM_Square(700, 250, 75, 75, ren));
	aSquareList.push_back(RM_Square(800, 400, 75, 75, ren));
	aSquareList.push_back(RM_Square(900, 550, 75, 75, ren));
	//adding squares(enemies) to list

	for (int i = 0; i < 4; i++)
	{

	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
	}
	else
	{
		SOUND_shot = Mix_LoadWAV("./content/ShotSound.wav");
		SOUND_backmusic = Mix_LoadMUS("./content/atmospace_jungle.wav");
		Mix_VolumeChunk(SOUND_shot, 128); //The volume of this sound (0-255)
		Mix_VolumeMusic(32); //The volume for the music (0-255)
	}

	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could access Joystick SDL_Error: %s\n", SDL_GetError());
	}
	//initialise gamepad

	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No GameControllers connected! \n");
		//check for gamepad, if present, load first gamepad
	}
	else
	{
		aGamePad = SDL_JoystickOpen(0);
		printf("GameController connected! \n");
		if (aGamePad == NULL)
		{
			printf("Error - %s \n", SDL_GetError());
		}
		gamePad = true;
	}

	scoreText = new ScreenText(win, "content/Xcelsion Italic.ttf");

	Mix_PlayMusic(SOUND_backmusic, -1);
}


void input()
{
	aJoystick.x = SDL_JoystickGetAxis(aGamePad, 0) / 327680.0f;
	aJoystick.y = SDL_JoystickGetAxis(aGamePad, 1) / 327680.0f;
	//getting values (-1 to 1) for the joystick input

	//printf("Joystick X: %f -- Y: %f \n", aJoystick.x, aJoystick.x);

	aGameItem.velocity.x = aJoystick.x;
	aGameItem.velocity.y = aJoystick.y;
	//setting player velcity to the joytsick input

	while (SDL_PollEvent(&_event))
	{
		if (_event.type == SDL_JOYBUTTONDOWN)
		{
			if (_event.jbutton.button == 0)
			{
				printf("Button 0 - pressed \n");
				RM_Vector2D shootVel;
				shootVel.x = 0.17;
				int rangeY = 1 - 0 + 1;
				shootVel.y = (rangeY / 100);
				aBulletController.shoot(shootVel);
				//calling shoot funtion on button press
			}
		}
		//gamepad inputs *********************************************

		if (_event.type == SDL_QUIT)
		{
			running = false;
		}
		//stopping game loop

		if (running2)
		{
			if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_a)
				{
					aGameItem.KEY_LEFT = true;
				}
				else if (_event.key.keysym.sym == SDLK_d)
				{
					aGameItem.KEY_RIGHT = true;
				}
				else if (_event.key.keysym.sym == SDLK_w)
				{
					aGameItem.KEY_UP = true;
				}
				else if (_event.key.keysym.sym == SDLK_s)
				{
					aGameItem.KEY_DOWN = true;
				}
			}

			if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_a)
				{
					aGameItem.KEY_LEFT = false;
				}
				else if (_event.key.keysym.sym == SDLK_d)
				{
					aGameItem.KEY_RIGHT = false;
				}
				else if (_event.key.keysym.sym == SDLK_w)
				{
					aGameItem.KEY_UP = false;
				}
				else if (_event.key.keysym.sym == SDLK_s)
				{
					aGameItem.KEY_DOWN = false;
				}
			}
			//getting inputs for player 1 movement

			if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_LEFT)
				{
					aGameItemPlayer2.KEY_LEFT = true;
				}
				else if ( _event.key.keysym.sym == SDLK_RIGHT)
				{
					aGameItemPlayer2.KEY_RIGHT = true;
				}
				else if ( _event.key.keysym.sym == SDLK_UP)
				{
					aGameItemPlayer2.KEY_UP = true;
				}
				else if ( _event.key.keysym.sym == SDLK_DOWN)
				{
					aGameItemPlayer2.KEY_DOWN = true;
				}
			}

			if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_LEFT)
				{
					aGameItemPlayer2.KEY_LEFT = false;
				}
				else if ( _event.key.keysym.sym == SDLK_RIGHT)
				{
					aGameItemPlayer2.KEY_RIGHT = false;
				}
				else if (_event.key.keysym.sym == SDLK_UP)
				{
					aGameItemPlayer2.KEY_UP = false;
				}
				else if (_event.key.keysym.sym == SDLK_DOWN)
				{
					aGameItemPlayer2.KEY_DOWN = false;
				}
			}
			//getting inputs for player 2 movement

			if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_SPACE)
				{
					Mix_PlayChannel(-1, SOUND_shot, 0);
					RM_Vector2D shootVel;
					shootVel.x = 0.17;
					int rangeY = 1 - 0 + 1;
					shootVel.y = (rangeY / 100);
					aBulletController.shoot(shootVel);
				}
				// calling the shoot function for player 1 on space key pressed

				if (_event.key.keysym.sym == SDLK_KP_ENTER)
				{
					Mix_PlayChannel(-1, SOUND_shot, 0);
					RM_Vector2D shootVel;
					shootVel.x = 0.17;
					int rangeY = 1 - 0 + 1;
					shootVel.y = (rangeY / 100);
					aBulletControllerPlayer2.shoot(shootVel);
				}
			}

		}
		else
		{
			if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_a || _event.key.keysym.sym == SDLK_LEFT)
				{
					aGameItem.KEY_LEFT = true;
				}
				else if (_event.key.keysym.sym == SDLK_d || _event.key.keysym.sym == SDLK_RIGHT)
				{
					aGameItem.KEY_RIGHT = true;
				}
				else if (_event.key.keysym.sym == SDLK_w || _event.key.keysym.sym == SDLK_UP)
				{
					aGameItem.KEY_UP = true;
				}
				else if (_event.key.keysym.sym == SDLK_s || _event.key.keysym.sym == SDLK_DOWN)
				{
					aGameItem.KEY_DOWN = true;
				}
			}
			// getting input from arrow keys and wasd to move aGameitem

			if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_a || _event.key.keysym.sym == SDLK_LEFT)
				{
					aGameItem.KEY_LEFT = false;
				}
				else if (_event.key.keysym.sym == SDLK_d || _event.key.keysym.sym == SDLK_RIGHT)
				{
					aGameItem.KEY_RIGHT = false;
				}
				else if (_event.key.keysym.sym == SDLK_w || _event.key.keysym.sym == SDLK_UP)
				{
					aGameItem.KEY_UP = false;
				}
				else if (_event.key.keysym.sym == SDLK_s || _event.key.keysym.sym == SDLK_DOWN)
				{
					aGameItem.KEY_DOWN = false;
				}
			}

			if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
			{
				if (_event.key.keysym.sym == SDLK_SPACE)
				{
					Mix_PlayChannel(-1, SOUND_shot, 0);
					RM_Vector2D shootVel;
					shootVel.x = 0.17;
					int rangeY = 1 - 0 + 1;
					shootVel.y = (rangeY / 100);
					aBulletController.shoot(shootVel);
				}
				// calling the shoot function on space key pressed
			}
		}

		
		if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
		{
			if (_event.key.keysym.sym == SDLK_m)
			{
				if (Mix_PlayingMusic() == 0)
				{
					Mix_PlayMusic(SOUND_backmusic, -1);
					printf("music playing \n");
					//play the music if no music is playing
				}
				else
				{
					Mix_HaltMusic();
				}
			}
		}

		if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
		{
			if (_event.key.keysym.sym == SDLK_ESCAPE && menurunning == false)
			{
				menurunning = true;
				score = 0;
				aGameItem.x = 200;

				for (int i = 0; i < aSquareList.size(); i++)
				{
					aSquareList[i].x = 925;
				}
				//resets the score and sqaure positions

				std::string scorestring = "Score: " + std::to_string(score);
				scoreText->setText(scorestring.c_str(), 10, 10, 24);

			}
			//going back to menu when escape is pressed, resets score

			if (_event.key.keysym.sym == SDLK_u && pause == true)
			{
				pause = false;
				SDL_Log("Game unpaused");
			}

			if (_event.key.keysym.sym == SDLK_p && pause == false)
			{
				pause = true;
				SDL_Log("Game Paused");
			}
			//pausing the game when p is pressed

		}

	}
}

void update(SDL_Renderer* ren)
{

	if (pause == true)
	{

	}

	if (pause == false)
	{
		if (running2)
		{
			aGameItemPlayer2.update(gamePad);
			aBulletControllerPlayer2.update();

			aBulletControllerPlayer2.X = aGameItemPlayer2.x;
			aBulletControllerPlayer2.Y = aGameItemPlayer2.y;

			for (int i = 0; i < aSquareList.size(); i++)
			{
				if (aGameItemPlayer2.collision(aSquareList[i]))
				{
					SDL_Log("Player + Sqaure collision");
					menurunning = true;

					score = 0;

					for (int i = 0; i < aSquareList.size(); i++)
					{
						aSquareList[i].x = 925;
					}
					//resets the score and sqaure positions
				}

				if (aBulletControllerPlayer2.collision(aSquareList[i]))
				{
					int rangeY = 550 - 0 + 1;
					int rangeX = 300 - 0 + 1;
					// random numbers range max - min + 1

					int numy = rand() % rangeY;
					int numx = rand() % rangeX + 600;

					aSquareList[i].x = numx;
					aSquareList[i].y = numy;
					// moving aSquare to random locations

					SDL_Log("Collision");

					score = score + 10;

					std::string scorestring = "Score: " + std::to_string(score);
					scoreText->setText(scorestring.c_str(), 10, 10, 24);
				}
			}
			//looping through the collion check for each square
			
		}

		aGameItem.update(gamePad);

		aBulletController.update();

		for (int i = 0; i < aSquareList.size(); i++)
		{
			aSquareList[i].update();
		}
		//calling update functions

		aBulletController.X = aGameItem.x;
		aBulletController.Y = aGameItem.y;
		//setting Bullet controller location to Game item location

		for (int i = 0; i < aSquareList.size(); i++)
		{
			if (aGameItem.collision(aSquareList[i]))
			{
				SDL_Log("Player + Sqaure collision");
				menurunning = true;
				score = 0;

				for (int i = 0; i < aSquareList.size(); i++)
				{
					aSquareList[i].x = 925;
				}
				//resets the score and sqaure positions

				std::string scorestring = "Score: " + std::to_string(score);
				scoreText->setText(scorestring.c_str(), 10, 10, 24);
			}

			if (aBulletController.collision(aSquareList[i]))
			{
				int rangeY = 550 - 0 + 1;
				int rangeX = 300 - 0 + 1;
				// random numbers range max - min + 1

				int numy = rand() % rangeY;
				int numx = rand() % rangeX + 600;

				aSquareList[i].x = numx;
				aSquareList[i].y = numy;
				// moving aSquare to random locations

				SDL_Log("Collision");

				score = score + 10;

				std::string scorestring = "Score: " + std::to_string(score);
				scoreText->setText(scorestring.c_str(), 10, 10, 24);
			}
		}
		//looping through the collion check for each square
	}

}

void render(SDL_Renderer* ren)
{
	if (running2)
	{
		aGameItemPlayer2.render();
		aBulletControllerPlayer2.render(ren);
	}

	aGameItem.render();
	aBulletController.render(ren);

	for (auto& square : aSquareList)
	{
		square.render();
	}
	//rendering all the sqaures in the list

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	// sets background to black after every render
}

void quit()
{
	logFile.close();
	//closing log file

	Mix_FreeChunk(SOUND_shot);
	Mix_FreeMusic(SOUND_backmusic);
	Mix_CloseAudio();

	SDL_JoystickClose(aGamePad);
	aGamePad = NULL;


	SDL_Quit();
}









// ****************************************************



//bool collision()
//{
//	float left1 = aGameItem.x;
//	float right1 = aGameItem.x + aGameItem.width;
//	float top1 = aGameItem.y;
//	float bottom1 = aGameItem.y + aGameItem.height;
//	// finding edges of gameItem
//
//	float left2 = aSquare.x;
//	float right2 = aSquare.x + aSquare.w;
//	float top2 = aSquare.y;
//	float bottom2 = aSquare.y + aSquare.h;
//	// finding egdes on RM_Square
//
//	if (left1 > right2)
//	{
//		return false;
//	}
//
//	if (right1 < left2)
//	{
//		return false;
//	}
//
//	if (top1 > bottom2)
//	{
//		return false;
//	}
//
//	if (bottom1 < top2)
//	{
//		return false;
//	}
//
//	return true;
//}




//if (collision())
//{
//	int rangeX = 950 - 400 + 1;
//	int rangeY = 550 - 0 + 1;
//	// random numbers range max - min + 1
//	int numx = rand() % rangeX;
//	int numy = rand() % rangeY;

//	aSquare.x = numx;
//	aSquare.y = numy;
//	// moving aSquare to random locations

//	SDL_Log("Collision");
//}

