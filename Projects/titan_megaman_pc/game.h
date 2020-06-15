/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "base.h"
#include "rain.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount;
	int buttonCount;
	SDL_Surface *screen, *background, *block, *blocksBG, *bul, *ene, *ene2, *hud, *energy;
	SDL_Surface *energy_life, *numb, *goat, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface  *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, energy1, energy2, energy3, energy4, numb1, press_start1;
	SDL_Rect clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<rain*> goats;
	std::vector<bullet*> bullets;
	std::vector<enemy*> enemies;
	std::vector<enemy*> enemies_bkp;
	bool direction[2];
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename); 
	SDL_Surface* load_image2(const char* filename); 
	SDL_Surface* load_image3(const char* filename); 
	void loadmap(const char* filename);
	void showmap();
	void showmapBG();
	void loadBG(const char* filename);
	void menu();
	void load_image();
	void load_image2();
	void load_image3();
	void handleEvents();
	void restart_game();
	bool running;
	static const int SCREEN_WIDTH=320;
	static const int SCREEN_HEIGHT=240;
	player* player1;
        public:
        game();
        ~game();
        void start();
};

#endif
