/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "rumble.h"

rumble::rumble(bool can_rumble) {
  active = can_rumble;
  if (can_rumble) {
    if (hasRumblePack()) {
      purupurus[0] = maple_enum_type(0, MAPLE_FUNC_PURUPURU);
    } else {
      active = false;
    }
  }
}

bool rumble::hasRumblePack() {
  if (maple_enum_type_ex(0, MAPLE_FUNC_PURUPURU, 0x00010000)) {
    return true;
  } else {
    return false;
  }
}

void rumble::setActive(bool a) {
  if (hasRumblePack()) {
    active = a;
  } else {
    active = false;
  }
}

bool rumble::getActive() {
  if (hasRumblePack()) {
    return active;
  } else {
    return false;
  }
}

void rumble::make_rumble() {
  if (active) {
    purupuru_rumble_raw(purupurus[0], 0x05281011);
  }
}

void rumble::stop_rumble() {
  if (active) {
    purupuru_rumble_raw(purupurus[0], 0x000000FF);
  }
}