/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "enemy.h"

/////Main function for the enemy
enemy::enemy(SDL_Surface * img, int x, int y, int xVel, int yVel) {
  image = img;
  count_x = 500;
  life = 5;
  box.x = x;
  box.y = y;
  enemy_size = 32;
  box.w = enemy_size;
  box.h = enemy_size;
  xvel = xVel;
  yvel = yVel;
  direction = 'l';
  ground = 0;
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
  frame += 0.1;

  if (direction == 'r' && frame >= 1.4) {
    frame = 0;
  } else if (direction == 'l' && frame >= 3.4) {
    frame = 2;
  }

  int start = (baseclass::coord.x - 320 - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
  int end = (baseclass::coord.x + baseclass::coord.w + 320 + (baseclass::TILE_SIZE -
    (baseclass::coord.x + 320 + baseclass::coord.w) % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;

  if (start < 0)
    start = 0;
  if (end > map[0].size())
    end = map[0].size();

  bool nc = 0;
  ground = 0;

  if (count_x < 100)
    count_x++;

  for (int i = 0; i < map.size(); i++)
    for (int j = start; j < end; j++) {
      if (map[i][j] == 0)
        continue;

      SDL_Rect destrect = {
        j * enemy_size - baseclass::coord.x + enemy_size - 20,
        i * enemy_size - baseclass::coord.y,
        4,
        4
      };
      SDL_Rect clone_box = {
        box.x - coord.x,
        box.y - coord.y,
        enemy_size,
        enemy_size
      };

      if (collision( & clone_box, & destrect)) {
        nc = 1;

        if (destrect.y > box.y - coord.y + box.h - 6.1) {
          ground = 1; //then we don't fall any more and we are on the ground
          yvel = 0;
          nc = 1;
        } else {
          if (box.x - coord.x + box.w >= destrect.x - 6.1 && box.y - coord.y + box.h >= destrect.y + 6.6 && box.x - coord.x +
            box.w <= destrect.x + 20) {
            count_x = 0;
            setDirection('l');
            box.x -= 2;
            xvel = -2; //else change the direction in the x axis
            printf("%d\n", 8);
          } else if (box.x - coord.x <= destrect.x + destrect.w && box.y - coord.y + box.h >= destrect.y + 6.1) {
            count_x = 0;
            setDirection('r');
            box.x += 2;
            xvel = +2; //else change the direction in the x axis
            printf("%d\n", 9);
          }
        }
      }
    }

  if (!nc)
    yvel = 2;

  if (ground) {
    box.x += xvel;
  }

  box.y += yvel;
}

//// Get the enemy image
SDL_Surface * enemy::getImage() {
  return image;
}

//// Check the enemy direction
char enemy::getDirection() {
  return direction;
}

//// Set y of the enemy
void enemy::setY(int new_y) {
  box.y = new_y;
  //printf("Joystick has %d buttons\n", box.y);
}

///// Set the direction
void enemy::setDirection(char c) {
  if ((c == 'r' || c == 'l') && direction != c) {
    direction = c;
    if (direction == 'r')
      frame = 1;
    else
      frame = 5;
  }
}

///// Subtract the life of the enemy
int enemy::subtractLife() {
  life--;
  return life;
}

void enemy::setLife() {
  life = 5;
}