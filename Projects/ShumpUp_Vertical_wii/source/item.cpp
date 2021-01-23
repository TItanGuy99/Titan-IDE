/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include "item.h"

/////Main function for the item
item::item(SDL_Surface* img, int x, int y, int xVel, int yVel)
{
	image=img;
	box.x=x;
	box.y=y;
	item_size=16;
	box.w=item_size;
	box.h=item_size;
	direction = rand() % 100 +1;

	for (int i=0;i<8;i++)
	{
		clips[i].x=i*item_size;
		clips[i].y=0;
		clips[i].w=item_size;
		clips[i].h=item_size;
	}
	frame=0;
}

///// Move the item
void item::move()
{
	frame+=0.1;	
			
	if(frame>=3.4)
	{
		frame=0;
	}
	
	if(direction>50) 
	{
		if(box.x<310) {
			box.x+=2;	
		}
		else {
			direction = 0;
		}
	}
	else 
	{
		if(box.x>0) {
			box.x-=2;	
		}
		else {
			direction = 100;
		}		
	}
}

//// Show the item on the screen
void item::show(SDL_Surface* screen)
{
    SDL_Rect tmp={box.x-coord.x,box.y-coord.y,40,40};
	SDL_BlitSurface(image,&clips[(int)(frame)],screen,&tmp);
}

///// Get Y,X, width and height of the enemy
SDL_Rect* item::getRect()
{
	return &box;
}