/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <SDL/SDL.h>
#include <vector>
#include "base.h"
#ifndef PLAYER_H
#define PLAYER_H

class player:baseclass{
	SDL_Rect box;
	SDL_Surface* image;
	int xvel, yvel, upvel, countvel, speed, player_size;
	SDL_Rect clips[40];
	bool ground,jump,on_top,animation_limit,is_colliding, is_shooting;
	char direction;
	double frame;
	bool moving;
	int lives;
	int health;
	int count_shooting;
	int map_y;
	public:
	SDL_Surface* getImage();
	player(SDL_Surface* img);
	~player();
    SDL_Rect* getRect();
	void setXvel(int vel);
	int getXvel();
	void move(const std:: vector<std::vector<int> >&map);
	void show(SDL_Surface* screen);
	void setJump();
	void setMoving(bool);
	void resetPosition();
	void setFrame();
	bool getMoving();
	void setDirection(char);
	char getDirection();
	int getHealth();
	int getY();
	int getX();
	int getYvel();
	int get_mapy();
	bool getJump();
	void setHealth(int);
	void setLives(int h);
	int getLives();
};
#endif