/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "player.h"

////Main function for the player
player::player(SDL_Surface *img)
{
	is_shooting=false;
	image=img;
	count_standing=0;
	player_size = 32;
	box.x=140;
	box.y=100;
	box.w=32;
	box.h=player_size;
	lives=3;
	countvel=0;
	xvel=0;
	my_x=0;
	my_y=0;
	yvel=0;
	upvel=0;
	map_y=0;
	looking_up=false;
	looking_down=false;
	count_shooting=0;
	direction='u';
	colliding_obstacle=false;
	
	for(int i=0;i<32;i++)
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

////To destroy the player in the memory
player::~player()
{
	SDL_FreeSurface(image);
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
	if(!colliding_obstacle)
	{
		if(direction!='z')
		{
			frame+=0.1;
			save_direction = direction;
				
			if(direction=='u' && frame >= 15.4)
			{
				frame=12;
			} 
			else if(direction=='d' && frame >= 3.4)
			{
				frame=0;
			}	
			else if(direction=='l' && frame >= 7.4)
			{
				frame=4;
			}	
			else if(direction=='r' && frame >= 11.4)
			{
				frame=8;
			}	
		}
		else
		{
			if(direction=='u')
			{
				frame=12;
			} 
			else if(direction=='d')
			{
				frame=0;
			}	
			else if(direction=='l')
			{
				frame=4;
			}	
			else if(direction=='r')
			{
				frame=8;
			}	
			else
			{			
				if(save_direction=='u')
				{
					frame=12;
				} 
				else if(save_direction=='d')
				{
					frame=0;
				}	
				else if(save_direction=='l')
				{
					frame=4;
				}	
				else if(save_direction=='r')
				{
					frame=8;
				}			
			}
		}
	}
}

/////Set that the player is moving
void player::setMoving(bool b)
{
	if(!b)
	{
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
	
		if(direction=='u')
		{
			frame=12;
		} 
		else if(direction=='d')
		{
			frame=0;
		}	
		else if(direction=='l')
		{
			frame=4;
		}	
		else if(direction=='r')
		{
			frame=8;
		}	
	
}

/////Get a value for the variable mapy
int player::get_mapy()
{
	return map_y;
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

bool player::return_colliding()
{
	if(colliding_obstacle)
	{
		return true;
	}
	else
	{
		return false;
	}
    
}

void player::set_colliding(bool collision_blocks)
{
	if(collision_blocks)
	{
		colliding_obstacle=true;
	}
	else
	{
		colliding_obstacle=false;
	}
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
	frame=0;
	is_shooting=false;
	health=200;
	box.x=140;
	box.y=100;
	map_y=0;
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
