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

#include <malloc.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "base.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"

// Audio
#include "sfxdeath_raw.h"
#include "sfxenemies_raw.h"
#include "sfxring_raw.h"
#include "sfxjump_raw.h"

#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int joystickCount, buttonCount, count_end, save_clock;
	void *sounds[4];
	size_t sound_size[4];
	SDL_Surface *screen, *block, *blocksBG, *ene, *ene2, *bos, *ite, *hud, *energy;
	SDL_Surface *energy_life, *numb, *m_screen, *press_start, *titan_logo, *game_over, *final_screen;
	SDL_Surface  *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;  
	SDL_Rect camera, numb1, rect_hud, press_start1, m_screen_rect;
	SDL_Rect clip_number[10];
	Mix_Chunk *sfx_enemies, *sfx_hurt,  *sfx_ring, *sfx_jump;
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
	void play_music(Mix_Music *myAudio, int repeat);
	void play_sfx(Mix_Chunk *mysfx, int channel, int volume, int repeat);
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
