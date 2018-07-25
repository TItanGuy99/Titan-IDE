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
#include "bullet.h"
#include "enemy.h"
#include "item.h"
#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount;
	int buttonCount, count_end, count_background, count_animation, count_frames;
	SDL_Surface *screen, *block, *ene, *ene2, *ite, *hud, *energy,*bul;
	SDL_Surface *background;
	SDL_Surface *bg1, *bg2, *bg3, *bg4, *bg5, *bg6, *bg7, *bg8, *bg9, *bg10, *bg11, *bg12, *bg13, *bg14, *bg15, *bg16, *bg17, *bg18, *bg19, *bg20, *bg21;
	SDL_Surface *energy_life, *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface  *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, rect_bg, rect_bg2, rect_bg3, energy1, energy2, energy3, energy4, numb1, press_start1, rect_cloud1, rect_cloud2, rect_cloud3;
	SDL_Rect clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<item*> items;
	std::vector<item*> items_bkp;
	std::vector<enemy*> enemies;
	std::vector<enemy*> enemies_bkp;
	std::vector<bullet*> bullets;
	bool direction[2];
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename); 
	SDL_Surface* load_image2(const char* filename); 
	SDL_Surface* load_image3(const char* filename); 
	SDL_Surface* load_image4(const char* filename); 
	void loadmap(const char* filename);
	void showmap();
	void menu();
	void control_animation();
	void end_game();
	void load_image();
	void load_image2();
	void load_image3();
	void handleEvents();
	void restart_game();
	void control_bg(char d);
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
