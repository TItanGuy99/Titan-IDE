/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
// normal includes
#include <stdlib.h>
#include <time.h>
#include <gccore.h>
#include <wiiuse/wpad.h> 
#include <asndlib.h>
#include <mp3player.h>

// SDL includes
#include <SDL/sdl.h>
#include <SDL/sdl_image.h>
#include <SDL/SDL_mixer.h>

#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "base.h"
#include "player.h"
//#include "bullet.h"
//#include "enemy.h"
#include "obstacle.h"
#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount, buttonCount, save_clock;
	SDL_Surface *screen, *block, *blocksBG, *hud;
	SDL_Surface *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, energy1, energy2, energy3, energy4, numb1, press_start1, clip_number[10], m_screen_rect, rect_hud;
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<obstacle*> obstacles;
	std::vector<obstacle*> obstacles_bkp;
	bool direction[2];
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename, int r, int g, int b);
	void loadmap(const char* filename, bool isBG);
	void showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock);
	void menu();
	void end_game();
	void handleEvents();
	void restart_game();
	void control_bg(char d);
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
