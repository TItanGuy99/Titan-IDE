/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <fstream>
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
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
#include "obstacle.h"
#include "vmu.h"
#include "animfonts.h"
#include "animloop.h"
#include "rumble.h"
#ifndef GAME_H
#define GAME_H
#include <kos.h>

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount;
	int buttonCount, axi_X, axi_Y;
	SDL_Surface *screen, *block, *blocksBG, *hud, *spritePlayer;
	SDL_Surface *m_screen, *press_start, *titan_logo, *game_over, *final_screen; 
	SDL_Rect camera, cameraPVR, energy1, energy2, energy3, energy4, press_start1, clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<obstacle*> obstacles;
	std::vector<obstacle*> obstacles_bkp;
	bool direction[2], is_paused;
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename, const char* extension, int r, int g, int b);
	void loadmap(const char* filename, bool isBG);
	void showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock);
	void menu();
	void handleEvents();
	void control_bg(char d);
	void end_game();
	void draw_hud();
	void f_game_over();
	void erase_bullets();
	void control_bg();
	void update_screen();
	bool mount_romdisk(char *filename, char *mountpoint);
	void load_assets(int fileToLoad);
	void clr_menu_mem();
	void clr_stage1_mem();
	bool running, all_running;
	static const int SCREEN_WIDTH=320;
	static const int SCREEN_HEIGHT=240;
	animfonts* present_text1;
	animfonts* completed_text;
	rumble* rumble_pack;
	vmu* my_vmu;
	player* player1;
        public:
        game();
        ~game();
        void start();
};

#endif