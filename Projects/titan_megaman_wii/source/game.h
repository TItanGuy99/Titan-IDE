/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
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

#include <malloc.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

// Audio
#include "sfxbullet_raw.h"
#include "sfxenemy_raw.h"
#include "sfxhurt_raw.h"
#include "sfxjump_raw.h"

// include generated header
#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount;
	int buttonCount;
	void *sounds[4];
	size_t sound_size[4];
	SDL_Surface *screen, *background, *block, *blocksBG, *bul, *ene, *ene2, *hud, *energy;
	SDL_Surface *energy_life, *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface  *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, energy1, energy2, energy3, energy4, numb1, press_start1, m_screen_rect, rect_hud;
	SDL_Rect clip_number[10];
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > mapBG;
	std::vector<bullet*> bullets;
	std::vector<enemy*> enemies;
	std::vector<enemy*> enemies_bkp;
	bool direction[2];
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename, int r, int g, int b);
	void loadmap(const char* filename, bool isBG);
	void showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock);
	void menu();
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
