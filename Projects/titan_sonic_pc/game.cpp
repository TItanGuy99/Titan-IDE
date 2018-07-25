/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "game.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass
int sfx_enemies; 
int sfx_hurt; 
int save_clock;
int sfx_ring;
 
game::game()    //constructor
{	
	//init kos
    //vid_init(DM_320x240, PM_RGB565);
    //pvr_init_defaults();
	
	SDL_Init(SDL_INIT_JOYSTICK);
	
	//snd_stream_init();
			
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,16,SDL_FULLSCREEN);
	//PVR_SET(PVR_SCALER_CFG, 0x400);
	
	SDL_ShowCursor(SDL_DISABLE);
	SDL_JoystickEventState(SDL_ENABLE);
	
	joystick = SDL_JoystickOpen(0);
	buttonCount = SDL_JoystickNumButtons(joystick);
		
	SDL_Delay(200);
	
	titan_logo = load_image2("rd/images/menu/Titan.bmp");
	press_start = load_image("rd/images/menu/Start_Game.bmp");
	m_screen = load_image2("rd/images/menu/menu.bmp");
	game_over  = load_image2("rd/images/menu/game_over.bmp");
	final_screen = load_image2("rd/images/menu/final_screen.bmp");
	block= load_image3("rd/images/blocks/blocks.bmp");
	bg1=load_image2("rd/images/BG/BG1.bmp");
	bg2=load_image2("rd/images/BG/BG1.bmp");
	bg3=load_image2("rd/images/BG/BG2.bmp");
	bg4=load_image2("rd/images/BG/BG2.bmp");
	/*bg5=load_image2("rd/images/BG/BG5.bmp");
	bg6=load_image2("rd/images/BG/BG6.bmp");
	bg7=load_image2("rd/images/BG/BG7.bmp");*/
	background=bg2;
	ite=load_image3("rd/images/itens/rings.bmp");
	ene=load_image4("rd/images/enemy/enemy.bmp");
	ene2=load_image4("rd/images/enemy/enemy2.bmp");
	bos=load_image3("rd/images/boss/boss.bmp");
	hud=load_image("rd/images/hud/HUD.bmp");
	numb=load_image("rd/images/numbers/N3.bmp");
	//sfx_enemies = snd_sfx_load("/rd/enemies.wav"); 
	//sfx_hurt = snd_sfx_load("/rd/death.wav"); 
	//sfx_ring = snd_sfx_load("/rd/ring.wav"); 
	n9=load_image("rd/images/numbers/N9.bmp");
	n8=load_image("rd/images/numbers/N8.bmp");
	n7=load_image("rd/images/numbers/N7.bmp");
	n6=load_image("rd/images/numbers/N6.bmp");
	n5=load_image("rd/images/numbers/N5.bmp");
	n4=load_image("rd/images/numbers/N4.bmp");
	n3=load_image("rd/images/numbers/N3.bmp");
	n2=load_image("rd/images/numbers/N2.bmp");
	n1=load_image("rd/images/numbers/N1.bmp");
	n0=load_image("rd/images/numbers/N0.bmp");
		
	baseclass::coord.x = 0;
	baseclass::coord.y=0;
	camera.x=0;
	camera.y=0;
	count_animation=0;
	count_background=0;
	///////////////
	baseclass::coord.w=SCREEN_WIDTH;
	///////////////
	camera.w=SCREEN_WIDTH;
	baseclass::coord.h=SCREEN_HEIGHT;
	camera.h=SCREEN_HEIGHT;
	
	rect_bg.w=SCREEN_WIDTH;
	rect_bg.h=SCREEN_HEIGHT;
	rect_bg2.w=SCREEN_WIDTH;
	rect_bg2.h=SCREEN_HEIGHT;
	rect_bg3.w=SCREEN_WIDTH;
	rect_bg3.h=SCREEN_HEIGHT;
		
	rect_bg.x=-320;
	rect_bg.y=0;
	rect_bg2.x=0;
	rect_bg2.y=0;
	rect_bg3.x=320;
	rect_bg3.y=0;
	

    numb1.x=-25;
	numb1.y=-2;
	numb1.w=-16;
	numb1.h=-16;
	
	direction[0]=direction[1]=0;
	running=true;
	player1=new player(load_image3("rd/images/player/player.bmp"));
	finish.x=0;
    finish.y=0;
	finish.w=50;
	finish.h=50;
	
	press_start1.x = -100; 
	press_start1.y = -215;
	press_start1.w = SCREEN_WIDTH;
	press_start1.h = SCREEN_HEIGHT;
	music_boss=false;
	boss_defeated=false;
	count_end=0;
	count_moving=0;
}

///// Destroy all the variables in the memory for the game.
game::~game()
{
	SDL_FreeSurface(titan_logo);
	SDL_FreeSurface(press_start);
	SDL_FreeSurface(m_screen);
	SDL_FreeSurface(block);
	SDL_FreeSurface(background);
	SDL_FreeSurface(ene);
	SDL_FreeSurface(ene2);
	SDL_FreeSurface(hud);
	SDL_FreeSurface(numb);
	
	for(int i =0;i<enemies.size();i++)
		delete enemies[i];
	for(int i =0;i<enemies_bkp.size();i++)
		delete enemies_bkp[i];
	for(int i =0;i<items.size();i++)
		delete items[i];
	for(int i =0;i<items_bkp.size();i++)
		delete items_bkp[i];
	
	
	SDL_Quit();
	//pvr_shutdown();
}

//// Function to control the bg (not using on this code)
void game::control_bg(char d)
{
	if(count_moving>20)
	{
		if(d=='r')
		{
			rect_bg.x+=1;
			rect_bg2.x+=1;
			rect_bg3.x+=1;
		}
		else
		{
			rect_bg.x-=1;
			rect_bg2.x-=1;
			rect_bg3.x-=1;
		}
		
		count_moving=0;
	}

	if(rect_bg.x<-320)
	{
		rect_bg.x=320;
	}
	
	if(rect_bg2.x<-320)
	{
		rect_bg2.x=320;
	}
	
	if(rect_bg3.x<-320)
	{
		rect_bg3.x=320;
	}
	
	if(rect_bg.x>320)
	{
		rect_bg.x=-320;
	}
	
	if(rect_bg2.x>320)
	{
		rect_bg2.x=-320;
	}
	
	if(rect_bg3.x>320)
	{
		rect_bg3.x=-320;
	}
}

//// Control animation
void game::control_animation()
{
	count_background++;
	
	switch(count_background)
	{
		case 1:
			background = bg1;
		break;
		
		case 2:
			background = bg2;
		break;
		
		case 3:
			background = bg3;
		break;
		
		case 4:
			background = bg4;
			count_background=0;
		break;
		
		/*case 5:
			background = bg5;
		break;
		
		case 6:
			background = bg6;
		break;
		
		case 7:
			background = bg6;
			count_background=0;
		break;*/
	}
}

///////Function to load the images without black
SDL_Surface* game::load_image(const char* filename)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0x00,0x00)); //set the colorkey, so the 00ffff color is transparent
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

///////Function to load the images with black
SDL_Surface* game::load_image2(const char* filename)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

///////Function to load the images without magenta
SDL_Surface* game::load_image3(const char* filename)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0xff,0x00,0xff)); //set the colorkey, so the 00ffff color is transparent
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

///////Function to load the images without green
SDL_Surface* game::load_image4(const char* filename)     //it will load an image
{
        SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0xff,0x00)); //set the colorkey, so the 00ffff color is transparent
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}


////Function to handle all the Joystick/Keyboard events
void game::handleEvents()
{
	SDL_Event event;
		
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
					    player1->setLives(3);
						restart_game();					
					break;					

					case SDLK_KP_ENTER:
					    player1->setLives(3);
						restart_game();	
					break;
					
					case SDLK_RIGHT:
					    direction[1]=1;
						player1->setMoving(1);
					break;	
					
                    case SDLK_ESCAPE:
						SDL_Quit();
					break;
                   
                    case SDLK_SPACE:
                        player1->setJump();
                    break;	
					
                    case SDLK_UP:
                        player1->setLookingUp(1);
                    break;
					
                    case SDLK_DOWN:
                        player1->setDown(1);
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
					
                    case SDLK_UP:
                        player1->setLookingUp(0);
                    break;
					
                    case SDLK_DOWN:
                        player1->setDown(0);
                    break;

                    case SDLK_f:

					break;
					
				}
			break;	

            case SDL_JOYBUTTONDOWN:
			    switch(event.jbutton.button)
				{				
                    case 0:
                        player1->setJump();
                    break;	

					case 4:
					    player1->setLives(3);
						restart_game();	
					break;						
				}
			break;


            case SDL_JOYBUTTONUP:
			    switch(event.jbutton.button)
				{
                    case 2:
						
					break;
					
				}
            break;	

			case SDL_JOYHATMOTION:

			    switch(event.jhat.value)
				{
					
					case 1: //up
						player1->setLookingUp(1);
					break;
					
					
					case 4: //down
						player1->setDown(1);
					break;
					
					
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
						player1->setLookingUp(0);
						player1->setDown(0);
					break;
				}
			break;	

            default:

            break;			
			
		}
	}
}

///// Function to load the map
void game::loadmap(const char* filename)
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
                        if(current<0) //if it's -1 than we put a new enemy to the position
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
							else if(current==-5)
							{
                                the_boss.push_back(new boss(bos,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));//because every tile is TILE_SIZE width and height, we can calculate
                                the_boss_bkp.push_back(new boss(bos,j*TILE_SIZE,(i*TILE_SIZE)-50,-2,0));
								//where they start by multiplying it with the i or j
                                vec.push_back(0);       //and we push back 0 to the vector (so nothing will be visible there)	
							}
							else if(current==-9)
						    {
                                items.push_back(new item(ite,j*TILE_SIZE+7,(i*TILE_SIZE),-2,0));//because every tile is TILE_SIZE width and height, we can calculate
                                items_bkp.push_back(new item(ite,j*TILE_SIZE+7,(i*TILE_SIZE),-2,0));
								//where they start by multiplying it with the i or j
                                vec.push_back(0);       //and we push back 0 to the vector (so nothing will be visible there)
							
							}
                        }else{
                                if(current>=0 && current<=13)    //if the current is greater or equal then 0 (so nothing) and less or equal than the max number of tiles
                                //change the 7 to a bigger number, if you want to add more tile to the tiles.bmp image, don't forget 50x50 tiles
                                {
                                    if(current==3)  //if the current is 3
                                    {
                                        finish.x=j*50;  //set the finish coordinate
                                        finish.y=i*50;
                                    }
                                    vec.push_back(current); //put the current into our matrix which represent the map in the game
                                }
								else
								{
                                    vec.push_back(0);       //if the tile number is not known than just push 0 (so nothing) in the current position
                                }
                        }
                }
                map.push_back(vec);     //finally we push the vector to the end of the vector (dynamically allocated matrix :D)
        }
				
        in.close();     //close the file
}

////// Function to show the map on the screen
void game::showmap()
{	
	int start=(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-
	(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	
	if(start<0)
		start=0;
	if(end>map[0].size())
       end=map[0].size();		
	for(int i=0; i<map.size(); i++)
	{
		for(int j=start; j<end;j++)
		{
			if(map[i][j]!=0)
			{
				SDL_Rect blockrect={(map[i][j]-1)*baseclass::TILE_SIZE,0,baseclass::TILE_SIZE,baseclass::TILE_SIZE};
				SDL_Rect destrect = {j*baseclass::TILE_SIZE-baseclass::coord.x,i*baseclass::TILE_SIZE};
								
				baseclass::coord.y = (player1->get_mapy()-map.size()/2+96);
				destrect.y += (player1->get_mapy()-map.size()/2+96)*-1;				
				SDL_BlitSurface(block,&blockrect,screen,&destrect);
			}
		}
	}
}

////// Main menu of the game
void game::menu()
{
	//cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
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
		
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
				case SDL_KEYDOWN:

					switch(event.key.keysym.sym)
					{
						case SDLK_RETURN:
							menu_running=false;						
						break;
						
						case SDLK_KP_ENTER:
							menu_running=false;
						break;
						
						case SDLK_ESCAPE:
							SDL_Quit();
						break;
					}
					
				break;
				
				case SDL_JOYBUTTONDOWN:
				
					switch(event.jbutton.button)
					{                   
						case 4:
							menu_running=false;
						break;						
					}
					
				break;
			}
		}
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
}

void game::restart_game()
{	
	enemies.clear();
	enemies.assign(enemies_bkp.begin(),enemies_bkp.end());
				
	the_boss.clear();
	the_boss.assign(the_boss_bkp.begin(),the_boss_bkp.end());
						
	items.clear();
	items.assign(items_bkp.begin(),items_bkp.end());

	for(int i=0;i<enemies_bkp.size();i++)
	{
		enemies_bkp[i]->setLife();
	}
	
	for(int i=0;i<the_boss_bkp.size();i++)
	{
		the_boss_bkp[i]->setLife();
	}
		
	boss_defeated=false;
	music_boss=false;
	count_end=0;
	count_moving=0;
	running=false;
	rect_bg.x=-320;
	rect_bg.y=0;
	rect_bg2.x=0;
	rect_bg2.y=0;
	rect_bg3.x=320;
	rect_bg3.y=0;
	direction[0]=0;
	direction[1]=0;
	player1->setMoving(0);
	player1->resetPosition();
	player1->setDirection('r');
	baseclass::coord.x = 0;
	baseclass::coord.y=0;
	camera.x=0;
	camera.y=0;			
	SDL_FillRect(screen,NULL, 0x000000); 
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

///////////// Go to end screen

void game::end_game()
{
	//cdrom_cdda_play(4, 4, 1, CDDA_TRACKS);
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
	rect_bg.x=-320;
	rect_bg.y=0;
	rect_bg2.x=0;
	rect_bg2.y=0;
	rect_bg3.x=320;
	rect_bg3.y=0;	
	numb=n3;			
	SDL_FillRect(screen,NULL, 0x000000); 
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_BlitSurface(final_screen,&camera,screen,NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);		
	SDL_Delay(8000);
	SDL_FillRect(screen,NULL, 0x000000); 
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	restart_game();
}

///// Function to start the game
void game::start()
{	
	int max;
	int min;
	int output;
	bool all_runing=true;
	//static pvr_poly_hdr_t hdr[2];
	//pvr_poly_cxt_t cxt;
	Uint32 start;
	loadmap("rd/map/map.map");	
	//vmu();
	
	while(all_runing)
	{	
		menu();
	    SDL_FillRect(screen,NULL, 0x000000); 
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		running=true;
		//cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);

		while(running)
		{
			start=SDL_GetTicks();
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
				   camera.x-=2;
				   baseclass::coord.x-=2;
				   control_bg('l');
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
				   camera.x+=2;
				   baseclass::coord.x+=2;
				   control_bg('r');
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
								}
	 	 			
			////Collisions between the enemies and the player
			for(int j=0;j<enemies.size();j++)       //go through the enemies
			{
					SDL_Rect tmprect={enemies[j]->getRect()->x-baseclass::coord.x,enemies[j]->getRect()->y-baseclass::coord.y,32,32}; //calculate relative coordinates see above
					SDL_Rect tmpbase={baseclass::coord.x,baseclass::coord.y,300,240}; 
					SDL_Rect tmp_player={player1->getRect()->x,player1->getRect()->y,16,16};
					
					if(collision(&tmpbase,enemies[j]->getRect()))  //if the enemy is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
					{
						if(collision(&tmprect,&tmp_player))      //if we collide with an enemy
						{														
							if(baseclass::coord.y+player1->getRect()->h+player1->getRect()->h/2 < enemies[j]->getRect()->y)   //if we are on the 'head' of the enemy																	
							{
								if(enemies[j]->getLife()>0)
								{
									//snd_sfx_play(sfx_enemies,225,128);
								}
										
								enemies[j]->subtractLife();
							}
							else if(enemies[j]->getLife()>0)
							{
								player1->setHealth(player1->getHealth()-200); //else decrease the health of the player with 1	
							}
						}	
							
						enemies[j]->move(map);  //only move, when the enemy is on the screen. (change)
					}
					
					if(enemies[j]->getDead())
					{
						enemies.erase(enemies.begin()+j);
					}
			}
			
			
			
			
			
			
			
			
			
			
			////Collisions between the boss and the player
			for(int j=0;j<the_boss.size();j++)       //go through the bosses
			{
					SDL_Rect tmprect={the_boss[j]->getRect()->x-baseclass::coord.x,the_boss[j]->getRect()->y-baseclass::coord.y,40,40}; //calculate relative coordinates see above
					SDL_Rect tmpbase={baseclass::coord.x,baseclass::coord.y,300,240}; 
					SDL_Rect tmp_player={player1->getRect()->x,player1->getRect()->y,16,16};
					
					if(collision(&tmpbase,the_boss[j]->getRect()))  //if the boss is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
					{
						    if(!music_boss)
							{
								//cdrom_cdda_play(3, 3, 10, CDDA_TRACKS);
								music_boss=true;
							}
						
						
							if(collision(&tmprect,&tmp_player))      //if we collide with an boss
							{
								if(!the_boss[j]->getCollision())
								{
									the_boss[j]->setCollision(true); 
									the_boss[j]->subtractLife();
									//snd_sfx_play(sfx_enemies,225,128);
								}
							}
							else
							{
								the_boss[j]->setCollision(false);
							}
							
						the_boss[j]->move(map);  //only move, when the boss is on the screen. (change)
					}
					
					if(the_boss[j]->getLife()<=0)
					{
						
						count_end++;
						
						if(!boss_defeated)
						{
							//cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);
							boss_defeated=true;
						}
								
						if(count_end==300)
						{
							the_boss.erase(the_boss.begin()+j);
							end_game();									
						}				
					}
			}			
			
			
			
			
			
			
			////Collisions between the items and the player
			for(int j=0;j<items.size();j++)       //go through the enemies
			{
					SDL_Rect tmprect={items[j]->getRect()->x-baseclass::coord.x,items[j]->getRect()->y-baseclass::coord.y,40,40}; //calculate relative coordinates see above
					SDL_Rect tmpbase={baseclass::coord.x,baseclass::coord.y,300,240}; 
					
					if(collision(&tmpbase,items[j]->getRect()))  //if the enemy is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
					{
							if(collision(&tmprect,player1->getRect()))      //if we collide with an enemy
							{
								//snd_sfx_play(sfx_ring,255,128);
								items.erase(items.begin()+j);
							}
					}
			}
									 
			player1->move(map);
			
			count_moving++;
			count_animation++;
			
			if(count_animation>5)
			{
				count_animation=0;
				control_animation();
			}
			
			start=SDL_GetTicks();
			SDL_BlitSurface(background,&rect_bg,screen,NULL);	
			SDL_BlitSurface(background,&rect_bg2,screen,NULL);	
			SDL_BlitSurface(background,&rect_bg3,screen,NULL);	
			
									
			showmap();

			player1->show(screen);
			

			for(int i=0;i<enemies.size();i++)
			{
				enemies[i]->show(screen);
			}
			for(int i=0;i<the_boss.size();i++)
			{
				the_boss[i]->show(screen);
			}			
			for(int i=0;i<items.size();i++)
			{
				items[i]->show(screen);
				items[i]->move();
			}
			

			SDL_BlitSurface(hud,&camera,screen,NULL);	
					
			if(player1->getHealth()==5 || player1->getHealth()==50 || player1->getHealth()==100 || player1->getHealth()==150)
			{
				player1->setHealth(player1->getHealth()-1);
				//snd_sfx_play(sfx_hurt,255,128);
			}
			
			
			SDL_BlitSurface(numb,&numb1,screen,NULL);		
			SDL_UpdateRect(screen, 0, 0, 0, 0);
		
		
			///////////////////////////////////Em teste/////////////////
			
			///////////////////////////////////Em teste/////////////////
			
			save_clock=SDL_GetTicks()-start;
			
			if(SDL_GetTicks()-start<=20)
			{
				SDL_Delay(10);
			}
			else
			{
				SDL_Delay(5);
			}
			
			//////////////////////////////////////////////////////////
					
					
		   if(player1->getHealth()<=0 || player1->get_mapy() >=400)
			{
				player1->setLives(player1->getLives()-1);	
								
				enemies.clear();
				enemies.assign(enemies_bkp.begin(),enemies_bkp.end());
				
				the_boss.clear();
				the_boss.assign(the_boss_bkp.begin(),the_boss_bkp.end());
						
				items.clear();
				items.assign(items_bkp.begin(),items_bkp.end());
				
				for(int i=0;i<enemies_bkp.size();i++)
				{
					enemies_bkp[i]->setLife();
				}
				
				for(int i=0;i<the_boss_bkp.size();i++)
				{
					the_boss_bkp[i]->setLife();
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
					direction[0]=0;
					direction[1]=0;
					player1->setMoving(0);
				}
				else
				{
					//cdrom_cdda_play(5, 5, 1, CDDA_TRACKS);
					boss_defeated=false;
					music_boss=false;
					count_end=0;
					running=false;
					rect_bg.x=-320;
					rect_bg.y=0;
					rect_bg2.x=0;
					rect_bg2.y=0;
					rect_bg3.x=320;
					rect_bg3.y=0;
					direction[0]=0;
					direction[1]=0;
					player1->setMoving(0);
					player1->setLives(3);
					player1->resetPosition();
					baseclass::coord.x = 0;
					baseclass::coord.y=0;
					camera.x=0;
					camera.y=0;		
					numb=n3;			
					SDL_FillRect(screen,NULL, 0x000000); 
					SDL_UpdateRect(screen, 0, 0, 0, 0);
					SDL_BlitSurface(game_over,&camera,screen,NULL);
					SDL_UpdateRect(screen, 0, 0, 0, 0);					
					SDL_Delay(11000);
					SDL_FillRect(screen,NULL, 0x000000); 
					SDL_UpdateRect(screen, 0, 0, 0, 0);
				}
			}
		}
	}
}