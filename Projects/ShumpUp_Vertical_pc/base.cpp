/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/

#include "base.h"

////Class to check the collisions
bool baseclass::collision(SDL_Rect* rec1,SDL_Rect* rec2)
{
	if(rec1->y >= rec2->y + rec2->h)
	    return 0;
	if(rec1->x >=rec2->x + rec2->w)
		return 0;
	if(rec1->y + rec1->h <= rec2->y)
	    return 0;
	if(rec1->x+ rec1->w <= rec2->x)
		return 0;
	return 1;
}