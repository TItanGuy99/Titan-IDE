/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "enemy.h"

/////Main function for the enemy
enemy::enemy(SDL_Surface * img, int x, int y, int xVel, int yVel) {
  image = img;
  count_x = 500;
  life = 5;
  box.x = x;
  box.y = y;
  save_x = x;
  save_y = y;
  enemy_size = 64;
  box.w = enemy_size;
  box.h = 64;
  xvel = xVel;
  dead = false;
  yvel = yVel;
  direction = 'l';
  ground = 0;
  count_bullets = 0;

  for (int i = 0; i < 8; i++) {
    clips[i].x = i * enemy_size;
    clips[i].y = 0;
    clips[i].w = enemy_size;
    clips[i].h = enemy_size;
  }
  frame = 0;
}

//// Show the enemy on the screen
void enemy::show(SDL_Surface * screen) {
  SDL_Rect tmp = {
    box.x - coord.x,
    box.y - coord.y,
    40,
    40
  };
  SDL_BlitSurface(image, & clips[(int)(frame)], screen, & tmp);
}

///// Get Y,X, width and height of the enemy
SDL_Rect * enemy::getRect() {
  return &box;
}

///// Move the enemy
void enemy::move(std::vector < std::vector < int > > & map) {
  if (life > 0) {
    if (frame < 2.4) {
      frame += 0.1;
    } else {
      frame = 0;
    }
  } else if (!dead) {
    frame += 0.2;

    if (frame < 3) {
      frame = 3;
    }

    if (frame > 8.4) {
      dead = true;
    }
  }

  if (player_x > box.x) {
    distance = player_x - box.x;
  } else {
    distance = box.x - player_x;
  }

  if (player_x > box.x && distance > 20) {
    if (life > 0)
      box.x++;
  } else if (distance > 20) {
    if (life > 0)
      box.x--;
  }

  count_bullets++;

  if (count_bullets > 100) {
    count_bullets = 0;
  }
}

//// Get the enemy image
SDL_Surface * enemy::getImage() {
  return image;
}

//// Get the count_bullets
int enemy::getCount_Bullets() {
  return count_bullets;
}

//// Check if the enemy is dead
bool enemy::getDead() {
  return dead;
}

//// Check the enemy direction
char enemy::getDirection() {
  return direction;
}

//// Set y of the enemy
void enemy::setX(int new_x) {
  box.x = new_x;
}

/// Get player y
void enemy::getPlayerX(int c) {
  player_x = c;
}

/// Get player Y
int enemy::getEnemyY() {
  return box.y;
}

///// Set the direction
void enemy::setDirection(char c) {
  /*if((c=='r' || c=='l') && direction!=c)
  {
  	direction=c;
  	if(direction=='r')
  		frame=0;
  	else
  		frame=4;
  }*/
}

///// Subtract the life of the enemy
void enemy::subtractLife() {
  life = 0;
}

///Return the life of the enemy
int enemy::getLife() {
  return life;
}

///Set life to 5
void enemy::setLife() {
  frame = 0;
  box.x = save_x;
  box.y = save_y;
  dead = false;
  life = 5;
}