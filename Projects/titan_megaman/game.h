/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_dreamcast.h>  
#include <SDL_image.h>
#include "sh4_math.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "vmu.h"
#include "enemy.h"
#ifndef GAME_H
#define GAME_H
#include <kos.h>
//#include <mp3/sndserver.h>

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount, buttonCount, sfx_bullet, sfx_alien, sfx_hurt, save_clock, axi_X, axi_Y;
	SDL_Surface *screen, *block, *blocksBG, *bul, *ene, *ene2, *hud, *energy;
	SDL_Surface *energy_life, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;  
	SDL_Rect camera, cameraPVR, energy1, energy2, energy3, energy4, press_start1;
	SDL_Rect clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<bullet*> bullets;
	std::vector<enemy*> enemies;
	std::vector<enemy*> enemies_bkp;
	bool direction[2];
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename, const char* extension, int r, int g, int b);
	void loadmap(const char* filename, bool isBG);
	void showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock);
	void menu();
	void handleEvents();
	void restart_game();
	void update_screen();
	bool running, all_running;
	static const int SCREEN_WIDTH=320;
	static const int SCREEN_HEIGHT=240;
	player* player1;
        public:
        game();
        ~game();
        void start();
};

#endif
