/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "animloop.h"

/////Main function for the enemy
animloop::animloop(SDL_Surface * img, int x, int y, int item_size, double total_frames, bool running, int frame_speed) {
  speed = frame_speed;
  count_frames = 0;
  image = img;
  t_frames = total_frames;
  box.x = x;
  box.y = y;
  box.w = item_size;
  box.h = item_size;
  is_running = running;

  for (int i = 0; i < t_frames; i++) {
    clips[i].x = i * item_size;
    clips[i].y = 0;
    clips[i].w = item_size;
    clips[i].h = item_size;
  }

  frame = 0;
}

///// Move the item
void animloop::move() {
  count_frames++;
  if (is_running && count_frames == speed) {
    frame += 0.1;
    if (frame > t_frames) {
      frame = 0.0;
    }
  } else if (count_frames > speed) {
    count_frames = 0;
  }
}

//// Show the item on the screen
void animloop::show(SDL_Surface * screen) {
  SDL_Rect tmp = {
    box.x,
    box.y,
    40,
    40
  };
  SDL_BlitSurface(image, & clips[(int)(frame)], screen, & tmp);
}

void animloop::setRunning(bool running) {
  is_running = running;
}