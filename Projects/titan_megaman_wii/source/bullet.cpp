/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "bullet.h"

//// Main class for the bullers
bullet::bullet(SDL_Surface* img,int x,int y,int xVel,int yVel)  //constructor
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
 
/// Move the bullets on the screen
void bullet::move()
{
        //move the bullet, we just add the velocity (speed) to the position
        box.x+=xvel;
        box.y+=yvel;
}
 
//// Show the bullets on the screen
void bullet::show(SDL_Surface* screen)
{
        //blit it to the screen
        SDL_BlitSurface(image,NULL,screen,&box);
}
 

//// Get X, Y, width and height for the bullet 
SDL_Rect* bullet::getRect()
{
        //return the address of the bound box (for collision detection)
        return &box;
}
//that was one of the simplest class, nothing tricky.