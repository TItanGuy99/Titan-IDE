/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "player.h"

////Main function for the player
player::player(SDL_Surface *img)
{
	is_shooting=false;
	image=img;
	count_standing=0;
	player_size = 64;
	box.x=130;
	box.y=90;
	box.w=32;
	box.h=player_size;
	lives=3;
	countvel=0;
	xvel=0;
	yvel=0;
	upvel=0;
	on_wall=false;
	is_colliding=false;
	looking_up=false;
	looking_down=false;
	count_shooting=0;
	direction='z';
	
	for(int i=0;i<3;i++)
	{
		clips[i].x=i*player_size;
		clips[i].y=0;
		clips[i].w=player_size;
		clips[i].h=player_size;
	}
	animation_limit=0;
	ground=0;
	direction='r';
	frame=0.0;
	moving=0;
	on_top=0;
	health=200;
}

/////Check the X and Y, Width and Height of the player
SDL_Rect* player::getRect()
{
	return &box;
}

/////Get the X vel
int player::getXvel()
{
	return xvel;
}


/////Set the X vel
void player::setXvel(int vel)
{
	xvel=vel;
}

///// Show player on the screen
void player::show(SDL_Surface* screen)
{
	SDL_BlitSurface(image,&clips[(int)(frame)],screen,&box);
}

///// Move the player
void player::move(const std:: vector<std::vector<int> >&map)
{	
	if(frame<2.4)
	{
		frame+=0.1;
	}
	else
	{
		frame=0;
	}
	
	switch(direction)
	{
		case 'l':
			box.x-=2;
		break;
		
		case 'r':
			if(box.x<260)
				box.x+=2;
		break;
		
		case 'u':
			box.y-=2;
		break;
	
		case 'e':
			if(box.x<260) {
				box.x+=2;
				box.y-=2;				
			}
		break;
		
		case 'q':
			box.y-=2;
			box.x-=2;
		break;
		
		case 'c':
			if(box.y<180) {
				box.x+=2;
				box.y+=2;	
			}
		break;
		
		case 'x':
			if(box.y<180) {
				box.y+=2;
				box.x-=2;	
			}
		break;
		
		case 'd':
			if(box.y<180)
				box.y+=2;
		break;
	}
}

/////Set that the player is moving
void player::setMoving(bool b)
{
	if(!b)
	{
		on_wall=false;
		frame=0;
	}
	
	moving=b;
}

/////Set that the player is looking up or not
void player::setLookingUp(bool b)
{
	looking_up=b;
}

/////Set that the player is down or not
void player::setDown(bool b)
{
	looking_down=b;
}

/////Check if the player is mobing or not
bool player::getMoving()
{
	return moving;
}

////Set the direction
void player::setDirection(char c)
{
	direction=c;
}

/////Get y of the player
int player::getY()
{
    return box.y;	
}

/////Get x of the player
int player::getX()
{
    return box.x;	
}

/////Check the health of the player
int player::getHealth()
{
    return health;	
}

/////Get the y vel of the player
int player::getYvel()
{
	return yvel;
}

///// Set the player's health
void player::setHealth(int h)
{
    health=h;	
}

///// Set the player's lives
void player::setLives(int h)
{
    lives=h;
}

///// Check how many lives the player has
int player::getLives()
{
	return lives;
}

///// Reset the position in the map
void player::resetPosition()
{
	on_wall=false;
	frame=0;
	is_shooting=false;
	health=200;
	box.x=130;
	box.y=90;
}

///// Check the direction
char player::getDirection()
{
	is_shooting=false;
    return direction;	
}

///// Get the player's image
SDL_Surface* player::getImage()
{
	return image;
}
