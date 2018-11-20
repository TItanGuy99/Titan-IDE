/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "obstacle.h"

/////Main function for the item
obstacle::obstacle(int x, int y)
{
	box.x=x;
	box.y=y;
}

///// Get Y,X, width and height of the enemy
SDL_Rect* obstacle::getRect()
{
	return &box;
}