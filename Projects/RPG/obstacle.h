/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include <SDL/SDL.h>

#include <vector>

#include "base.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H
class obstacle: public baseclass {
  SDL_Rect box;
  public:
    obstacle(int x, int y);
  SDL_Rect * getRect();
};
#endif