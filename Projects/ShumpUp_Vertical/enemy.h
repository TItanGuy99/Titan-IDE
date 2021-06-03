/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include <SDL/SDL.h>

#include <vector>

#include "base.h"

#ifndef ENEMY_H
#define ENEMY_H
class enemy: public baseclass {
  SDL_Rect box;
  int xvel, yvel, life, count_x, enemy_size, save_x, save_y, player_x, count_bullets, distance;
  SDL_Surface * image;
  bool ground, dead;
  SDL_Rect clips[8];
  double frame;
  char direction;
  public:
    enemy(SDL_Surface * , int x, int y, int xvel, int yvel);
  SDL_Surface * getImage();
  void move(std::vector < std::vector < int > > & );
  void show(SDL_Surface * );
  void setDirection(char);
  void setX(int);
  void getPlayerX(int);
  void setLife();
  int getY();
  int getEnemyY();
  int getCount_Bullets();
  bool getDead();
  int getInitialY();
  char getDirection();
  void subtractLife();
  int getLife();
  SDL_Rect * getRect();
};
#endif