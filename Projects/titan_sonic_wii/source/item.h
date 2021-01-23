/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <SDL/SDL.h>
#include <vector>
#include "base.h"
#ifndef ITEM_H
#define ITEM_H
class item:public baseclass
{
	SDL_Rect box;
	int item_size;
	SDL_Surface* image;
	SDL_Rect clips[8];
	double frame;	
	public:
	item(SDL_Surface*, int x, int y, int xvel, int yvel);
	void move();
	void show(SDL_Surface* screen);
	SDL_Rect* getRect();
};
#endif