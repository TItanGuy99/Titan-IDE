/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <fstream>
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
#include <vector>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "base.h"
#include "player.h"
#include "vmu.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"
#ifndef GAME_H
#define GAME_H
#include <kos.h>

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount, buttonCount, count_end, sfx_enemies, sfx_hurt, save_clock, sfx_ring;
	SDL_Surface *screen, *block, *blocksBG, *ene, *ene2, *bos, *ite, *hud, *energy;
	SDL_Surface *energy_life, *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface  *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, energy1, energy2, energy3, energy4, numb1, press_start1, rect_cloud1, rect_cloud2, rect_cloud3;
	SDL_Rect clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<item*> items;
	std::vector<item*> items_bkp;
	std::vector<enemy*> enemies;
	std::vector<enemy*> enemies_bkp;
	std::vector<boss*> the_boss;
	std::vector<boss*> the_boss_bkp;
	bool direction[2];
	bool music_boss, boss_defeated;
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename, int r, int g, int b);
	void loadmap(const char* filename, bool isBG);
	void showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock);
	void menu();
	void end_game();
	void handleEvents();
	void restart_game();
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
