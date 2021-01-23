/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "player.h"

////Main function for the player
player::player(SDL_Surface *img)
{
	sfx_jump = snd_sfx_load("/stage1/jump.wav"); 
	is_shooting=false;
	image=img;
	player_size = 32;
	box.x=130;
	box.y=128;
	box.w=player_size;
	box.h=player_size;
	lives=3;
	countvel=0;
	xvel=0;
	yvel=0;
	upvel=0;
	map_y=0;
	is_colliding=false;
	count_shooting=0;
	
	for(int i=0;i<14;i++)
	{
		clips[i].x=i*player_size;
		clips[i].y=0;
		clips[i].w=player_size;
		clips[i].h=player_size;
	}
	animation_limit=0;
	ground=0;
	jump = 0;
	direction='r';
	frame=0.0;
	moving=0;
	on_top=0;
	health=200;
}

////To destroy the player in the memory
player::~player()
{
	snd_sfx_unload_all();
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
	
   if(jump)
	{		
		if(direction=='r')
		{
			frame=5;
		}
		if(direction=='l')
		{
			frame=12;
		}
		
	}
	else if(moving)
	{
		frame+=0.2;
		if(direction=='r' && frame >= 4.4)
		{
			frame=2;
		}else if(direction=='l' && frame>=11.4)
		{
			frame=9;
		}	
	}
	else if(!is_shooting)
	{
		frame+=0.1;
		if(direction=='r' && frame >= 1.4)
		{
			frame=0.0;
		}else if(direction=='l' && frame >= 8.4)
		{
			frame=7;
		}
	}
	else
	{
		count_shooting+=1;
		if(count_shooting==10)
		{
			count_shooting=0;
			is_shooting=false;
		}
	}
		
	int start=(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-
	(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	
	if(start<0)
		start=0;
	if(end>map[0].size())
       end=map[0].size();	

   bool nc=0;
   ground=0;
   
	for(int i=0; i<map.size(); i++)
		for(int j=start; j<end;j++)
		{
			if(map[i][j]==0)
            continue;
		  
		  SDL_Rect destrect={j*player_size-baseclass::coord.x+player_size-20,i*player_size-baseclass::coord.y,player_size/2,player_size};
		  
		  if(collision(&box,&destrect))
		  {
			  nc=1;
			  
			  if(destrect.y>box.y+box.h-6.1)
			  {
				if(yvel!=0)
				{
					//box.y -=1;
					//map_y-=1;
				}
				  
				ground=1;
				yvel=0;				
			  }
			  else if(destrect.y+destrect.h<=box.y+6.1)
			  {
				box.x++;
			  }
			  
			  if(box.x+box.w>=destrect.x-6.1 && box.y+box.h>=destrect.y+6.6 && box.x
			  +box.w<=destrect.x+20)
			  {
				  xvel=0;
				  box.x--;
				  is_colliding=true;
			  }
			  else if(box.x<=destrect.x+destrect.w && box.y+box.h>=destrect.y+6.6)
			  {
				  xvel=0;
				  box.x++;
				  is_colliding=true;
			  }
		  }
		}
		
	if(!nc && !jump)
	{
		yvel=8;
	}
	if(jump && on_top && !ground)
	{		
		if(yvel<4)
		yvel++;
	}
	else if(ground)
	{
		animation_limit=0;
		on_top=0;
		
		if(upvel==0)
			jump=0;
	}

	if(upvel!=0)
	{
	    yvel=-4;
		countvel-=4;
		
//////////////////////////////////////////////////////

is_colliding=false;
		
/////////////////////////////////////////////////////
		
		if(countvel<upvel)
		{
			on_top=1;
			upvel=0;
		}
	}

	
	if(!is_colliding)
		box.x+=xvel;
	
	map_y+=yvel;
}

/////Set that the player is moving
void player::setMoving(bool b)
{
	is_shooting=false;
	moving=b;
}

/////Check if the player is mobing or not
bool player::getMoving()
{
	return moving;
}

////Set the direction
void player::setDirection(char c)
{
	if((c=='r' || c=='l') && direction!=c)
	{
		direction=c;
		is_colliding=false;
		if(direction=='r')
			frame=0;
		else
			frame=6;
	}
}

////// Set that the player is jumping
void player::setJump()
{	
	if(ground && !jump)
	{
		snd_sfx_play(sfx_jump,255,128);
		is_shooting=false;
	    jump=1;
		animation_limit=0;
		ground=0;
		countvel=0;
		yvel=-6;
		upvel=-90;		
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

///// Check if the player is jumping
bool player::getJump()
{
	return jump;
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

///// Set frame when shooting and standing
void player::setFrame()
{
	is_shooting=true;
	
		if(direction=='r')
		{
			frame=6;
		}
		if(direction=='l')
		{
			frame=13;
		}	
}

///// Reset the position in the map
void player::resetPosition()
{
	is_shooting=false;
	health=200;
	box.x=130;
	box.y=128;
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
