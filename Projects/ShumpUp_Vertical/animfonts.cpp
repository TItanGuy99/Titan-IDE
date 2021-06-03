/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/ #include "animfonts.h"

/////Main function for the enemy
animfonts::animfonts(char * my_text, int my_speed) {
  speed = my_speed;
  count_speed = 0;
  length_string = 0;
  current_text = new char;
  new_text = new char;
  current_text = my_text;
}

animfonts::~animfonts() {
  delete current_text;
  delete new_text;
}

char * animfonts::returnText() {
  //strncpy(new_text,current_text,length_string);
  snprintf(new_text, length_string, "%s", current_text);
  count_speed++;

  if (length_string < strlen(current_text) && count_speed == speed) {
    count_speed = 0;
    length_string++;
  }

  return new_text;
}

void animfonts::resetAnimation() {
  length_string = 0;
  count_speed = 0;
}