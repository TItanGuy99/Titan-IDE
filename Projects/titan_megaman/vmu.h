/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/ #include <kos.h>

#include <zlib/zlib.h>

#ifndef VMU_H
#define VMU_H

class vmu {
  maple_device_t * addr;
  bool letSaving;
  public:

    const unsigned char icon_data[544] = {
      0x00,
      0xF0,
      0x0F,
      0x0F,
      0x69,
      0xF6,
      0xCC,
      0xFC,
      0x88,
      0xF3,
      0xFC,
      0xFF,
      0xFC,
      0xFF,
      0x99,
      0xF9,
      0x77,
      0xF7,
      0x44,
      0xF4,
      0x21,
      0xF2,
      0xA0,
      0xFF,
      0x61,
      0xF9,
      0x93,
      0xFC,
      0xCB,
      0xFC,
      0x00,
      0xF0,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x33,
      0x33,
      0x33,
      0xCC,
      0xCC,
      0x22,
      0x22,
      0x22,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x66,
      0x66,
      0x66,
      0xCC,
      0xCC,
      0x66,
      0x66,
      0x66,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x66,
      0x00,
      0x66,
      0xCC,
      0xCC,
      0x66,
      0x00,
      0x66,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x66,
      0x66,
      0x66,
      0xCC,
      0xCC,
      0x66,
      0x66,
      0x66,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x33,
      0x33,
      0x33,
      0xCC,
      0xCC,
      0x22,
      0x22,
      0x22,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x00,
      0x00,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0x00,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x00,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0x00,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x00,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0x00,
      0xCC,
      0xCC,
      0x00,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x00,
      0x00,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0xCC,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x33,
      0x33,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x33,
      0x33,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x00,
      0x00,
      0x00,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x33,
      0x33,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x00,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x33,
      0x33,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44,
      0x44
    };

  void lcd_gs_pixel(int x, int y, int amt);
  void lcd_gs_setup(char ** xpm);
  void draw(int current_screen);
  bool hasMemoryCard();
  bool getcanSave();
  void setcanSave(bool s);
  int DC_SaveToVMU(char * score);
  int DC_LoadFromVMU();
  vmu();
};
#endif