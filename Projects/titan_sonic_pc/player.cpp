/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
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
	map_y=0;
	on_wall=false;
	is_colliding=false;
	looking_up=false;
	looking_down=false;
	count_shooting=0;
	
	for(int i=0;i<48;i++)
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
   if(looking_up && !jump && !moving)
   {
       if(direction=='r')
	   {
	       frame=16;
	   } 
	   else if(direction=='l')
	   {
	      frame=40; 
	   }	   
   }
   else if(looking_down && !jump && !moving)
   {
       if(direction=='r')
	   {
	       frame=15;
	   } 
	   else if(direction=='l')
	   {
	        frame=39;
	   }	   
   }
   else if(on_wall && !jump)
   {
	   if(moving)
	   {
		    count_standing=0;
		    count_running=0;
		   
			if(direction=='r' && frame < 22)
			{
				frame=22;
			}
			else if(direction=='l' && frame < 46)
			{
				frame=46;
			}	

			frame+=0.1;
			
			if(direction=='r' && frame >= 23.4)
			{
				frame=22;
			} else if(direction=='l' && frame >= 47.4)
			{
				frame=46;
			}		   
	   }
   }
   
   else if(jump)
   {
		count_standing=0;
		
		if(direction=='r' && frame < 17)
		{
			frame=17;
		}
		else if(direction=='l' && frame < 41)
		{
			frame=41;
		}
		
		frame+=0.2;
		
		if(direction=='r' && frame >= 20.4)
		{
			frame=17;
		} else if(direction=='l' && frame >= 44.4)
		{
			frame=41;
		}
	}
	else if(moving)
	{
		count_running++;
		
		if(direction=='r' && frame <5)
		{
			frame=5;
		}else if(direction=='l' && frame<29)
		{
			frame=29;
		}	
		
		frame+=0.2;
		
		if(count_running>50)
		{
			if(direction=='r' && frame >= 14.4)
			{
				frame=11;
			}else if(direction=='l' && frame>=38.4)
			{
				frame=35;
			}			
		}
		else
		{
			if(direction=='r' && frame >= 10.4)
			{
				frame=5;
			}else if(direction=='l' && frame>=34.4)
			{
				frame=29;
			}				
		}
		

	}
	else
	{
		count_standing++;
		count_running=0;
		
		if(count_standing<300)
		{
			if(direction=='r')
			{
				frame=0;
			}else if(direction=='l')
			{
				frame=24;
			}				
		}
		else
		{
			
			if(direction=='r'  && frame <1)
			{
				frame=1;
			}else if(direction=='l'  && frame <25)
			{
				frame=25;
			}				
			
			frame+=0.1;
			
			if(direction=='r' && frame >= 4.4)
			{
				frame=3;
			}else if(direction=='l' && frame>=28.4)
			{
				frame=27;
			}					
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
				  
		  //SDL_Rect destrect={j*32-baseclass::coord.x,i*32-baseclass::coord.y,32,32};
		  SDL_Rect destrect={j*32-baseclass::coord.x+18,i*32-baseclass::coord.y,16,32};
		  
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
				box.x+=2;
			  }
			  
			  if(box.x+box.w>=destrect.x-6.1 && box.y+box.h>=destrect.y+6.6 && box.x
			  +box.w<=destrect.x+5)
			  {
				  xvel=0;
				  box.x-=2;
				  is_colliding=true;
			  }
			  else if(box.x<=destrect.x+destrect.w && box.y+box.h>=destrect.y+6.6)
			  {
				  xvel=0;
				  box.x+=2;
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
	{
		box.x+=xvel;
	}
	else
	{
		on_wall=true;
	}
		
	
	map_y+=yvel;
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
	if((c=='r' || c=='l') && direction!=c)
	{
		direction=c;
		is_colliding=false;
		on_wall=false;
		count_running=0;
		count_running=0;
		if(direction=='r')
			frame=0;
		else
			frame=24;
	}
}

////// Set that the player is jumping
void player::setJump()
{	
	if(ground && !jump)
	{
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

///// Reset the position in the map
void player::resetPosition()
{
	on_wall=false;
	frame=0;
	is_shooting=false;
	health=200;
	box.x=130;
	box.y=90;
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
