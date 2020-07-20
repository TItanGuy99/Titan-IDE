/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include <fstream>
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
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
	SDL_Surface *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen, *windowIcon;
	SDL_Surface *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, energy1, energy2, energy3, energy4, numb1, press_start1, clip_number[10];
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
	void play_music(Mix_Music *myAudio, int repeat);
	void play_sfx(Mix_Chunk *mysfx, int channel, int volume, int repeat);
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
