/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include <SDL/SDL.h>

#include <vector>

#include "base.h"

#ifndef ANIMLOOP_H
#define ANIMLOOP_H
class animloop: public baseclass {
  int speed, count_frames;
  SDL_Rect box;
  SDL_Surface * image;
  SDL_Rect clips[32];
  bool is_running;
  double frame, t_frames;
  public:
    animloop(SDL_Surface * , int x, int y, int item_size, double total_frames, bool running, int frame_speed);
  void move();
  void show(SDL_Surface * screen);
  void setRunning(bool running);
};
#endif