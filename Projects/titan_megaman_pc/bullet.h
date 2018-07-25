/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <SDL/SDL.h>    //for SDL
#include <iostream>             //if we want to write out something, probobly it can be deleted if you don't want
 
#ifndef BULLET_H        //avoid multiple indclusion
#define BULLET_H
 
class bullet{
        SDL_Rect box;   //bounding box (for the blitting and for the collision detection)
        int xvel,yvel;  //the velocity (speed)
        SDL_Surface* image;     //the image of the bullet
        public:
        bullet(SDL_Surface* img,int x,int y,int xvel,int yvel); //constructor
        //obvious
        void move();
        void show(SDL_Surface* screen);
        SDL_Rect* getRect();
};
 
#endif