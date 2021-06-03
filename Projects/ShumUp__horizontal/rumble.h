#include <kos.h>

#ifndef RUMBLE_H
#define RUMBLE_H

class rumble {
  maple_device_t * purupurus[2];
  bool active;
  public:
    rumble(bool can_rumble);
  void make_rumble();
  bool hasRumblePack();
  void setActive(bool a);
  bool getActive();
  void stop_rumble();
};
#endif