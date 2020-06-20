/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include <SDL/SDL.h>
#ifndef BASE_H
#define BASE_H

class baseclass{
	   protected:
                bool collision(SDL_Rect* rec1,SDL_Rect* rec2);  //make the collision function, it'll return true if there was a collision between rec1 and rec2

	   public:
	   static SDL_Rect coord;
	   static const int TILE_SIZE=32;
};

#endif