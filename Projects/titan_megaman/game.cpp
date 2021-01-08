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

	titan_logo = load_image("rd/images/menu/Titan.pvr", "pvr", 1, 1, 1);
	press_start = load_image("rd/images/menu/Start_Game.bmp", "bmp", 0x00, 0x00, 0x00);
	m_screen = load_image("rd/images/menu/menu.pvr", "pvr", 1, 1, 1);
	game_over = load_image("rd/images/menu/game_over.pvr", "pvr", 1, 1, 1);
	final_screen = load_image("rd/images/menu/final_screen.pvr", "pvr", 1, 1, 1);
	block = load_image("rd/images/blocks/blocks.bmp", "bmp", 0xff, 0x00, 0x00);
	blocksBG = load_image("rd/images/BG/blocks.bmp", "bmp", 0xff, 0x00, 0x00);
	bul = load_image("rd/images/bullets/BLT.bmp", "bmp", 0x00, 0x00, 0x00);
	ene = load_image("rd/images/enemy/enemy.bmp", "bmp", 0xff, 0x00, 0x00);
	ene2 = load_image("rd/images/enemy/enemy2.bmp", "bmp", 0xff, 0x00, 0x00);
	hud = load_image("rd/images/hud/HUD.bmp", "bmp", 0x00, 0x00, 0x00);
	energy = load_image("rd/images/hud/LIFE.bmp", "bmp", 0x00, 0x00, 0x00);
	energy_life = load_image("rd/images/hud/LIFE2.bmp", "bmp", 0x00, 0x00, 0x00);

	sfx_bullet = snd_sfx_load("/rd/shooting.wav");
	sfx_alien = snd_sfx_load("/rd/enemy.wav");
	sfx_hurt = snd_sfx_load("/rd/hurt.wav");

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

	energy1.x = -32;
	energy1.y = -13;
	energy1.w = -16;
	energy1.h = -16;

	energy2.x = -62;
	energy2.y = -13;
	energy2.w = -16;
	energy2.h = -16;

	energy3.x = -92;
	energy3.y = -13;
	energy3.w = -16;
	energy3.h = -16;

	energy4.x = -124;
	energy4.y = -15;
	energy4.w = -16;
	energy4.h = -16;

	direction[0] = direction[1] = 0;
	running = true;
	all_running = true;
	player1 = new player(load_image("rd/images/player/player.bmp", "bmp", 0xff, 0x00, 0x00));
	finish.x = 0;
	finish.y = 0;
	finish.w = 50;
	finish.h = 50;

	press_start1.x = -100;
	press_start1.y = -180;
	press_start1.w = -118;
	press_start1.h = -11;
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

	for (int i = 0; i < bullets.size(); i++)
		delete bullets[i];
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	for (int i = 0; i < enemies_bkp.size(); i++)
		delete enemies_bkp[i];

	SDL_Quit();
	pvr_shutdown();
}

///////Function to load the images without black
SDL_Surface *game::load_image(const char *filename, const char* extension, int r, int g, int b) //it will load an image
{
	SDL_Surface *tmp;
	

	if(extension=="pvr") {
		tmp= IMG_Load(filename);
	}
	else {
		tmp = SDL_LoadBMP(filename);	//load the BMP to a tmp variable
	}
	
	SDL_Surface *tmp2 = SDL_DisplayFormat(tmp); //change it to the format of the screen
	if (r != 1 && g != 1 && b != 1)
	{
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
		case SDL_QUIT:
			running = false;
			return;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					direction[0] = 1;
					player1->setMoving(1);
					break;

				case SDLK_RETURN:
					restart_game();
					break;

				case SDLK_KP_ENTER:
					restart_game();
					break;

				case SDLK_RIGHT:
					direction[1] = 1;
					player1->setMoving(1);
					break;

				case SDLK_SPACE:
					player1->setJump();
					break;
					
				default:
				
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				direction[0] = 0;
				player1->setMoving(0);
				break;

			case SDLK_RIGHT:
				direction[1] = 0;
				player1->setMoving(0);
				break;

			case SDLK_f:
				snd_sfx_stop(sfx_bullet);
				snd_sfx_play(sfx_bullet, 255, 128);

				if (player1->getDirection() == 'r')
				{
					if (!player1->getJump())
					{
						if (!player1->getMoving())
						{
							player1->setFrame();
							bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 8, 0));
						}
						else
						{
							bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 8, 0));
						}
					}
					else
					{
						bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 8, 8, 0));
					}
				}
				else
				{
					if (!player1->getJump())
					{
						if (!player1->getMoving())
						{
							player1->setFrame();
							bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 15, -8, 0));
						}
						else
						{
							bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 15, -8, 0));
						}
					}
					else
					{
						bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 8, -8, 0));
					}
				}

				break;
				
				default:
				
				break;
			}
			break;

		case SDL_JOYBUTTONDOWN:

			switch (event.jbutton.button)
			{
			case 0:
				player1->setJump();
				break;

			case 4:
				restart_game();
				break;
			}
			break;

		case SDL_JOYBUTTONUP:
			switch (event.jbutton.button)
			{
			case 2:

				snd_sfx_stop(sfx_bullet);
				snd_sfx_play(sfx_bullet, 255, 128);

				if (player1->getDirection() == 'r')
				{
					if (!player1->getJump())
					{
						if (!player1->getMoving())
						{
							player1->setFrame();
							bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 8, 0));
						}
						else
						{
							bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 8, 0));
						}
					}
					else
					{
						bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 8, 8, 0));
					}
				}
				else
				{
					if (!player1->getJump())
					{
						if (!player1->getMoving())
						{
							player1->setFrame();
							bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 15, -8, 0));
						}
						else
						{
							bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 15, -8, 0));
						}
					}
					else
					{
						bullets.push_back(new bullet(bul, player1->getRect()->x, player1->getRect()->y + 8, -8, 0));
					}
				}
				break;
			}
			break;

		case SDL_JOYHATMOTION:

			switch (event.jhat.value)
			{
			case 2: //right
				direction[0] = 0;
				direction[1] = 1;
				player1->setMoving(1);
				break;

			case 8: //left
				direction[0] = 1;
				direction[1] = 0;
				player1->setMoving(1);
				break;

			case 0: //neutral
				direction[0] = 0;
				player1->setMoving(0);
				direction[1] = 0;
				player1->setMoving(0);
				break;
			}
			break;

		default:

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
			in >> current;			  //read the current number
			if (current < 0 && !isBG) //if it's -1 than we put a new enemy to the position
			{
				if (current == -1)
				{
					enemies.push_back(new enemy(ene, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0)); //because every tile is TILE_SIZE width and height, we can calculate
					enemies_bkp.push_back(new enemy(ene, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0));
					//where they start by multiplying it with the i or j
					vec.push_back(0); //and we push back 0 to the vector (so nothing will be visible there)
				}
				else if (current == -2)
				{
					enemies.push_back(new enemy(ene2, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0)); //because every tile is TILE_SIZE width and height, we can calculate
					enemies_bkp.push_back(new enemy(ene2, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0));
					//where they start by multiplying it with the i or j
					vec.push_back(0); //and we push back 0 to the vector (so nothing will be visible there)
				}
			}
			else
			{
				if (current >= 0)
				{
					vec.push_back(current); //put the current into our matrix which represent the map in the game
				}
				else
				{
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
	int start = (baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;

	if (start < 0)
		start = 0;
	if (end > currentMap[0].size())
		end = currentMap[0].size();
	for (int i = 0; i < currentMap.size(); i++)
	{
		for (int j = start; j < end; j++)
		{
			if (currentMap[i][j] != 0)
			{
				SDL_Rect blockrect = {(currentMap[i][j] - 1) * baseclass::TILE_SIZE, 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE};
				SDL_Rect destrect = {j * baseclass::TILE_SIZE - baseclass::coord.x, i * baseclass::TILE_SIZE};

				if (checkY)
				{
					baseclass::coord.y = (player1->get_mapy() - currentMap.size() / 2 + 96);
					destrect.y += (player1->get_mapy() - currentMap.size() / 2 + 96) * -1;
				}

				SDL_BlitSurface(currentBlock, &blockrect, screen, &destrect);
			}
		}
	}
}

////// Main menu of the game
void game::menu()
{
	//cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
	SDL_Event event;
	bool menu_running = true;
	bool check_limit = false;
	int alpha = 255;

	SDL_FillRect(screen, NULL, 0x000000);
	SDL_SetAlpha(titan_logo, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(titan_logo, &cameraPVR, screen, NULL);
	update_screen();
	SDL_Delay(5000);

	while (alpha > 0)
	{
		alpha -= 5;
		SDL_BlitSurface(m_screen, &cameraPVR, screen, NULL);
		SDL_BlitSurface(titan_logo, &cameraPVR, screen, NULL);
		SDL_SetAlpha(titan_logo, SDL_SRCALPHA, alpha);
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

		SDL_SetAlpha(press_start, SDL_SRCALPHA, alpha);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:

				switch (event.key.keysym.sym)
				{
					case SDLK_RETURN:
						thd_sleep(10);
						menu_running = false;
						break;

					case SDLK_KP_ENTER:
						thd_sleep(10);
						menu_running = false;
						break;

					case SDLK_ESCAPE:
						running = false;
						all_running = false;
						break;
						
					default:
					
					break;
				}

				break;

			case SDL_JOYBUTTONDOWN:

				switch (event.jbutton.button)
				{
				case 4:
					thd_sleep(10);
					menu_running = false;
					break;
				}

				break;
			}
		}
		update_screen();
	}
}

////////////////////////////////////////////////////////////////////////////

void game::restart_game()
{
	enemies.clear();
	enemies.assign(enemies_bkp.begin(), enemies_bkp.end());

	for (int i = 0; i < enemies_bkp.size(); i++)
	{
		enemies_bkp[i]->setLife();
	}

	running = false;
	direction[0] = 0;
	direction[1] = 0;
	player1->setMoving(0);
	player1->setLives(3);
	player1->resetPosition();
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x = 0;
	camera.y = 0;
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_Flip(screen);
}

void game::update_screen() {
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);	
}

///// Function to start the game
void game::start()
{
	Uint32 start;
	loadmap("rd/map/map.map", false);
	loadmap("rd/map/mapBG.map", true);
	vmu();

	cdrom_cdda_pause();
	pvr_shutdown();
	pvr_init_defaults();
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_SWSURFACE);
	PVR_SET(PVR_SCALER_CFG, 0x400);

	while (all_running)
	{
		menu();
		SDL_FillRect(screen, NULL, 0x000000);
		SDL_Flip(screen);
		running = true;
		cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);

		while (running)
		{
			start = SDL_GetTicks();
			handleEvents();

			if (direction[0])
			{
				player1->setDirection('l');

				if (player1->getRect()->x > 130)
				{
					player1->setXvel(-2);
				}
				else if (baseclass::coord.x < 3)
				{
					player1->setXvel(-2);
				}
				else
				{
					player1->setMoving(1);
					player1->setXvel(0);
					camera.x -= 3;
					baseclass::coord.x -= 3;
				}
				if (camera.x < 0)
					camera.x = 320 - SCREEN_WIDTH;
			}
			else if (direction[1])
			{
				player1->setDirection('r');
				if (player1->getRect()->x < 130)
				{
					player1->setXvel(2);
				}
				else
				{
					player1->setMoving(1);
					player1->setXvel(0);
					camera.x += 3;
					baseclass::coord.x += 3;
				}

				if (camera.x >= 320 - SCREEN_WIDTH)
					camera.x = 0;
			}
			else
			{
				player1->setXvel(0);
			}

			//calculate the start and the end coordinate (see a little bit above)
			int str = (baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
			int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 32;
			if (start < 0)
				start = 0;
			if (end > map[0].size())
				end = map[0].size();
			for (int i = 0; i < map.size(); i++) //go throuh the map
				for (int j = str; j < end; j++)
				{
					if (map[i][j] == 0) //if it's nothing, we don't have to check collision
						continue;
					SDL_Rect destrect = {j * 32 - baseclass::coord.x, i * 32 - baseclass::coord.y, 32, 32}; //calculate the relative coordinate to the screen (see above)
					for (int g = 0; g < bullets.size(); g++)												//go throuht the bullets
						if (collision(bullets[g]->getRect(), &destrect))									//if the bullet collide with a tile
						{
							delete bullets[g];					//than delete it
							bullets.erase(bullets.begin() + g); //and delete from the vector as well
						}
				}

			for (int i = 0; i < bullets.size(); i++)										//go through the bullets
				if (bullets[i]->getRect()->x >= screen->w || bullets[i]->getRect()->x <= 0) //and if it's outside of the screen
				{
					delete bullets[i]; //delete them
					bullets.erase(bullets.begin() + i);
				}

			for (int i = 0; i < bullets.size(); i++) //go through both enemies and bullets
				for (int j = 0; j < enemies.size(); j++)
				{
					SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x, enemies[j]->getRect()->y - baseclass::coord.y, 40, 40}; //calculate relative coordinates see above
					if (collision(&tmprect, bullets[i]->getRect()))																			   //if one bullet collide with and enemy
					{
						if (enemies[j]->subtractLife() <= 0)
						{
							enemies.erase(enemies.begin() + j);
							snd_sfx_play(sfx_alien, 225, 128);
						}

						delete bullets[i];
						bullets.erase(bullets.begin() + i);
					}
				}

			////Collisions between the enemies and the player
			for (int j = 0; j < enemies.size(); j++) //go through the enemies
			{
				//{box.x-coord.x,box.y-coord.y,40,40};
				SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x, enemies[j]->getRect()->y - baseclass::coord.y, 40, 40}; //calculate relative coordinates see above
				SDL_Rect tmpbase = {baseclass::coord.x, baseclass::coord.y, 300, 240};

				if (collision(&tmpbase, enemies[j]->getRect())) //if the enemy is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
				{
					if (collision(&tmprect, player1->getRect())) //if we collide with an enemy
					{
						player1->setHealth(player1->getHealth() - 2); //else decrease the health of the player with 1
					}

					enemies[j]->move(map); //only move, when the enemy is on the screen. (change)
				}
			}

			//move everything
			player1->move(map);
			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->move();
			}

			start = SDL_GetTicks();

			showmap(mapBG, false, blocksBG);
			showmap(map, true, block);

			player1->show(screen);
			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->show(screen);
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->show(screen);
			}

			SDL_BlitSurface(hud, &camera, screen, NULL);
			
			char current_live[100];
			sprintf(current_live,"%d",player1->getLives());
			
			gfxPrimitivesSetFont(&SDL_gfx_font_7x13O_fnt,7,13);
			stringRGBA(screen,13,10,current_live,255,255,255,255);

			if (player1->getHealth() > 5)
				SDL_BlitSurface(energy, &energy1, screen, NULL);
			if (player1->getHealth() > 50)
				SDL_BlitSurface(energy, &energy2, screen, NULL);
			if (player1->getHealth() > 100)
				SDL_BlitSurface(energy, &energy3, screen, NULL);
			if (player1->getHealth() > 150)
				SDL_BlitSurface(energy_life, &energy4, screen, NULL);

			if (player1->getHealth() == 5 || player1->getHealth() == 50 || player1->getHealth() == 100 || player1->getHealth() == 150)
			{
				player1->setHealth(player1->getHealth() - 1);
				snd_sfx_play(sfx_hurt, 255, 128);
			}

			update_screen();

			///////////////////////////////////still in test/////////////////

			save_clock = SDL_GetTicks() - start;

			if (SDL_GetTicks() - start <= 20)
			{
				SDL_Delay(10);
			}

			//////////////////////////////////////////////////////////

			if (player1->getHealth() <= 0 || player1->get_mapy() >= 400)
			{
				player1->setLives(player1->getLives() - 1);

				enemies.clear();
				enemies.assign(enemies_bkp.begin(), enemies_bkp.end());

				for (int i = 0; i < enemies_bkp.size(); i++)
				{
					enemies_bkp[i]->setLife();
				}

				if (player1->getLives() > 0)
				{
					player1->resetPosition();
					baseclass::coord.x = 0;
					baseclass::coord.y = 0;
					camera.x = 0;
					camera.y = 0;
				}
				else
				{
					running = false;
					direction[0] = 0;
					direction[1] = 0;
					player1->setMoving(0);
					player1->setLives(3);
					player1->resetPosition();
					baseclass::coord.x = 0;
					baseclass::coord.y = 0;
					camera.x = 0;
					camera.y = 0;
					cdrom_cdda_play(3, 3, 10, CDDA_TRACKS);
					SDL_FillRect(screen, NULL, 0x000000);
					SDL_Flip(screen);
					SDL_BlitSurface(game_over, &cameraPVR, screen, NULL);
					SDL_Flip(screen);
					SDL_Delay(5000);
					SDL_FillRect(screen, NULL, 0x000000);
					SDL_Flip(screen);
					//delete this;
				}
			}

			///////////// Go to end screen
			if (baseclass::coord.x > 5080)
			{
				restart_game();
			}
		}
	}
}