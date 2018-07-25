/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <SDL/SDL.h>
#include <vector>
#include "base.h"
#ifndef BOSS_H
#define BOSS_H
class boss:public baseclass
{
	SDL_Rect box;
	int xvel,yvel,life,count_x,boss_size,save_x,save_y;
	SDL_Surface* image;
	bool ground, collision_with_player;
	SDL_Rect clips[8];
	double frame;
	char direction;	
	public:
	boss(SDL_Surface*, int x, int y, int xvel, int yvel);
	SDL_Surface* getImage();
	void move(std::vector<std::vector<int> >&);
	void show(SDL_Surface*);
	void setDirection(char);
	void setY(int);
	void setLife();
	void setCollision(bool);
	bool getCollision();
	int getY();
	int getLife();
	int getInitialY();
	char getDirection();	
	int subtractLife();
	SDL_Rect* getRect();
};
#endif