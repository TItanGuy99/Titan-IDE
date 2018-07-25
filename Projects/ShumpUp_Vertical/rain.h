/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <SDL/SDL.h>    //for SDL
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
 
#ifndef RAIN_H        //avoid multiple indclusion
#define RAIN_H
 
class rain{
        SDL_Rect box;   //bounding box (for the blitting and for the collision detection)
        int xvel,yvel;  //the velocity (speed)
        SDL_Surface* image; 
        public:
        rain(SDL_Surface* img,int x,int y,int xvel,int yvel); //constructor
        //obvious
        void move();
        void show(SDL_Surface* screen);
        SDL_Rect* getRect();
};
 
#endif