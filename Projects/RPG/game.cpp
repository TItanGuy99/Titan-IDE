/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "game.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_gfx_5x7_fnt.h"
#include "SDL_gfx_7x13_fnt.h"
#include "SDL_gfx_7x13B_fnt.h"
#include "SDL_gfx_7x13O_fnt.h"
#include "SDL_gfx_9x18_fnt.h"
#include "SDL_gfx_9x18B_fnt.h"
#include "SDL_gfx_fnt.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass
int save_clock;

game::game() //constructor
{
    SDL_DC_ShowAskHz(SDL_FALSE);
    SDL_DC_Default60Hz(SDL_FALSE);
    SDL_DC_VerticalWait(SDL_FALSE);
    SDL_DC_SetVideoDriver(SDL_DC_DMA_VIDEO);

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

	snd_stream_init();

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_FULLSCREEN|SDL_DOUBLEBUF|SDL_HWSURFACE);
	PVR_SET(PVR_SCALER_CFG, 0x400);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_JoystickEventState(SDL_ENABLE);

	joystick = SDL_JoystickOpen(0);
	buttonCount = SDL_JoystickNumButtons(joystick);

	load_assets(0);

	is_paused = false;
	axi_X = 0;
	axi_Y = 0;
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x = 0;
	camera.y = 0;
	cameraPVR.x = -33;
	cameraPVR.y = 0;
	cameraPVR.w = SCREEN_WIDTH;
	cameraPVR.h = SCREEN_HEIGHT;

	///////////////
	baseclass::coord.w = SCREEN_WIDTH;
	///////////////
	camera.w = SCREEN_WIDTH;
	baseclass::coord.h = SCREEN_HEIGHT;
	camera.h = SCREEN_HEIGHT;

	direction[0] = direction[1] = 0;
	running = true;
	all_running = true;
	finish.x = 0;
	finish.y = 0;
	finish.w = 50;
	finish.h = 50;

	press_start1.x = -100;
	press_start1.y = -215;
	press_start1.w = -118;
	press_start1.h = -11;
}

///Load assets in memory
bool game::mount_romdisk(char *filename, char *mountpoint)
{
    void *buffer;
    ssize_t size = fs_load(filename, &buffer);

    // Successfully read romdisk image
    if(size != -1)
    {
        fs_romdisk_mount(mountpoint, (const uint8*)buffer, 1);
        return true;
    }
    else
        return false;
}

void game::clr_stage1_mem() {
	delete player1;
	
	SDL_FreeSurface(block);
	block = NULL;
	SDL_FreeSurface(blocksBG);
	blocksBG = NULL;
	SDL_FreeSurface(hud);
	hud = NULL;
	SDL_FreeSurface(spritePlayer);
	spritePlayer = NULL;	
	fs_romdisk_unmount("/stage1");

	for (int i = 0; i < obstacles.size(); i++)
		delete obstacles[i];
	for (int i = 0; i < obstacles_bkp.size(); i++)
		delete obstacles_bkp[i];

	obstacles.clear();
	obstacles_bkp.clear();
	map.clear();
	mapBG.clear();

	snd_sfx_unload_all();
}

void game::clr_menu_mem() {
	SDL_FreeSurface(titan_logo);
	titan_logo = NULL;
	SDL_FreeSurface(press_start);
	press_start = NULL;
	SDL_FreeSurface(m_screen);
	m_screen = NULL;
	SDL_FreeSurface(game_over);
	game_over = NULL;
	SDL_FreeSurface(final_screen);
	final_screen = NULL;
	fs_romdisk_unmount("/menu");
}

void game::load_assets(int fileToLoad) {
	SDL_FillRect(screen,NULL, 0x000000);
	char mytext[] = "Now Loading...";
	
	SDL_FillRect(screen,NULL,0);

	gfxPrimitivesSetFont(&SDL_gfx_font_5x7_fnt,5,7);
	stringRGBA(screen,05,05,mytext,255,255,255,255);
	update_screen();
		
	switch (fileToLoad)
	{
		case 0:
			if(mount_romdisk("/cd/romdisk.img", "/menu")) {
				titan_logo = load_image("menu/images/menu/Titan.pvr", "pvr", 1, 1, 1);
				press_start = load_image("menu/images/menu/Start_Game.bmp", "bmp", 0x00, 0x00, 0x00);
				m_screen = load_image("menu/images/menu/menu.pvr", "pvr", 1, 1, 1);
				game_over = load_image("menu/images/menu/game_over.pvr", "pvr", 1, 1, 1);
				final_screen = load_image("menu/images/menu/final_screen.pvr", "pvr", 1, 1, 1);
			}
		break;

		case 1:
			clr_stage1_mem();
			if(mount_romdisk("/cd/romdisk.img", "/menu")) {
				titan_logo = load_image("menu/images/menu/Titan.pvr", "pvr", 1, 1, 1);
				press_start = load_image("menu/images/menu/Start_Game.bmp", "bmp", 0x00, 0x00, 0x00);
				m_screen = load_image("menu/images/menu/menu.pvr", "pvr", 1, 1, 1);
				game_over = load_image("menu/images/menu/game_over.pvr", "pvr", 1, 1, 1);
				final_screen = load_image("menu/images/menu/final_screen.pvr", "pvr", 1, 1, 1);
			}
		break;

		case 2:
			clr_menu_mem();
			if(mount_romdisk("/cd/romdisk2.img", "/stage1")) {
				block = load_image("/stage1/images/blocks/blocks.bmp", "bmp", 0xff, 0x00, 0xff);
				blocksBG = load_image("/stage1/images/BG/blocks.bmp", "bmp", 1, 1, 1);
				hud = load_image("/stage1/images/hud/HUD.bmp", "bmp", 0xff, 0x00, 0xff);
				spritePlayer = load_image("/stage1/images/player/player.bmp", "bmp", 0xff, 0x00, 0xff);
				player1 = new player(spritePlayer);
				player1->setDirection('z');

				if(map.size()<=0) {
					loadmap("/stage1/map/map.map", false);
					loadmap("/stage1/map/mapBG.map", true);
				}
			}
		break;
	}
}

///// Destroy all the variables in the memory for the game.
game::~game()
{
	for (int i = 0; i < obstacles.size(); i++)
		delete obstacles[i];
	for (int i = 0; i < obstacles_bkp.size(); i++)
		delete obstacles_bkp[i];

	SDL_Quit();
	pvr_shutdown();
}

//// Function to control the bg (not using on this code)
void game::control_bg(char d)
{

	//baseclass::coord.y+=1;

	switch (d)
	{
	case 'u':
		if (player1->getDirection() == 'u' && !player1->return_colliding())
		{
			baseclass::coord.y += 1;
		}
		else
		{
			player1->setDirection('z');
			baseclass::coord.y -= 1;
		}
		break;

	case 'd':
		if (player1->getDirection() == 'd' && !player1->return_colliding())
		{
			baseclass::coord.y -= 1;
		}
		else
		{
			player1->setDirection('z');
			baseclass::coord.y += 1;
		}
		break;

	case 'l':
		if (player1->getDirection() == 'l' && !player1->return_colliding())
		{
			baseclass::coord.x -= 1;
		}
		else
		{
			player1->setDirection('z');
			baseclass::coord.x += 2;
		}
		break;

	case 'r':
		if (player1->getDirection() == 'r' && !player1->return_colliding())
		{
			baseclass::coord.x += 1;
		}
		else
		{
			player1->setDirection('z');
			baseclass::coord.x -= 2;
		}
		break;
	}
}

///////Function to load the images
SDL_Surface *game::load_image(const char *filename, const char* extension, int r, int g, int b) //it will load an image
{
	SDL_Surface *tmp;
	
	if(extension=="pvr") {
		tmp= IMG_Load(filename);   //load a PVR image
	}
	else {
		tmp = SDL_LoadBMP(filename);	//load the BMP to a tmp variable
	}
	
	SDL_Surface *tmp2 = SDL_DisplayFormat(tmp); //change it to the format of the screen
	if (r != 1 && g != 1 && b != 1) {
		SDL_SetColorKey(tmp2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, r, g, b)); //set the colorkey, so the 00ffff color is transparent
	}

	SDL_FreeSurface(tmp); //free the tmp, we don't need it anymore
	return tmp2;		  //return
}

////Function to handle all the Joystick/Keyboard events
void game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_JOYBUTTONDOWN:
				switch (event.jbutton.button)
				{
					case 3:
						is_paused = !is_paused;
					break;
						
					default:
					
					break;
				}
			break;
			
			case SDL_JOYAXISMOTION:
				 
				if(event.jaxis.value!=0) 
				{	
					if( event.jaxis.axis==0 ){ //left right
						axi_X=event.jaxis.value;
					}
					else{ //up down
						axi_Y=event.jaxis.value;
					}
					
					int limit = 50;

					if(axi_Y < -limit && axi_X < -limit) {
						player1->setDirection('l');
					}
					else if(axi_Y < -limit && axi_X > limit){
						player1->setDirection('r');
					}
					else if(axi_Y > limit && axi_X > limit) { 
						player1->setDirection('r');
					}
					else if(axi_Y > limit && axi_X < -limit){
						player1->setDirection('l');
					}
					
					if(axi_X < 0 && axi_Y >-limit && axi_Y <limit){
						player1->setDirection('l');
					}
					else if(axi_X > 0 && axi_Y >-limit && axi_Y <limit) {
						player1->setDirection('r');
					}
					
					
					if(axi_Y < 0 && axi_X > -limit && axi_X < limit){
						player1->setDirection('u');
					}
					else if(axi_Y > 0 && axi_X > -limit && axi_X < limit){
						player1->setDirection('d');
					}
				}
				else {
					axi_X = 0;
					axi_Y = 0;	
					player1->setDirection('z');
				}
								
			break;

			case SDL_JOYHATMOTION:

				switch (event.jhat.value)
				{
					case 14: //up
						player1->setDirection('u');
					break;

					case 11: //down
						player1->setDirection('d');
					break;

					case 13: //right
						player1->setDirection('r');
					break;

					case 7: //left
						player1->setDirection('l');
					break;

					default: //neutral
						player1->setDirection('z');
					break;
				}
			break;
		}
	}
}

///// Function to load the map
void game::loadmap(const char *filename, bool isBG)
{
	std::ifstream in(filename); //open the file
	if (!in.is_open())			//if we are not succeded
	{
		std::cout << "Problem with loading the file" << std::endl; //write out end exit
		return;
	}
	//read the width and the height from the file
	int width, height;
	in >> width;
	in >> height;
	int current;
	for (int i = 0; i < height; i++) //with two for loops go throught the file
	{
		std::vector<int> vec; //every time we create a vector, and later we push that vector to the end of another vector
		//so it's like a 2D array (matrix)
		for (int j = 0; j < width; j++)
		{
			if (in.eof()) //if we reached the file before we end with the read in
			{
				std::cout << "File end reached too soon" << std::endl; //write out and exit
				return;
			}
			in >> current; //read the current number
			if (!isBG)	   //if it's -1 than we put a new enemy to the position
			{
				if (current >= 0 && current <= 13) //if the current is greater or equal then 0 (so nothing) and less or equal than the max number of tiles
				//change the 7 to a bigger number, if you want to add more tile to the tiles.bmp image, don't forget 50x50 tiles
				{
					vec.push_back(current); //put the current into our matrix which represent the map in the game
					if (current > 2)
					{
						obstacles.push_back(new obstacle(MATH_fmac(j, TILE_SIZE, 0), MATH_fmac((MATH_fmac(i, TILE_SIZE, 0)),-1,190))); //because every tile is TILE_SIZE width and height, we can calculate
						obstacles_bkp.push_back(new obstacle(MATH_fmac(j, TILE_SIZE, 0), MATH_fmac((MATH_fmac(i, TILE_SIZE, 0)), -1, 190)));
					}
				}
				else
				{
					vec.push_back(0); //if the tile number is not known than just push 0 (so nothing) in the current position
				}
			}
			else
			{
				if (current >= 0)
				{
					printf("está aqui carregando algo");
					vec.push_back(current); //put the current into our matrix which represent the map in the game
				}
				else
				{
					printf("está aqui acumulando lixo");
					vec.push_back(0); //if the tile number is not known than just push 0 (so nothing) in the current position
				}
			}
		}
		if (!isBG)
		{
			map.push_back(vec); //finally we push the vector to the end of the vector (dynamically allocated matrix :D)
		}
		else
		{
			mapBG.push_back(vec);
		}
	}

	in.close(); //close the file
}

////// Function to show the map on the screen
void game::showmap(std::vector<std::vector<int> > currentMap, bool checkY, SDL_Surface *currentBlock)
{
	
	int start=MATH_Fast_Divide(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE),baseclass::TILE_SIZE);
	int end=MATH_Fast_Divide(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-
	(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE), baseclass::TILE_SIZE);
	
	if (start < 0)
		start = 0;
	if (end > currentMap[0].size())
		end = currentMap[0].size();

	int i = 0;
	int j = start;

	if (!checkY)
	{
		for (i = 0; i < currentMap.size(); i++)
		{
			for (j = 0; j < currentMap[0].size(); j++)
			{
				if (currentMap[i][j] != 0)
				{
					SDL_Rect blockrect = {MATH_fmac(currentMap[i][j] - 1, baseclass::TILE_SIZE, 0), 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE};
					SDL_Rect destrect = {MATH_fmac(j, baseclass::TILE_SIZE, 0), MATH_fmac(i, baseclass::TILE_SIZE, 0)};
					SDL_BlitSurface(currentBlock, &blockrect, screen, &destrect);
				}
			}
		}
	}
	else
	{
		for (i = 0; i < currentMap.size(); i++)
		{
			for (j = start; j < end; j++)
			{
				if (currentMap[i][j] != 0)
				{
					SDL_Rect blockrect = {MATH_fmac(currentMap[i][j] - 1, baseclass::TILE_SIZE, 0), 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE};
					SDL_Rect destrect = {MATH_fmac_Dec(j, baseclass::TILE_SIZE, baseclass::coord.x), MATH_fmac(i , baseclass::TILE_SIZE, 0)};
					destrect.y += baseclass::coord.y;
					destrect.x -= 1;
					SDL_BlitSurface(currentBlock, &blockrect, screen, &destrect);
				}
			}
		}
	}
}

////// Main menu of the game
void game::menu()
{
	//cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
	bool menu_running = true;
	bool check_limit = false;
	int alpha = 255;

	SDL_FillRect(screen, NULL, 0x000000);
	SDL_SetAlpha(titan_logo, SDL_SRCALPHA|SDL_RLEACCEL, alpha);
	SDL_BlitSurface(titan_logo, &cameraPVR, screen, NULL);
	update_screen();
	SDL_Delay(5000);

	while (alpha > 0)
	{
		alpha -= 5;
		SDL_BlitSurface(m_screen, &cameraPVR, screen, NULL);
		SDL_BlitSurface(titan_logo, &cameraPVR, screen, NULL);
		SDL_SetAlpha(titan_logo, SDL_SRCALPHA|SDL_RLEACCEL, alpha);
		update_screen();
	}

	alpha = 0;

	while (menu_running)
	{
		if (check_limit)
		{
			if (alpha < 255)
			{
				alpha++;
			}
			else if (alpha == 255)
			{
				check_limit = false;
			}
		}
		else
		{
			if (alpha > 0)
			{
				alpha--;
			}
			else if (alpha == 0)
			{
				check_limit = true;
			}
		}

		SDL_BlitSurface(m_screen, &cameraPVR, screen, NULL);
		SDL_BlitSurface(press_start, &press_start1, screen, NULL);

		SDL_SetAlpha(press_start, SDL_SRCALPHA|SDL_RLEACCEL, alpha);


		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_JOYBUTTONDOWN:
					switch (event.jbutton.button)
					{
						case 3:
							menu_running = false;
						break;
							
						default:
						
						break;
					}
				break;
			}
		}

		update_screen();
	}
}

///////////// Go to end screen

void game::end_game()
{	
	running = false;
	direction[0] = 0;
	direction[1] = 0;
	player1->setMoving(0);
	player1->resetPosition();
	player1->setDirection('z');
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x = 0;
	camera.y = 0;
	load_assets(1);
	SDL_FillRect(screen, NULL, 0x000000);
	update_screen();
	SDL_BlitSurface(final_screen, &cameraPVR, screen, NULL);
	update_screen();
	SDL_Delay(8000);
	SDL_FillRect(screen, NULL, 0x000000);
	update_screen();
}

///Draw Hud
void game::draw_hud() {
	SDL_BlitSurface(hud, &camera, screen, NULL);
				
	char current_live[100];
	sprintf(current_live,"%d",player1->getLives());
				
	gfxPrimitivesSetFont(&SDL_gfx_font_7x13O_fnt,7,13);
	stringRGBA(screen,22,7,current_live,255,255,255,255);
}

////////// Go to Game Over Screen
void game::f_game_over() 
{
	running = false;
	direction[0] = 0;
	direction[1] = 0;
	player1->setMoving(0);
	player1->resetPosition();
	player1->setDirection('z');
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x = 0;
	camera.y = 0;
	load_assets(1);
	SDL_FillRect(screen, NULL, 0x000000);
	update_screen();
	SDL_BlitSurface(game_over, &cameraPVR, screen, NULL);
	update_screen();
	SDL_Delay(11000);
	SDL_FillRect(screen, NULL, 0x000000);
	update_screen();
}

void game::update_screen() {
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);	
}

///// Function to start the game
void game::start()
{
	Uint32 start;
	vmu();
	player1->setDirection('z');

	while (all_running)
	{
		menu();
		load_assets(2);
		SDL_FillRect(screen, NULL, 0x000000);
		update_screen();
		running = true;
		//cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);

		while (running)
		{
			start = SDL_GetTicks();
			handleEvents();
			
			if(!is_paused) {

				//calculate the start and the end coordinate (see a little bit above)
				int str=MATH_Fast_Divide(baseclass::coord.x-(baseclass::coord.x%baseclass::TILE_SIZE), baseclass::TILE_SIZE);
				int end=MATH_Fast_Divide(baseclass::coord.x+baseclass::coord.w+(baseclass::TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE), 32);
				if (start < 0)
					start = 0;
				if (end > map[0].size())
					end = map[0].size();
				for (int i = 0; i < map.size(); i++) //go throuh the map
					for (int j = str; j < end; j++)
					{
						if (map[i][j] == 0) //if it's nothing, we don't have to check collision
							continue;
					}

				////Collisions between the obstacles and the player
				for (int j = 0; j < obstacles.size(); j++) //go through the obstacles
				{
					SDL_Rect tmprect = {obstacles[j]->getRect()->x - baseclass::coord.x, obstacles[j]->getRect()->y - baseclass::coord.y + 16, 22, 24};
					SDL_Rect tmpbase = {baseclass::coord.x, baseclass::coord.y, 300, 240};

					if (collision(&tmpbase, obstacles[j]->getRect())) //if the obstacle is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
					{
						if (collision(&tmprect, player1->getRect())) //if we collide with an enemy
						{
							player1->set_colliding(true);
							break;
							break;
						}
						else
						{
							player1->set_colliding(false);
						}
					}
				}

				//move everything

				player1->move(map);

				control_bg(player1->getDirection());

				showmap(mapBG, false, blocksBG);
				showmap(map, true, block);

				player1->show(screen);
				draw_hud();
				update_screen();

				///////////////////////////////////Em teste/////////////////

				/*save_clock = SDL_GetTicks() - start;

				if (SDL_GetTicks() - start <= 20)
				{
					SDL_Delay(3);
				}
				else
				{
					SDL_Delay(2);
				}*/

				//////////////////////////////////////////////////////////

				if (player1->getHealth() <= 0 || player1->get_mapy() >= 400)
				{
					player1->setLives(player1->getLives() - 1);
					obstacles.clear();
					obstacles.assign(obstacles_bkp.begin(), obstacles_bkp.end());

					if (player1->getLives() > 0)
					{
						player1->resetPosition();
						baseclass::coord.x = 0;
						baseclass::coord.y = 0;
						camera.x = 0;
						camera.y = 0;
						direction[0] = 0;
						direction[1] = 0;
						player1->setMoving(0);
					}
					else
					{
						f_game_over();
					}
				}
			}
			else {
				char paused[] = "PAUSE";
				gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
				stringRGBA(screen,136,120,paused,255,255,255,255);					
				update_screen();
			}
		}
	}
}