/*Code and engine made by Titan Game Studios 2016/2021 coded by Luiz Nai.*/
#include "vmu.h"

/////Verify if there is a VMU connected.
int vmu::check_start() 
{
    maple_device_t *cont;
    cont_state_t *state;

    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

    if(!cont)
        return 0;


    state = (cont_state_t *)maple_dev_status(cont);

    if(!state) {
        return 0;
    }

    if(state->buttons & CONT_START) {
        printf("Pressed start\n");
        return 1;
    }

    return 0;
}

/* Only this XPM will work with this code.. it's too cheap to actually
   do any parsing =) */
#include "graphic.xpm"

/* LCD Test: this will do a grayscale seperation into several "frames" and
   flip through them quickly to give the illusion of grayscale on the LCD
   display. */

uint8 lcd_disp[8][48 * 32 / 8];
void vmu::lcd_gs_pixel(int x, int y, int amt) {
    int i;

    for(i = 0; i < amt; i++)
        lcd_disp[i][(y * 48 + x) / 8] |= 0x80 >> (x & 7);
}

///////Function to display in the VMU screen
void vmu::lcd_gs_setup() 
{
    char **xpm = graphic_xpm + 12;  
    int x, y;

    memset(lcd_disp, 0, sizeof(lcd_disp));

    for(y = 0; y < 32; y++) {
        for(x = 0; x < 48; x++) {
 
            int pixel = xpm[31 - y][47 - x];

            switch(pixel) {
                case '%':   
                    lcd_gs_pixel(x, y, 7);
                    break;
            }
        }
    }
}

///Main class for the VMU
vmu::vmu()
{
	int frame = 0;
	lcd_gs_setup();
	
	////////////////////Code for the VMU
	maple_device_t *addr = maple_enum_type(0, MAPLE_FUNC_LCD);

    if(addr) {
        int rv = vmu_draw_lcd(addr, lcd_disp + frame);

        if(rv < 0)
            printf("got error %d\n", rv);
        else {
            frame=0;
        }
    }
}

////Class to destroy the VMU in the memory
vmu::~vmu()
{

}