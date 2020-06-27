/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "game.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass
 
game::game()    //constructor
{		
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,24,SDL_FULLSCREEN);

	// button initialization
	SDL_ShowCursor(SDL_DISABLE);		
	SDL_Delay(200);

	// button initialization
	WPAD_Init();

	// Initialise the audio subsystem
	ASND_Init();
	MP3Player_Init();
	
	titan_logo = load_image("sd:/apps/Titan_Megaman/rd/images/menu/Titan.bmp",1,1,1);
	press_start = load_image("sd:/apps/Titan_Megaman/rd/images/menu/Start_Game.bmp",0x00,0x00,0x00);
	m_screen = load_image("sd:/apps/Titan_Megaman/rd/images/menu/menu.bmp",1,1,1);
	game_over  = load_image("sd:/apps/Titan_Megaman/rd/images/menu/game_over.bmp",1,1,1);
	final_screen = load_image("sd:/apps/Titan_Megaman/rd/images/menu/final_screen.bmp",1,1,1);
	block = load_image("sd:/apps/Titan_Megaman/rd/images/blocks/blocks.bmp", 0xff,0x00,0x00);
	blocksBG = load_image("sd:/apps/Titan_Megaman/rd/images/BG/blocks.bmp", 0xff,0x00,0x00);
	bul=load_image("sd:/apps/Titan_Megaman/rd/images/bullets/BLT.bmp",0x00,0x00,0x00);
	ene=load_image("sd:/apps/Titan_Megaman/rd/images/enemy/enemy.bmp",0xff,0x00,0x00);
	ene2=load_image("sd:/apps/Titan_Megaman/rd/images/enemy/enemy2.bmp",0xff,0x00,0x00);
	hud=load_image("sd:/apps/Titan_Megaman/rd/images/hud/HUD.bmp",0x00,0x00,0x00);
	energy=load_image("sd:/apps/Titan_Megaman/rd/images/hud/LIFE.bmp",0x00,0x00,0x00);
	energy_life=load_image("sd:/apps/Titan_Megaman/rd/images/hud/LIFE2.bmp",0x00,0x00,0x00);
	numb=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N3.bmp",0x00,0x00,0x00);
	n9=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N9.bmp",0x00,0x00,0x00);
	n8=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N8.bmp",0x00,0x00,0x00);
	n7=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N7.bmp",0x00,0x00,0x00);
	n6=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N6.bmp",0x00,0x00,0x00);
	n5=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N5.bmp",0x00,0x00,0x00);
	n4=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N4.bmp",0x00,0x00,0x00);
	n3=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N3.bmp",0x00,0x00,0x00);
	n2=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N2.bmp",0x00,0x00,0x00);
	n1=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N1.bmp",0x00,0x00,0x00);
	n0=load_image("sd:/apps/Titan_Megaman/rd/images/numbers/N0.bmp",0x00,0x00,0x00);
		
	baseclass::coord.x = 0;
	baseclass::coord.y=0;
	camera.x=0;
	camera.y=0;
	///////////////
	baseclass::coord.w=SCREEN_WIDTH;
	///////////////
	camera.w=SCREEN_WIDTH;
	baseclass::coord.h=SCREEN_HEIGHT;
	camera.h=SCREEN_HEIGHT;
		
    numb1.x=-8;
	numb1.y=-6;
	numb1.w=-16;
	numb1.h=-16;
	
    energy1.x=-32;
	energy1.y=-13;
	energy1.w=-16;
	energy1.h=-16;
	
    energy2.x=-62;
	energy2.y=-13;
	energy2.w=-16;
	energy2.h=-16;
	
    energy3.x=-92;
	energy3.y=-13;
	energy3.w=-16;
	energy3.h=-16;
	
    energy4.x=-124;
	energy4.y=-15;
	energy4.w=-16;
	energy4.h=-16;
	
	
	direction[0]=direction[1]=0;
	running=true;
	player1=new player(load_image("sd:/apps/Titan_Megaman/rd/images/player/player.bmp",0xff,0x00,0x00));
	finish.x=0;
    finish.y=0;
	finish.w=50;
	finish.h=50;
	
	press_start1.x = -100; 
	press_start1.y = -180;
}

///// Destroy all the variables in the memory for the game.
game::~game()
{
	SDL_FreeSurface(titan_logo);
	SDL_FreeSurface(press_start);
	SDL_FreeSurface(m_screen);
	SDL_FreeSurface(game_over);
	SDL_FreeSurface(final_screen);
	SDL_FreeSurface(block);
	SDL_FreeSurface(blocksBG);
	SDL_FreeSurface(bul);
	SDL_FreeSurface(ene);
	SDL_FreeSurface(ene2);
	SDL_FreeSurface(hud);
	SDL_FreeSurface(energy);
	SDL_FreeSurface(energy_life);
	SDL_FreeSurface(numb);
	SDL_FreeSurface(n9);
	SDL_FreeSurface(n8);
	SDL_FreeSurface(n7);
	SDL_FreeSurface(n6);
	SDL_FreeSurface(n5);
	SDL_FreeSurface(n4);
	SDL_FreeSurface(n3);
	SDL_FreeSurface(n2);
	SDL_FreeSurface(n1);
	SDL_FreeSurface(n0);
		
	SDL_Quit();
}

///////Function to load the images without black
SDL_Surface* game::load_image(const char* filename, int r, int g, int b)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);    //change it to the format of the screen
		if(r != 1 && g != 1 && b != 1) {
			SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,r,g,b)); //set the colorkey, so the 00ffff color is transparent
		}
		
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

////Function to handle all the Joystick/Keyboard events
void game::handleEvents()
{
    WPAD_ScanPads();
    u32 buttonsDown = WPAD_ButtonsDown(0);
    u32 buttonsHeld = WPAD_ButtonsHeld(0);
    u32 buttonsUp = WPAD_ButtonsUp(0);

	if(!buttonsDown & !buttonsHeld &!buttonsUp) 
	{
		direction[0]=0;
		player1->setMoving(0);
		direction[1]=0; 
		player1->setMoving(0);	
	}

	if(buttonsDown & WPAD_BUTTON_LEFT)
	{
		direction[0]=1;
		player1->setMoving(1);
	}
	else if(buttonsDown & WPAD_BUTTON_RIGHT)
	{
		direction[1]=1;
		player1->setMoving(1);
	}
	else if(buttonsDown & WPAD_BUTTON_HOME) 
	{
		SDL_Quit();	
	}
	else if(buttonsDown & WPAD_BUTTON_A) 
	{
		player1->setJump();
	}

	if(buttonsUp & WPAD_BUTTON_LEFT)
	{
		direction[0]=0;
		player1->setMoving(0);
	}
	else if(buttonsUp & WPAD_BUTTON_RIGHT)
	{
		direction[1]=0; 
		player1->setMoving(0);
	}
	else if(buttonsUp & WPAD_BUTTON_1) 
	{
		if(player1->getDirection()=='r')   
		{
			if(!player1->getJump())
			{
				if(!player1->getMoving())     
				{
					player1->setFrame();
					bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
				}								
				else
				{
					bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
				}			
			}
			else
			{
				bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+8,8,0));				
			}
		}							
		else
		{
			if(!player1->getJump())
			{							
				if(!player1->getMoving())   
				{
					player1->setFrame();
					bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
				}	
				else
				{
					bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
				}
			}
			else
			{
				bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+8,-8,0));
			}	
		}		
	}

	/*if(neutral)
	{
		direction[0]=0;
		player1->setMoving(0);
		direction[1]=0; 
		player1->setMoving(0);		
	}*/

	/*if(!buttonsDown && buttonsHeld && buttonsUp) 
	{
		direction[0]=0;
		player1->setMoving(0);
		direction[1]=0; 
		player1->setMoving(0);		
	}*/

	/*else
	{
		direction[0]=0;
		player1->setMoving(0);
	}*/

/*	SDL_Event event;
		
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
		        running=false;
				return;
			case SDL_KEYDOWN:
			    switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
					    direction[0]=1;
						player1->setMoving(1);
					break;
					
					case SDLK_RETURN:
						restart_game();					
					break;					

					case SDLK_KP_ENTER:
						restart_game();
					break;
					
					case SDLK_RIGHT:
					    direction[1]=1;
						player1->setMoving(1);
					break;	
                   
                    case SDLK_SPACE:
                        player1->setJump();
                    break;						
				}
			break;
			
			case SDL_KEYUP:
			    switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
					    direction[0]=0;
						player1->setMoving(0);
					break;
					
					case SDLK_RIGHT:
					    direction[1]=0; 
						player1->setMoving(0);
					break;	

                    case SDLK_f:
						
                        if(player1->getDirection()=='r')   
						{
							if(!player1->getJump())
							{
								if(!player1->getMoving())     
								{
									player1->setFrame();
									bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
								}								
								else
								{
									bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
								}			
							}
							else
							{
								bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+8,8,0));
							}
						}							
                        else
						{
							if(!player1->getJump())
							{							
								if(!player1->getMoving())   
								{
									player1->setFrame();
									bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
								}	
								else
								{
									bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
								}
							}
							else
							{
								bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+8,-8,0));
							}	
						}
						
						break;
				}
			break;	

            case SDL_JOYBUTTONDOWN:
			
			    switch(event.jbutton.button)
				{                   
                    case 0:
                        player1->setJump();
                    break;	

					case 7:
						restart_game();
					break;						
				}
			break;

            case SDL_JOYBUTTONUP:
			    switch(event.jbutton.button)
				{
                    case 2:
					
                        if(player1->getDirection()=='r')   
						{
							if(!player1->getJump())
							{
								if(!player1->getMoving())     
								{
									player1->setFrame();
									bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
								}								
								else
								{
									bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+15,8,0));
								}			
							}
							else
							{
								bullets.push_back(new bullet(bul,player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+8,8,0));
							}
						}							
                        else
						{
							if(!player1->getJump())
							{							
								if(!player1->getMoving())   
								{
									player1->setFrame();
									bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
								}	
								else
								{
									bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+15,-8,0));
								}
							}
							else
							{
								bullets.push_back(new bullet(bul,player1->getRect()->x,player1->getRect()->y+8,-8,0));
							}	
						}							
						break;
				}
            break;	

			case SDL_JOYHATMOTION:

			    switch(event.jhat.value)
				{
                    case 2: //right
					    direction[0]=0;
					    direction[1]=1;
						player1->setMoving(1);
					break;
					
                    case 8:  //left
					    direction[0]=1;
						direction[1]=0;
						player1->setMoving(1);
					break;
					
					case 0: //neutral
						direction[0]=0;
						player1->setMoving(0);
						direction[1]=0; 
						player1->setMoving(0);
					break;
				}
			break;	

            default:

            break;						
		}
	}*/
}

///// Function to load the map
void game::loadmap(const char* filename, bool isBG)
{
        std::ifstream in(filename);     //open the file
        if(!in.is_open())       //if we are not succeded
        {
                std::cout << "Problem with loading the file" << std::endl;      //write out end exit
                return;
        }
        //read the width and the height from the file
        int width,height;
        in >> width;
        in >> height;
        int current;
        for(int i=0;i<height;i++)       //with two for loops go throught the file
        {
                std::vector<int> vec;   //every time we create a vector, and later we push that vector to the end of another vector
                //so it's like a 2D array (matrix)
                for(int j=0;j<width;j++)
                {
                        if(in.eof())    //if we reached the file before we end with the read in
                        {
                                std::cout << "File end reached too soon" << std::endl;  //write out and exit
                                return;
                        }
                        in >> current;  //read the current number
                        if(current<0 && !isBG) //if it's -1 than we put a new enemy to the position
                        {
							if(current==-1)
							{
                                enemies.push_back(new enemy(ene,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));//because every tile is TILE_SIZE width and height, we can calculate
                                enemies_bkp.push_back(new enemy(ene,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));
								//where they start by multiplying it with the i or j
                                vec.push_back(0);       //and we push back 0 to the vector (so nothing will be visible there)	
							}
							else if(current==-2)
							{
                                enemies.push_back(new enemy(ene2,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));//because every tile is TILE_SIZE width and height, we can calculate
                                enemies_bkp.push_back(new enemy(ene2,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));
								//where they start by multiplying it with the i or j
                                vec.push_back(0);       //and we push back 0 to the vector (so nothing will be visible there)	
							}
                        }
                        else
                        {
							if(current>=0) {
								vec.push_back(current); //put the current into our matrix which represent the map in the game
							}
							else {
								vec.push_back(0);       //if the tile number is not known than just push 0 (so nothing) in the current position
							}
                        }
                }
                if(!isBG) 
                {
                    map.push_back(vec);     //finally we push the vector to the end of the vector (dynamically allocated matrix :D)
                }
                else 
                {
                    mapBG.push_back(vec);
                }
        }
				
        in.close();     //close the file
}

////// Function to show the map on the screen
void game::showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock)
{	
	int start=(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-
	(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	
	if(start<0)
		start=0;
	if(end>currentMap[0].size())
       end=currentMap[0].size();		
	for(int i=0; i<currentMap.size(); i++)
	{
		for(int j=start; j<end;j++)
		{
			if(currentMap[i][j]!=0)
			{
				SDL_Rect blockrect={(currentMap[i][j]-1)*baseclass::TILE_SIZE,0,baseclass::TILE_SIZE,baseclass::TILE_SIZE};
				SDL_Rect destrect = {j*baseclass::TILE_SIZE-baseclass::coord.x,i*baseclass::TILE_SIZE};
								
                if(checkY) 
                {
                    baseclass::coord.y = (player1->get_mapy()-currentMap.size()/2+96);
                    destrect.y += (player1->get_mapy()-currentMap.size()/2+96)*-1;
                }

				SDL_BlitSurface(currentBlock,&blockrect,screen,&destrect);
			}
		}
	}
}

////// Main menu of the game
void game::menu()
{
	SDL_Event event;
	bool menu_running=true;
	bool logo_running=true;
	bool check_limit=false;
	int alpha=255;
	
	SDL_SetAlpha(titan_logo,SDL_SRCALPHA,alpha);
	SDL_BlitSurface(titan_logo,&camera,screen,NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(5000);
		
	while(alpha>0)
	{
		alpha-=5;
		SDL_BlitSurface(m_screen,&camera,screen,NULL);
		SDL_BlitSurface(titan_logo,&camera,screen,NULL);
		SDL_SetAlpha(titan_logo,SDL_SRCALPHA,alpha);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
		
	alpha=0;
	
	while(menu_running)
	{
		if(check_limit)
		{
			if(alpha<255)
			{
				alpha++;
			}
			else if(alpha==255)
			{
				check_limit=false;
			}
		}
		else
		{
			if(alpha>0)
			{
				alpha--;
			}
			else if(alpha==0)
			{
				check_limit=true;
			}			
		}
		
		SDL_BlitSurface(m_screen,&camera,screen,NULL);
		SDL_BlitSurface(press_start,&press_start1,screen,NULL);
		
		SDL_SetAlpha(press_start,SDL_SRCALPHA,alpha);
		
        while(menu_running)
        {
			WPAD_ScanPads();
			u32 held = WPAD_ButtonsHeld(0);

			if(held & WPAD_BUTTON_HOME) 
			{
				SDL_Quit();	
			}
			else if(held & WPAD_BUTTON_A) 
			{
				menu_running=false;
			}
		}
		SDL_Delay(100);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
}

void game::restart_game()
{
	enemies.clear();
	enemies.assign(enemies_bkp.begin(),enemies_bkp.end());

	for(int i=0;i<enemies_bkp.size();i++)
	{
		enemies_bkp[i]->setLife();
	}	
				
	running=false;
	direction[0]=0;
	direction[1]=0;
	player1->setMoving(0);
	player1->setLives(3);
	player1->resetPosition();
	baseclass::coord.x = 0;
	baseclass::coord.y=0;
	camera.x=0;
	camera.y=0;			
	SDL_FillRect(screen,NULL, 0x000000); 
	SDL_Flip(screen); 	
}

///// Function to start the game
void game::start()
{	
	int max;
	int min;
	int output;
	bool all_runing=true;
	Uint32 start;
	loadmap("sd:/apps/Titan_Megaman/rd/map/map.map", false);
	loadmap("sd:/apps/Titan_Megaman/rd/map/mapBG.map", true);	
	
	while(all_runing)
	{		
		menu();
	    SDL_FillRect(screen,NULL, 0x000000); 
		SDL_Flip(screen); 
		running=true;
		//cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);

		while(running)
		{
			//start=SDL_GetTicks();
			handleEvents();
							
			if(direction[0])
			{			
				player1->setDirection('l');
				
			   if(player1->getRect()->x>130)
			   {
				   player1->setXvel(-2);
			   }
			   else if(baseclass::coord.x<3)
			   {
				   player1->setXvel(-2);
			   }
			   else{
				   player1->setMoving(1);
				   player1->setXvel(0);
				   camera.x-=3;
				   baseclass::coord.x-=3;
			   }
			   if(camera.x<0)
				 camera.x=320-SCREEN_WIDTH;	   
			}else if(direction[1])
			{
			   player1->setDirection('r');
			   if(player1->getRect()->x <130)
			   {
					player1->setXvel(2);
			   } 
			   else
			   {
				   player1->setMoving(1);
				   player1->setXvel(0);
				   camera.x+=3;
				   baseclass::coord.x+=3;
			   }

			   if(camera.x>=320-SCREEN_WIDTH)
				 camera.x=0;  
			}else 
			{
				player1->setXvel(0);
			}
			
			//calculate the start and the end coordinate (see a little bit above)
			int str=(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
			int end=(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE))/32;
						if(start<0)
								start=0;
						if(end>map[0].size())
								end=map[0].size();
						for(int i=0;i<map.size();i++)   //go throuh the map
								for(int j=str;j<end;j++)
								{
									if(map[i][j]==0)        //if it's nothing, we don't have to check collision
										continue;
									SDL_Rect destrect={j*32-baseclass::coord.x,i*32-baseclass::coord.y,32,32}; //calculate the relative coordinate to the screen (see above)
									for(int g=0;g<bullets.size();g++)       //go throuht the bullets
										if(collision(bullets[g]->getRect(),&destrect))  //if the bullet collide with a tile
										{
											delete bullets[g];      //than delete it
											bullets.erase(bullets.begin()+g);       //and delete from the vector as well
										}
								}
	 
			for(int i=0;i<bullets.size();i++)       //go through the bullets
					if(bullets[i]->getRect()->x >= screen->w || bullets[i]->getRect()->x <= 0) //and if it's outside of the screen
					{
						delete bullets[i];      //delete them
						bullets.erase(bullets.begin()+i);
					}
	 
			for(int i=0;i<bullets.size();i++)       //go through both enemies and bullets
					for(int j=0;j<enemies.size();j++)
					{
						SDL_Rect tmprect={enemies[j]->getRect()->x-baseclass::coord.x,enemies[j]->getRect()->y-baseclass::coord.y,40,40}; //calculate relative coordinates see above
						if(collision(&tmprect,bullets[i]->getRect()))   //if one bullet collide with and enemy
						{				
							if(enemies[j]->subtractLife()<=0)
							{
								//delete enemies[j];      //delete the bullet and the enemy
								enemies.erase(enemies.begin()+j);					
							}
										
								delete bullets[i];
								bullets.erase(bullets.begin()+i);
						}
					}
			
			////Collisions between the enemies and the player
			for(int j=0;j<enemies.size();j++)       //go through the enemies
			{
					//{box.x-coord.x,box.y-coord.y,40,40};
					SDL_Rect tmprect={enemies[j]->getRect()->x-baseclass::coord.x,enemies[j]->getRect()->y-baseclass::coord.y,40,40}; //calculate relative coordinates see above
					SDL_Rect tmpbase={baseclass::coord.x,baseclass::coord.y,300,240}; 
					
					if(collision(&tmpbase,enemies[j]->getRect()))  //if the enemy is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
					{
							if(collision(&tmprect,player1->getRect()))      //if we collide with an enemy
							{
									//if(player1->getRect()->y+player1->getRect()->h>=enemies[j]->getRect()->y && player1->getRect()->y+player1->getRect()->h<=enemies[j]->getRect()->y+10)   //if we are on the 'head' of the enemy
									//{
											//delete enemies[j];      //kill the enemy
											//enemies.erase(enemies.begin()+j);
									//}else{
											player1->setHealth(player1->getHealth()-2); //else decrease the health of the player with 1	
									//}
							}
							
								enemies[j]->move(map);  //only move, when the enemy is on the screen. (change)
					}
			}

			//move everything
			player1->move(map);
			for(int i=0;i<bullets.size();i++)
			{
				bullets[i]->move();
			}

			//start=SDL_GetTicks();
	
			showmap(mapBG, false, blocksBG);
			showmap(map, true, block);

			player1->show(screen);
			for(int i=0;i<bullets.size();i++)
			{
				bullets[i]->show(screen);
			}
			for(int i=0;i<enemies.size();i++)
			{
				enemies[i]->show(screen);
			}
			
			SDL_BlitSurface(hud,&camera,screen,NULL);	
			
			if(player1->getHealth()>5)
			SDL_BlitSurface(energy,&energy1,screen,NULL);
			if(player1->getHealth()>50)
			SDL_BlitSurface(energy,&energy2,screen,NULL);
			if(player1->getHealth()>100)
			SDL_BlitSurface(energy,&energy3,screen,NULL);
			if(player1->getHealth()>150)
			SDL_BlitSurface(energy_life,&energy4,screen,NULL);
			
			if(player1->getHealth()==5 || player1->getHealth()==50 || player1->getHealth()==100 || player1->getHealth()==150)
			{
				player1->setHealth(player1->getHealth()-1);
			}
			
			SDL_BlitSurface(numb,&numb1,screen,NULL);		
			SDL_Flip(screen);
	
			//SDL_Delay(15);
		
			//////////////////////////////////////////////////////////
					
		   if(player1->getHealth()<=0 || player1->get_mapy() >=400)
			{
				player1->setLives(player1->getLives()-1);	
								
				enemies.clear();
				enemies.assign(enemies_bkp.begin(),enemies_bkp.end());

				for(int i=0;i<enemies_bkp.size();i++)
				{
					enemies_bkp[i]->setLife();
				}
				
				switch(player1->getLives())
				{
					case 9:
						numb=n9;
					break;
					
					case 8:
						numb=n8;
					break;
					
					case 7:
						numb=n7;
					break;
					
					case 6:
						numb=n6;
					break;
					
					case 5:
						numb=n5;
					break;
					
					case 4:
						numb=n4;
					break;
					
					case 3:
						numb=n3;
					break;
					
					case 2:
						numb=n2;
					break;
					
					case 1:
						numb=n1;
					break;
					
					case 0:
						numb=n0;
					break;
				}
				
				if(player1->getLives()>0)
				{
					player1->resetPosition();
					baseclass::coord.x = 0;
					baseclass::coord.y=0;
					camera.x=0;
					camera.y=0;	
				}
				else
				{
					running=false;
					direction[0]=0;
					direction[1]=0;
					player1->setMoving(0);
					player1->setLives(3);
					player1->resetPosition();
					baseclass::coord.x = 0;
					baseclass::coord.y=0;
					camera.x=0;
					camera.y=0;		
					//cdrom_cdda_play(3, 3, 10, CDDA_TRACKS);	
					numb=n3;			
					SDL_FillRect(screen,NULL, 0x000000); 
					SDL_Flip(screen); 
					SDL_BlitSurface(game_over,&camera,screen,NULL);
					SDL_Flip(screen);					
					SDL_FillRect(screen,NULL, 0x000000); 
					SDL_Flip(screen); 
					//delete this;
				}
			}
			
			///////////// Go to end screen
			if(baseclass::coord.x>5080)
			{		
				restart_game();		
			}
		}
	}
}