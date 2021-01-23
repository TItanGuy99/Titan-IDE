/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <SDL/SDL.h>
#include <vector>
#include "base.h"
#ifndef PLAYER_H
#define PLAYER_H

class player:baseclass{
	SDL_Rect box;
	SDL_Surface* image;
	int xvel, yvel, upvel, countvel, speed, player_size, count_standing, count_running, my_x, my_y;
	SDL_Rect clips[32];
	bool ground,on_top,animation_limit, is_shooting, looking_up, looking_down, colliding_obstacle;
	char direction, save_direction;
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
	void setMoving(bool);
	void setLookingUp(bool b);
	void setDown(bool b);
	void resetPosition();
	bool getMoving();
	void setDirection(char);
	void set_colliding(bool b);
	char getDirection();
	bool return_colliding();
	int getHealth();
	int getY();
	int getX();
	int getYvel();
	int get_mapy();
	void setHealth(int);
	void setLives(int h);
	int getLives();
};
#endif