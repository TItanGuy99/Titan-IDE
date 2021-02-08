/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <stdio.h>
#include <string.h>
#ifndef ANIMFONTS_H
#define ANIMFONTS_H
class animfonts
{
    int speed;
    int count_speed;
    int length_string;
    char* current_text;
    char* new_text;
    public:
	animfonts(char my_text[], int my_speed);
    ~animfonts();
    char* returnText();
    void resetAnimation();
};
#endif