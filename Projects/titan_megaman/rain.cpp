/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "rain.h"
 
rain::rain(SDL_Surface* img,int x,int y,int xVel,int yVel)  //constructor
{
        //just set all of the variables, nothing new in here
        box.x=x;
        box.y=y;
        image=img;
        box.w=image->w;
        box.h=image->h;
        xvel=xVel;
        yvel=yVel;
}
 
void rain::move()
{
        box.x+=xvel;
        box.y+=yvel;
}
 
void rain::show(SDL_Surface* screen)
{
        //blit it to the screen
        SDL_BlitSurface(image,NULL,screen,&box);
}
 
 
SDL_Rect* rain::getRect()
{
        //return the address of the bound box (for collision detection)
        return &box;
}
//that was one of the simplest class, nothing tricky.