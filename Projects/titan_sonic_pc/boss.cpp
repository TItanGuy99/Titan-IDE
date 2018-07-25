/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "boss.h"

/////Main function for the boss
boss::boss(SDL_Surface* img, int x, int y, int xVel, int yVel)
{
	image=img;
	count_x=500;
	life=7;
	box.x=x;
	box.y=y;
	save_x=x;
	save_y=y;
	boss_size=96;
	collision_with_player=false;
	box.w=boss_size;
	box.h=boss_size;
	xvel=xVel;
	yvel=yVel;
	direction='l';
	ground=0;
	for (int i=0;i<8;i++)
	{
		clips[i].x=i*boss_size;
		clips[i].y=0;
		clips[i].w=boss_size;
		clips[i].h=boss_size;
	}
	frame=0;
}

//// Show the boss on the screen
void boss::show(SDL_Surface* screen)
{
    SDL_Rect tmp={box.x-coord.x,box.y-coord.y,40,40};
	SDL_BlitSurface(image,&clips[(int)(frame)],screen,&tmp);
}

///// Get Y,X, width and height of the boss
SDL_Rect* boss::getRect()
{
	return &box;
}

///// Move the boss
void boss::move(std::vector<std::vector<int> >& map)
{
	
	if(collision_with_player)
	{
		if(direction=='r')
		{
			frame=2;
		}else if(direction=='l')
		{
			frame=6;
		}			
	}
	else if(life>0)
	{
		if(direction=='r' && frame > 1.4)
		{
			frame=0;
		}else if(direction=='l' && frame<4)
		{
			frame=4;
		}	
		
		frame+=0.1;	
				
		if(direction=='r' && frame >= 1.4)
		{
			frame=0;
		}else if(direction=='l' && frame>=5.4)
		{
			frame=4;
		}		
	}
	else
	{
		if(direction=='r')
		{
			frame=3;
		}else if(direction=='l')
		{
			frame=7;
		}		
	}
		
	int start=(baseclass::coord.x-320-(baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+320+(baseclass::TILE_SIZE-
	(baseclass::coord.x+320+baseclass::coord.w)%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	
	if(start<0)
		start=0;
	if(end>map[0].size())
       end=map[0].size();	

   bool nc=0;
   ground=0;
   
   if(count_x<100)
	   count_x++;
   
	for(int i=0; i<map.size(); i++)
		for(int j=start; j<end;j++)
		{
			if(map[i][j]==0)
            continue;
		  
		  SDL_Rect destrect={j*32-baseclass::coord.x,i*32-baseclass::coord.y,32,32};
		  SDL_Rect clone_box={box.x-coord.x,box.y-coord.y,boss_size,boss_size};
		  
		  if(collision(&clone_box,&destrect))
		  {
			  nc=1;
			  
			  if(destrect.y>box.y-coord.y+box.h-6.1)
			  {
					  ground=1;       //then we don't fall any more and we are on the ground
					  yvel=0;
					  nc=1;
			  }
			  else 
			  {
		          if(box.x-coord.x+box.w>=destrect.x-6.1 && box.y-coord.y+box.h>=destrect.y+6.6 && box.x-coord.x
				  +box.w<=destrect.x+20)
				  {
				      count_x=0;
					  setDirection('l');
					  box.x-=2;
					  xvel=-2;     //else change the direction in the x axis
					  printf ("%d\n",8);
				  }
				  else if(box.x-coord.x<=destrect.x+destrect.w && box.y-coord.y+box.h>=destrect.y+6.1)
				  {
					  count_x=0;
					  setDirection('r');
					  box.x+=2;
					  xvel=+2;     //else change the direction in the x axis
					  printf ("%d\n",9);
				  }	  
			  }
		  }
		}	

    if(life>0)
	{
		box.x+=xvel;	
	}	
    else
	{
		box.y-=2;
	}		
		
}

//// Get the boss image
SDL_Surface* boss::getImage()
{
	return image;
}

//// Check the boss direction
char boss::getDirection()
{
    return direction;
}

//// Set y of the boss
void boss::setY(int new_y)
{
	box.y=new_y;
}

///// Set the direction
void boss::setDirection(char c)
{	
	if((c=='r' || c=='l') && direction!=c)
	{
		direction=c;
		if(direction=='r')
			frame=0;
		else
			frame=4;
	}
}

///// Subtract the life of the boss
int boss::subtractLife()
{
    life--;
	return life;
}

void boss::setLife()
{
	frame=0;
	life=5;
	box.x=save_x;
	box.y=save_y;
}

int boss::getLife()
{
	return life;
}

void boss::setCollision(bool b)
{
	collision_with_player=b;
}

bool boss::getCollision()
{
	return collision_with_player;
}

