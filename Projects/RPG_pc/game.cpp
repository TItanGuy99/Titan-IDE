/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "game.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass

game::game() //constructor
{
	SDL_Init(SDL_INIT_JOYSTICK);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_JoystickEventState(SDL_ENABLE);

	joystick = SDL_JoystickOpen(0);
	buttonCount = SDL_JoystickNumButtons(joystick);

	SDL_Delay(200);

	titan_logo = load_image("rd/images/menu/Titan.bmp", 1, 1, 1);
	press_start = load_image("rd/images/menu/Start_Game.bmp", 0x00, 0x00, 0x00);
	m_screen = load_image("rd/images/menu/menu.bmp", 1, 1, 1);
	game_over = load_image("rd/images/menu/game_over.bmp", 1, 1, 1);
	final_screen = load_image("rd/images/menu/final_screen.bmp", 1, 1, 1);
	block = load_image("rd/images/blocks/blocks.bmp", 0xff, 0x00, 0xff);
	blocksBG = load_image("rd/images/BG/blocks.bmp", 1, 1, 1);
	hud = load_image("rd/images/hud/HUD.bmp", 0xff, 0x00, 0xff);
	numb = load_image("rd/images/numbers/N3.bmp", 0x00, 0x00, 0x00);
	n9 = load_image("rd/images/numbers/N9.bmp", 0x00, 0x00, 0x00);
	n8 = load_image("rd/images/numbers/N8.bmp", 0x00, 0x00, 0x00);
	n7 = load_image("rd/images/numbers/N7.bmp", 0x00, 0x00, 0x00);
	n6 = load_image("rd/images/numbers/N6.bmp", 0x00, 0x00, 0x00);
	n5 = load_image("rd/images/numbers/N5.bmp", 0x00, 0x00, 0x00);
	n4 = load_image("rd/images/numbers/N4.bmp", 0x00, 0x00, 0x00);
	n3 = load_image("rd/images/numbers/N3.bmp", 0x00, 0x00, 0x00);
	n2 = load_image("rd/images/numbers/N2.bmp", 0x00, 0x00, 0x00);
	n1 = load_image("rd/images/numbers/N1.bmp", 0x00, 0x00, 0x00);
	n0 = load_image("rd/images/numbers/N0.bmp", 0x00, 0x00, 0x00);

	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x = 0;
	camera.y = 0;

	///////////////
	baseclass::coord.w = SCREEN_WIDTH;
	///////////////
	camera.w = SCREEN_WIDTH;
	baseclass::coord.h = SCREEN_HEIGHT;
	camera.h = SCREEN_HEIGHT;

	numb1.x = -25;
	numb1.y = -2;
	numb1.w = -16;
	numb1.h = -16;

	direction[0] = direction[1] = 0;
	running = true;
	player1 = new player(load_image("rd/images/player/player.bmp", 0xff, 0x00, 0xff));
	finish.x = 0;
	finish.y = 0;
	finish.w = 50;
	finish.h = 50;

	press_start1.x = -100;
	press_start1.y = -215;
	press_start1.w = -118;
	press_start1.h = -11;

	// start SDL with audio support
	if (SDL_Init(SDL_INIT_AUDIO) == -1)
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if (Mix_OpenAudio(44000, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
}

/// Play Music
void game::play_music(Mix_Music *myAudio, int repeat)
{
	Mix_PlayMusic(myAudio, repeat);
}

/// Play Music sfx
void game::play_sfx(Mix_Chunk *mysfx, int channel, int volume, int repeat)
{
	Mix_Volume(channel, MIX_MAX_VOLUME / volume);
	Mix_PlayChannel(channel, mysfx, repeat);
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
	SDL_FreeSurface(hud);
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

	for (int i = 0; i < obstacles.size(); i++)
		delete obstacles[i];
	for (int i = 0; i < obstacles_bkp.size(); i++)
		delete obstacles_bkp[i];

	SDL_Quit();
}

///////Function to load the images without black
SDL_Surface *game::load_image(const char *filename, int r, int g, int b) //it will load an image
{
	SDL_Surface *tmp = SDL_LoadBMP(filename);	//load the BMP to a tmp variable
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
				player1->setDirection('l');
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
				player1->setDirection('r');
				break;

			case SDLK_ESCAPE:
				SDL_Quit();
				break;

			case SDLK_SPACE:

				break;

			case SDLK_UP:
				player1->setDirection('u');
				break;

			case SDLK_DOWN:
				player1->setDirection('d');
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				player1->setDirection('z');
				break;

			case SDLK_RIGHT:
				player1->setDirection('z');
				break;

			case SDLK_UP:
				player1->setDirection('z');
				break;

			case SDLK_DOWN:
				player1->setDirection('z');
				break;
			}
			break;

		case SDL_JOYBUTTONDOWN:
			switch (event.jbutton.button)
			{
			case 0:

				break;

			case 4:
				player1->setLives(3);
				restart_game();
				break;
			}
			break;

		case SDL_JOYBUTTONUP:
			switch (event.jbutton.button)
			{
			case 2:

				break;
			}
			break;

		case SDL_JOYHATMOTION:

			switch (event.jhat.value)
			{

			case 1: //up
				player1->setDirection('u');
				break;

			case 4: //down
				player1->setDirection('d');
				break;

			case 2: //right
				player1->setDirection('r');
				break;

			case 8: //left
				player1->setDirection('l');
				break;

			case 0: //neutral
				player1->setDirection('z');
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
			in >> current; //read the current number
			if (!isBG)	   //if it's -1 than we put a new enemy to the position
			{
				if (current >= 0 && current <= 13) //if the current is greater or equal then 0 (so nothing) and less or equal than the max number of tiles
				//change the 7 to a bigger number, if you want to add more tile to the tiles.bmp image, don't forget 50x50 tiles
				{
					vec.push_back(current); //put the current into our matrix which represent the map in the game
					if (current > 2)
					{
						obstacles.push_back(new obstacle(j * TILE_SIZE, (i * TILE_SIZE) * -1 + 190)); //because every tile is TILE_SIZE width and height, we can calculate
						obstacles_bkp.push_back(new obstacle(j * TILE_SIZE, (i * TILE_SIZE) * -1 + 190));
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
	int start = (baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;

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
					SDL_Rect blockrect = {(currentMap[i][j] - 1) * baseclass::TILE_SIZE, 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE};
					SDL_Rect destrect = {j * baseclass::TILE_SIZE, i * baseclass::TILE_SIZE};
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
					SDL_Rect blockrect = {(currentMap[i][j] - 1) * baseclass::TILE_SIZE, 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE};
					SDL_Rect destrect = {j * baseclass::TILE_SIZE - baseclass::coord.x, i * baseclass::TILE_SIZE};
					destrect.y += baseclass::coord.y;
					destrect.x -= 1;
					SDL_BlitSurface(currentBlock, &blockrect, screen, &destrect);
				}
			}
		}
	}
}

//// Function to control the bg
void game::control_bg(char d)
{
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

////// Main menu of the game
void game::menu()
{
	//cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
	SDL_Event event;
	bool menu_running = true;
	bool logo_running = true;
	bool check_limit = false;
	int alpha = 255;

	SDL_SetAlpha(titan_logo, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(titan_logo, &camera, screen, NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(5000);

	while (alpha > 0)
	{
		alpha -= 5;
		SDL_BlitSurface(m_screen, &camera, screen, NULL);
		SDL_BlitSurface(titan_logo, &camera, screen, NULL);
		SDL_SetAlpha(titan_logo, SDL_SRCALPHA, alpha);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
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

		SDL_BlitSurface(m_screen, &camera, screen, NULL);
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
					menu_running = false;
					break;

				case SDLK_KP_ENTER:
					menu_running = false;
					break;

				case SDLK_ESCAPE:
					SDL_Quit();
					break;
				}

				break;

			case SDL_JOYBUTTONDOWN:

				switch (event.jbutton.button)
				{
				case 4:
					menu_running = false;
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
	obstacles.clear();
	obstacles.assign(obstacles_bkp.begin(), obstacles_bkp.end());
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
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

///////////// Go to end screen

void game::end_game()
{
	running = false;
	direction[0] = 0;
	direction[1] = 0;
	player1->setMoving(0);
	player1->setLives(3);
	player1->resetPosition();
	baseclass::coord.x = 0;
	camera.x = 0;
	camera.y = 0;
	numb = n3;
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_BlitSurface(final_screen, &camera, screen, NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(8000);
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	restart_game();
}

///// Function to start the game
void game::start()
{
	int max;
	int min;
	int output;
	bool all_runing = true;
	Uint32 start;
	loadmap("rd/map/map.map", false);
	loadmap("rd/map/mapBG.map", true);
	player1->setDirection('z');

	menu();
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	running = true;

	while (running)
	{
		start = SDL_GetTicks();
		handleEvents();

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

		start = SDL_GetTicks();
		control_bg(player1->getDirection());

		showmap(mapBG, false, blocksBG);
		showmap(map, true, block);

		player1->show(screen);

		SDL_BlitSurface(hud, &camera, screen, NULL);
		SDL_BlitSurface(numb, &numb1, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);

		///////////////////////////////////Em teste/////////////////

		save_clock = SDL_GetTicks() - start;

		if (SDL_GetTicks() - start <= 20)
		{
			SDL_Delay(10);
		}
		else
		{
			SDL_Delay(5);
		}

		//////////////////////////////////////////////////////////

		if (player1->getHealth() <= 0 || player1->get_mapy() >= 400)
		{
			player1->setLives(player1->getLives() - 1);

			obstacles.clear();
			obstacles.assign(obstacles_bkp.begin(), obstacles_bkp.end());

			switch (player1->getLives())
			{
			case 9:
				numb = n9;
				break;

			case 8:
				numb = n8;
				break;

			case 7:
				numb = n7;
				break;

			case 6:
				numb = n6;
				break;

			case 5:
				numb = n5;
				break;

			case 4:
				numb = n4;
				break;

			case 3:
				numb = n3;
				break;

			case 2:
				numb = n2;
				break;

			case 1:
				numb = n1;
				break;

			case 0:
				numb = n0;
				break;
			}

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
				running = false;
				direction[0] = 0;
				direction[1] = 0;
				player1->setMoving(0);
				player1->setLives(3);
				player1->setHealth(200);
				player1->resetPosition();
				baseclass::coord.x = 0;
				baseclass::coord.y = 0;
				camera.x = 0;
				camera.y = 0;
				numb = n3;
				SDL_FillRect(screen, NULL, 0x000000);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
				SDL_BlitSurface(game_over, &camera, screen, NULL);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
				SDL_Delay(11000);
				SDL_FillRect(screen, NULL, 0x000000);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
			}
		}
	}
}