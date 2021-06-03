/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include <fstream>

#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want

#include <vector>

#include <dreamroq/dreamroqlib.h>

#include <SDL.h>

#include <SDL/SDL_dreamcast.h>

#include <SDL_image.h>

#include "sh4_math.h"

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <time.h>

#include "base.h"

#include "player.h"

#include "vmu.h"

#include "animfonts.h"

#include "animloop.h"

#include "rumble.h"

#include "enemy.h"

#include "enemy.h"

#include "boss.h"

#include "item.h"

#ifndef GAME_H
#define GAME_H#include <kos.h>

class game: public baseclass {
  SDL_Joystick * joystick;
  int joystickCount, buttonCount, count_end, sfx_enemies, sfx_hurt, save_clock, sfx_ring, axi_X, axi_Y;
  SDL_Surface * screen, * block, * blocksBG, * ene, * ene2, * bos, * ite, * hud, * energy, * spritePlayer;
  SDL_Surface * energy_life, * numb, * m_screen, * press_start, * game_over, * final_screen;
  SDL_Rect camera, cameraPVR, energy1, energy2, energy3, energy4, numb1, press_start1, rect_cloud1, rect_cloud2, rect_cloud3;
  SDL_Rect clip_number[10];
  std::vector < std::vector < int > > map;
  std::vector < std::vector < int > > mapBG;
  std::vector < item * > items;
  std::vector < item * > items_bkp;
  std::vector < enemy * > enemies;
  std::vector < enemy * > enemies_bkp;
  std::vector < boss * > the_boss;
  std::vector < boss * > the_boss_bkp;
  bool direction[2], is_paused;
  bool music_boss, boss_defeated;
  SDL_Rect finish;
  SDL_Surface * load_image(const char * filename,
    const char * extension = "pvr",
      int r = 1,
      int g = 1,
      int b = 1);
  void loadmap(const char * filename, bool isBG);
  void showmap(std::vector < std::vector < int > > currentMap, bool checkY, SDL_Surface * currentBlock);
  void menu();
  void end_game();
  void draw_hud();
  void f_game_over();
  void handleEvents();
  void restart_game();
  void update_screen();
  void play_video(int number_video);
  bool mount_romdisk(char * filename, char * mountpoint);
  void load_assets(int fileToLoad);
  void clr_menu_mem();
  void clr_stage1_mem();
  bool running, all_running;
  static
  const int SCREEN_WIDTH = 320;
  static
  const int SCREEN_HEIGHT = 240;
  animfonts * present_text1;
  animfonts * completed_text;
  rumble * rumble_pack;
  vmu * my_vmu;
  player * player1;
  public:
    game();
  void start();
};

#endif