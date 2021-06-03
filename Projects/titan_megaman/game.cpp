/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "game.h"

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

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

  snd_stream_init();

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE);

  SDL_ShowCursor(SDL_DISABLE);
  SDL_JoystickEventState(SDL_ENABLE);

  joystick = SDL_JoystickOpen(0);
  buttonCount = SDL_JoystickNumButtons(joystick);
  my_vmu = new vmu();
  rumble_pack = new rumble(true);

  play_video(1);
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
  finish.x = 0;
  finish.y = 0;
  finish.w = 50;
  finish.h = 50;

  press_start1.x = -100;
  press_start1.y = -180;
  press_start1.w = -118;
  press_start1.h = -11;
}

///Function to call video API
void game::play_video(int number_video) {
  switch (number_video) {
  case 1:
    roq_play("/cd/videos/titan_logo.roq", // path to .roq file
      0, // 1 = loop, 0 = no loop
      roq_render_cb, // default video callback.
      roq_audio_cb, // default audio callback
      roq_quit_cb // default quit callback
    );
    break;
  }
}

///Load assets in memory
bool game::mount_romdisk(char * filename, char * mountpoint) {
  void * buffer;
  ssize_t size = fs_load(filename, & buffer);

  // Successfully read romdisk image
  if (size != -1) {
    fs_romdisk_mount(mountpoint, (const uint8 * ) buffer, 1);
    return true;
  } else
    return false;
}

void game::clr_stage1_mem() {
  delete player1;

  SDL_FreeSurface(block);
  block = NULL;
  SDL_FreeSurface(blocksBG);
  blocksBG = NULL;
  SDL_FreeSurface(ene);
  ene = NULL;
  SDL_FreeSurface(ene2);
  ene2 = NULL;
  SDL_FreeSurface(bul);
  bul = NULL;
  SDL_FreeSurface(hud);
  hud = NULL;
  SDL_FreeSurface(energy);
  energy = NULL;
  SDL_FreeSurface(energy_life);
  energy_life = NULL;
  SDL_FreeSurface(spritePlayer);
  spritePlayer = NULL;

  fs_romdisk_unmount("/stage1");

  int enemies_size = enemies.size();
  int enemies_bkp_size = enemies_bkp.size();

  for (int i = 0; i < bullets.size(); i++)
    delete bullets[i];
  for (int i = 0; i < enemies.size(); i++)
    delete enemies[i];
  for (int i = 0; i < enemies_bkp.size(); i++)
    delete enemies_bkp[i];

  bullets.clear();
  enemies.clear();
  enemies_bkp.clear();
  map.clear();
  mapBG.clear();

  snd_sfx_unload_all();
}

void game::clr_menu_mem() {
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
  SDL_FillRect(screen, NULL, 0x000000);
  char mytext[] = "Now Loading...";

  SDL_FillRect(screen, NULL, 0);

  gfxPrimitivesSetFont( & SDL_gfx_font_5x7_fnt, 5, 7);
  stringRGBA(screen, 05, 05, mytext, 255, 255, 255, 255);
  update_screen();

  switch (fileToLoad) {
  case 1:
    clr_stage1_mem();
  case 0:
    if (mount_romdisk("/cd/romdisk.img", "/menu")) {
      press_start = load_image("menu/images/menu/Start_Game.bmp", "bmp", 0x00, 0x00, 0x00);
      m_screen = load_image("menu/images/menu/menu.pvr");
      game_over = load_image("menu/images/menu/game_over.pvr");
      final_screen = load_image("menu/images/menu/final_screen.pvr");
    }
    break;

  case 2:
    clr_menu_mem();
    if (mount_romdisk("/cd/romdisk2.img", "/stage1")) {
      block = load_image("/stage1/images/blocks/blocks.bmp", "bmp", 0xff, 0x00, 0x00);
      blocksBG = load_image("/stage1/images/BG/blocks.bmp", "bmp");
      ene = load_image("/stage1/images/enemy/enemy.bmp", "bmp", 0xff, 0x00, 0x00);
      ene2 = load_image("/stage1/images/enemy/enemy2.bmp", "bmp", 0xff, 0x00, 0x00);
      bul = load_image("/stage1/images/bullets/BLT.bmp", "bmp", 0x00, 0x00, 0x00);
      hud = load_image("/stage1/images/hud/HUD.bmp", "bmp", 0x00, 0x00, 0x00);
      energy = load_image("/stage1/images/hud/LIFE.bmp", "bmp", 0x00, 0x00, 0x00);
      energy_life = load_image("/stage1/images/hud/LIFE2.bmp", "bmp", 0x00, 0x00, 0x00);
      spritePlayer = load_image("/stage1/images/player/player.bmp", "bmp", 0xff, 0x00, 0x00);
      sfx_bullet = snd_sfx_load("/stage1/shooting.wav");
      sfx_alien = snd_sfx_load("/stage1/enemy.wav");
      sfx_hurt = snd_sfx_load("/stage1/hurt.wav");
      player1 = new player(spritePlayer);

      if (map.size() <= 0) {
        loadmap("/stage1/map/map.map", false);
        loadmap("/stage1/map/mapBG.map", true);
      }
    }
    break;
  }
}

///////Function to load the images without black
SDL_Surface * game::load_image(const char * filename,
  const char * extension, int r, int g, int b) //it will load an image
{
  SDL_Surface * tmp;

  if (extension == "pvr") {
    tmp = IMG_Load(filename);
  } else {
    tmp = SDL_LoadBMP(filename); //load the BMP to a tmp variable
  }

  SDL_Surface * tmp2 = SDL_DisplayFormat(tmp); //change it to the format of the screen
  if (r != 1 && g != 1 && b != 1) {
    SDL_SetColorKey(tmp2, SDL_SRCCOLORKEY, SDL_MapRGB(screen -> format, r, g, b)); //set the colorkey, so the 00ffff color is transparent
  }

  SDL_FreeSurface(tmp); //free the tmp, we don't need it anymore
  return tmp2; //return
}

////Function to handle all the Joystick/Keyboard events
void game::handleEvents() {
  SDL_Event event;
  int limit = 25;

  while (SDL_PollEvent( & event)) {
    switch (event.type) {
    case SDL_JOYBUTTONDOWN:

      switch (event.jbutton.button) {
      case 2:
        player1 -> setJump();
        break;

      case 3:
        is_paused = !is_paused;
        break;
      }
      break;

    case SDL_JOYBUTTONUP:
      switch (event.jbutton.button) {
      case 6:

        snd_sfx_stop(sfx_bullet);
        snd_sfx_play(sfx_bullet, 255, 128);

        if (player1 -> getDirection() == 'r') {
          if (!player1 -> getJump()) {
            if (!player1 -> getMoving()) {
              player1 -> setFrame();
              bullets.push_back(new bullet(bul, player1 -> getRect() -> x + player1 -> getRect() -> w, player1 -> getRect() -> y + 15, 8, 0));
            } else {
              bullets.push_back(new bullet(bul, player1 -> getRect() -> x + player1 -> getRect() -> w, player1 -> getRect() -> y + 15, 8, 0));
            }
          } else {
            bullets.push_back(new bullet(bul, player1 -> getRect() -> x + player1 -> getRect() -> w, player1 -> getRect() -> y + 8, 8, 0));
          }
        } else {
          if (!player1 -> getJump()) {
            if (!player1 -> getMoving()) {
              player1 -> setFrame();
              bullets.push_back(new bullet(bul, player1 -> getRect() -> x, player1 -> getRect() -> y + 15, -8, 0));
            } else {
              bullets.push_back(new bullet(bul, player1 -> getRect() -> x, player1 -> getRect() -> y + 15, -8, 0));
            }
          } else {
            bullets.push_back(new bullet(bul, player1 -> getRect() -> x, player1 -> getRect() -> y + 8, -8, 0));
          }
        }
        break;
      }
      break;

    case SDL_JOYAXISMOTION:

      if (event.jaxis.axis == 0) { //left right
        axi_X = event.jaxis.value;
      }

      if (event.jaxis.axis == 1) { //up down
        axi_Y = event.jaxis.value;
      }

      if (axi_Y < -limit && axi_X < -limit) {
        direction[0] = 1;
        direction[1] = 0;
        player1 -> setMoving(1);
      } else if (axi_Y < -limit && axi_X > limit) {
        direction[0] = 0;
        direction[1] = 1;
        player1 -> setMoving(1);
      } else if (axi_Y > limit && axi_X > limit) {
        direction[0] = 0;
        direction[1] = 1;
        player1 -> setMoving(1);
      } else if (axi_Y > limit && axi_X < -limit) {
        direction[0] = 1;
        direction[1] = 0;
        player1 -> setMoving(1);
      } else if (axi_X < 0 && axi_Y > -limit && axi_Y < limit) {
        direction[0] = 1;
        direction[1] = 0;
        player1 -> setMoving(1);
      } else if (axi_X > 0 && axi_Y > -limit && axi_Y < limit) {
        direction[0] = 0;
        direction[1] = 1;
        player1 -> setMoving(1);
      } else if (axi_Y < 0 && axi_X > -limit && axi_X < limit) {
        player1 -> setDirection('u');
      } else if (axi_Y > 0 && axi_X > -limit && axi_X < limit) {
        player1 -> setDirection('d');
      } else {
        axi_X = 0;
        axi_Y = 0;
        direction[0] = 0;
        player1 -> setMoving(0);
        direction[1] = 0;
      }
      break;

    case SDL_JOYHATMOTION:

      switch (event.jhat.value) {
      case 13: //right
        direction[0] = 0;
        direction[1] = 1;
        player1 -> setMoving(1);
        break;

      case 7: //left
        direction[0] = 1;
        direction[1] = 0;
        player1 -> setMoving(1);
        break;

      default: //neutral
        direction[0] = 0;
        player1 -> setMoving(0);
        direction[1] = 0;
        player1 -> setMoving(0);
        break;
      }
      break;
    }
  }
}

///// Function to load the map
void game::loadmap(const char * filename, bool isBG) {
  std::ifstream in (filename); //open the file
  if (! in .is_open()) //if we are not succeded
  {
    std::cout << "Problem with loading the file" << std::endl; //write out end exit
    return;
  }
  //read the width and the height from the file
  int width, height; in >> width; in >> height;
  int current;
  for (int i = 0; i < height; i++) //with two for loops go throught the file
  {
    std::vector < int > vec; //every time we create a vector, and later we push that vector to the end of another vector
    //so it's like a 2D array (matrix)
    for (int j = 0; j < width; j++) {
      if ( in .eof()) //if we reached the file before we end with the read in
      {
        std::cout << "File end reached too soon" << std::endl; //write out and exit
        return;
      } in >> current; //read the current number
      if (current < 0 && !isBG) //if it's -1 than we put a new enemy to the position
      {
        if (current == -1) {
          enemies.push_back(new enemy(ene, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0)); //because every tile is TILE_SIZE width and height, we can calculate
          enemies_bkp.push_back(new enemy(ene, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0));
          //where they start by multiplying it with the i or j
          vec.push_back(0); //and we push back 0 to the vector (so nothing will be visible there)
        } else if (current == -2) {
          enemies.push_back(new enemy(ene2, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0)); //because every tile is TILE_SIZE width and height, we can calculate
          enemies_bkp.push_back(new enemy(ene2, j * TILE_SIZE, (i * TILE_SIZE) - 50, -2, 0));
          //where they start by multiplying it with the i or j
          vec.push_back(0); //and we push back 0 to the vector (so nothing will be visible there)
        }
      } else {
        if (current >= 0) {
          vec.push_back(current); //put the current into our matrix which represent the map in the game
        } else {
          vec.push_back(0); //if the tile number is not known than just push 0 (so nothing) in the current position
        }
      }
    }
    if (!isBG) {
      map.push_back(vec); //finally we push the vector to the end of the vector (dynamically allocated matrix :D)
    } else {
      mapBG.push_back(vec);
    }
  }

  in .close(); //close the file
}

////// Function to show the map on the screen
void game::showmap(std::vector < std::vector < int > > currentMap, bool checkY, SDL_Surface * currentBlock) {
  int start = MATH_Fast_Divide(baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE), baseclass::TILE_SIZE);
  int end = MATH_Fast_Divide(baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE -
    (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE), baseclass::TILE_SIZE);

  if (start < 0)
    start = 0;
  if (end > currentMap[0].size())
    end = currentMap[0].size();
  for (int i = 0; i < currentMap.size(); i++) {
    for (int j = start; j < end; j++) {
      if (currentMap[i][j] != 0) {
        SDL_Rect blockrect = {
          MATH_fmac((currentMap[i][j] - 1), baseclass::TILE_SIZE, 0),
          0,
          baseclass::TILE_SIZE,
          baseclass::TILE_SIZE
        };
        SDL_Rect destrect = {
          MATH_fmac_Dec(j, baseclass::TILE_SIZE, baseclass::coord.x),
          MATH_fmac(i, baseclass::TILE_SIZE, 0)
        };

        if (checkY) {
          baseclass::coord.y = (player1 -> get_mapy() - currentMap.size() / 2 + 96);
          destrect.y += (player1 -> get_mapy() - currentMap.size() / 2 + 96) * -1;
        }

        SDL_BlitSurface(currentBlock, & blockrect, screen, & destrect);
      }
    }
  }
}

////// Main menu of the game
void game::menu() {
  //cdrom_cdda_play(1, 1, 10, CDDA_TRACKS);
  bool menu_running = true;
  bool check_limit = false;
  int alpha = 0;

  SDL_FillRect(screen, NULL, 0x000000);
  update_screen();

  while (menu_running) {
    if (check_limit) {
      if (alpha < 255) {
        alpha++;
      } else if (alpha == 255) {
        check_limit = false;
      }
    } else {
      if (alpha > 0) {
        alpha--;
      } else if (alpha == 0) {
        check_limit = true;
      }
    }

    SDL_BlitSurface(m_screen, & cameraPVR, screen, NULL);
    SDL_BlitSurface(press_start, & press_start1, screen, NULL);

    SDL_SetAlpha(press_start, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

    SDL_Event event;

    while (SDL_PollEvent( & event)) {
      switch (event.type) {
      case SDL_JOYBUTTONDOWN:
        switch (event.jbutton.button) {
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

////////////////////////////////////////////////////////////////////////////

void game::restart_game() {
  enemies.clear();
  enemies.assign(enemies_bkp.begin(), enemies_bkp.end());

  for (int i = 0; i < enemies_bkp.size(); i++) {
    enemies_bkp[i] -> setLife();
  }

  running = false;
  direction[0] = 0;
  direction[1] = 0;
  player1 -> setMoving(0);
  player1 -> setLives(3);
  player1 -> resetPosition();
  baseclass::coord.x = 0;
  baseclass::coord.y = 0;
  camera.x = 0;
  camera.y = 0;
  SDL_FillRect(screen, NULL, 0x000000);
  SDL_Flip(screen);
}

///Draw Hud
void game::draw_hud() {
  SDL_BlitSurface(hud, & camera, screen, NULL);

  char current_live[100];
  sprintf(current_live, "%d", player1 -> getLives());

  gfxPrimitivesSetFont( & SDL_gfx_font_7x13O_fnt, 7, 13);
  stringRGBA(screen, 13, 10, current_live, 255, 255, 255, 255);
}

////////// Go to Game Over Screen
void game::f_game_over() {
  direction[0] = 0;
  direction[1] = 0;
  player1 -> setMoving(0);
  player1 -> setLives(3);
  player1 -> resetPosition();
  baseclass::coord.x = 0;
  baseclass::coord.y = 0;
  camera.x = 0;
  camera.y = 0;
  load_assets(1);
  //cdrom_cdda_play(3, 3, 10, CDDA_TRACKS);
  SDL_FillRect(screen, NULL, 0x000000);
  SDL_Flip(screen);
  SDL_BlitSurface(game_over, & cameraPVR, screen, NULL);
  SDL_Flip(screen);
  SDL_Delay(5000);
  SDL_FillRect(screen, NULL, 0x000000);
  SDL_Flip(screen);
  //delete this;
}

///////////// Go to end screen
void game::end_game() {
  //cdrom_cdda_play(4, 4, 1, CDDA_TRACKS);
  direction[0] = 0;
  direction[1] = 0;
  player1 -> setMoving(0);
  player1 -> setLives(3);
  player1 -> resetPosition();
  baseclass::coord.x = 0;
  baseclass::coord.y = 0;
  camera.x = 0;
  camera.y = 0;
  load_assets(1);
  SDL_FillRect(screen, NULL, 0x000000);
  update_screen();
  SDL_BlitSurface(final_screen, & cameraPVR, screen, NULL);
  update_screen();
  SDL_Delay(8000);
  SDL_FillRect(screen, NULL, 0x000000);
  update_screen();
  restart_game();
}

void game::update_screen() {
  SDL_UpdateRect(screen, 0, 0, 0, 0);
  SDL_Flip(screen);
}

///// Function to start the game
void game::start() {
  Uint32 start;
  int break_game = 0;
  my_vmu -> draw(1);

  while (all_running) {
    menu();
    load_assets(2);
    SDL_FillRect(screen, NULL, 0x000000);
    SDL_Flip(screen);
    running = true;
    cdrom_cdda_play(2, 2, 10, CDDA_TRACKS);

    while (running) {
      handleEvents();
      if (!is_paused) {
        start = SDL_GetTicks();

        if (direction[0]) {
          player1 -> setDirection('l');

          if (player1 -> getRect() -> x > 130) {
            player1 -> setXvel(-2);
          } else if (baseclass::coord.x < 3) {
            player1 -> setXvel(-2);
          } else {
            player1 -> setMoving(1);
            player1 -> setXvel(0);
            camera.x -= 3;
            baseclass::coord.x -= 3;
          }
          if (camera.x < 0)
            camera.x = 320 - SCREEN_WIDTH;
        } else if (direction[1]) {
          player1 -> setDirection('r');
          if (player1 -> getRect() -> x < 130) {
            player1 -> setXvel(2);
          } else {
            player1 -> setMoving(1);
            player1 -> setXvel(0);
            camera.x += 3;
            baseclass::coord.x += 3;
          }

          if (camera.x >= 320 - SCREEN_WIDTH)
            camera.x = 0;
        } else {
          player1 -> setXvel(0);
        }

        //calculate the start and the end coordinate (see a little bit above)
        int str = MATH_Fast_Divide(baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE), baseclass::TILE_SIZE);
        int end = MATH_Fast_Divide(baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE), 32);
        if (start < 0)
          start = 0;
        if (end > map[0].size())
          end = map[0].size();
        for (int i = 0; i < map.size(); i++) //go throuh the map
          for (int j = str; j < end; j++) {
            if (map[i][j] == 0) //if it's nothing, we don't have to check collision
              continue;
            SDL_Rect destrect = {
              MATH_fmac_Dec(j, 32, baseclass::coord.x),
              MATH_fmac_Dec(i, 32, baseclass::coord.y),
              32,
              32
            }; //calculate the relative coordinate to the screen (see above)
            for (int g = 0; g < bullets.size(); g++) //go throuht the bullets
              if (collision(bullets[g] -> getRect(), & destrect)) //if the bullet collide with a tile
            {
              delete bullets[g]; //than delete it
              bullets.erase(bullets.begin() + g); //and delete from the vector as well
            }
          }

        for (int i = 0; i < bullets.size(); i++) //go through the bullets
          if (bullets[i] -> getRect() -> x >= screen -> w || bullets[i] -> getRect() -> x <= 0) //and if it's outside of the screen
        {
          delete bullets[i]; //delete them
          bullets.erase(bullets.begin() + i);
        }

        for (int i = 0; i < bullets.size(); i++) //go through both enemies and bullets
          for (int j = 0; j < enemies.size(); j++) {
            SDL_Rect tmprect = {
              enemies[j] -> getRect() -> x - baseclass::coord.x,
              enemies[j] -> getRect() -> y - baseclass::coord.y,
              40,
              40
            }; //calculate relative coordinates see above
            if (collision( & tmprect, bullets[i] -> getRect())) //if one bullet collide with and enemy
            {
              if (enemies[j] -> subtractLife() <= 0) {
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
          SDL_Rect tmprect = {
            enemies[j] -> getRect() -> x - baseclass::coord.x,
            enemies[j] -> getRect() -> y - baseclass::coord.y,
            40,
            40
          }; //calculate relative coordinates see above
          SDL_Rect tmpbase = {
            baseclass::coord.x,
            baseclass::coord.y,
            300,
            240
          };

          if (collision( & tmpbase, enemies[j] -> getRect())) //if the enemy is on the screen, (change thanks for TheAngelbrothers to point out a bug :D)
          {
            if (collision( & tmprect, player1 -> getRect())) //if we collide with an enemy
            {
              player1 -> setHealth(player1 -> getHealth() - 2); //else decrease the health of the player with 1
            }

            enemies[j] -> move(map); //only move, when the enemy is on the screen. (change)
          }
        }

        //move everything
        player1 -> move(map);
        for (int i = 0; i < bullets.size(); i++) {
          bullets[i] -> move();
        }

        start = SDL_GetTicks();

        showmap(mapBG, false, blocksBG);
        showmap(map, true, block);

        player1 -> show(screen);
        for (int i = 0; i < bullets.size(); i++) {
          bullets[i] -> show(screen);
        }
        for (int i = 0; i < enemies.size(); i++) {
          enemies[i] -> show(screen);
        }

        draw_hud();

        if (player1 -> getHealth() > 5)
          SDL_BlitSurface(energy, & energy1, screen, NULL);
        if (player1 -> getHealth() > 50)
          SDL_BlitSurface(energy, & energy2, screen, NULL);
        if (player1 -> getHealth() > 100)
          SDL_BlitSurface(energy, & energy3, screen, NULL);
        if (player1 -> getHealth() > 150)
          SDL_BlitSurface(energy_life, & energy4, screen, NULL);

        if (player1 -> getHealth() == 5 || player1 -> getHealth() == 50 || player1 -> getHealth() == 100 || player1 -> getHealth() == 150) {
          player1 -> setHealth(player1 -> getHealth() - 1);
          snd_sfx_play(sfx_hurt, 255, 128);
        }

        update_screen();

        ///////////////////////////////////still in test/////////////////

        save_clock = SDL_GetTicks() - start;

        if (SDL_GetTicks() - start <= 20) {
          SDL_Delay(10);
        }

        //////////////////////////////////////////////////////////

        if (player1 -> getHealth() <= 0 || player1 -> get_mapy() >= 400) {
          player1 -> setLives(player1 -> getLives() - 1);

          enemies.clear();
          enemies.assign(enemies_bkp.begin(), enemies_bkp.end());

          for (int i = 0; i < enemies_bkp.size(); i++) {
            enemies_bkp[i] -> setLife();
          }

          if (player1 -> getLives() > 0) {
            player1 -> resetPosition();
            baseclass::coord.x = 0;
            baseclass::coord.y = 0;
            camera.x = 0;
            camera.y = 0;
          } else {
            running = false;
            break_game = 1;
          }
        }

        ///////////// Go to end screen
        if (baseclass::coord.x > 5080 && running) {
          running = false;
          break_game = 2;
        }
      } else {
        char paused[] = "PAUSE";
        gfxPrimitivesSetFont( & SDL_gfx_font_9x18B_fnt, 9, 18);
        stringRGBA(screen, 136, 120, paused, 255, 255, 255, 255);
        update_screen();
      }
    }
    switch (break_game) {
    case 1:
      f_game_over();
      break;

    case 2:
      end_game();
      break;
    }
  }
}