/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include <kos.h>
#ifndef VMU_H
#define VMU_H

class vmu{
	public:
	    int check_start();
		void lcd_gs_pixel(int x, int y, int amt);
		void lcd_gs_setup();
		
	     vmu();
		~vmu();
};
#endif