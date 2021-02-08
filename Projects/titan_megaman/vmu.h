/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include <kos.h>
#include <zlib/zlib.h>
#ifndef VMU_H
#define VMU_H

class vmu{
	maple_device_t *addr;
	bool letSaving;
	public:

	const unsigned char icon_data[544] ={
		0x00,0xf0,0x0d,0xf0,0x0f,0xf0,0x00,0x0f,
		0x44,0xf4,0x62,0xfb,0x96,0xff,0xca,0xff,
		0xff,0xff,0x00,0xf0,0x00,0xf0,0x00,0xf0,
		0x00,0xf0,0x00,0xf0,0x00,0xf0,0x00,0xf0,
		0x33,0x33,0x33,0x33,0x33,0x55,0x55,0x55,
		0x55,0x55,0x53,0x33,0x33,0x33,0x33,0x33,
		0x33,0x33,0x33,0x05,0x55,0x55,0x55,0x55,
		0x56,0x56,0x55,0x53,0x33,0x33,0x33,0x33,
		0x33,0x33,0x30,0x55,0x55,0x55,0x55,0x55,
		0x55,0x55,0x55,0x55,0x53,0x33,0x33,0x33,
		0x33,0x33,0x34,0x55,0x55,0x55,0x55,0x55,
		0x55,0x55,0x66,0x55,0x53,0x33,0x33,0x33,
		0x33,0x33,0x45,0x55,0x55,0x44,0x45,0x55,
		0x45,0x45,0x56,0x55,0x55,0x33,0x33,0x33,
		0x33,0x33,0x04,0x55,0x54,0x44,0x45,0x45,
		0x44,0x55,0x55,0x55,0x55,0x33,0x33,0x33,
		0x33,0x33,0x45,0x54,0x45,0x66,0x55,0x54,
		0x44,0x44,0x55,0x54,0x45,0x33,0x33,0x33,
		0x33,0x33,0x34,0x45,0x56,0x67,0x76,0x66,
		0x55,0x55,0x56,0x65,0x54,0x33,0x33,0x33,
		0x33,0x33,0x34,0x56,0x67,0x77,0x77,0x77,
		0x56,0x56,0x56,0x75,0x54,0x33,0x33,0x33,
		0x33,0x33,0x34,0x57,0x76,0x76,0x77,0x77,
		0x76,0x66,0x77,0x76,0x64,0x33,0x33,0x33,
		0x33,0x33,0x34,0x56,0x66,0x78,0x87,0x77,
		0x75,0x57,0x78,0x66,0x64,0x33,0x33,0x33,
		0x33,0x33,0x44,0x57,0x74,0x45,0x57,0x77,
		0x76,0x65,0x44,0x76,0x60,0x43,0x33,0x33,
		0x33,0x33,0x60,0x64,0x44,0x10,0x00,0x55,
		0x50,0x04,0x41,0x46,0x64,0x63,0x33,0x33,
		0x33,0x33,0x60,0x66,0x67,0x12,0x75,0x56,
		0x55,0x71,0x28,0x65,0x54,0x63,0x33,0x33,
		0x33,0x33,0x55,0x67,0x76,0x66,0x67,0x67,
		0x77,0x76,0x66,0x76,0x64,0x53,0x33,0x33,
		0x33,0x33,0x66,0x77,0x78,0x78,0x77,0x68,
		0x77,0x77,0x88,0x76,0x67,0x63,0x33,0x33,
		0x33,0x33,0x66,0x77,0x78,0x78,0x77,0x68,
		0x77,0x77,0x88,0x76,0x67,0x63,0x33,0x33,
		0x33,0x33,0x66,0x67,0x77,0x87,0x76,0x77,
		0x76,0x77,0x78,0x76,0x66,0x63,0x33,0x33,
		0x33,0x33,0x54,0x57,0x77,0x77,0x65,0x54,
		0x55,0x67,0x77,0x65,0x54,0x53,0x33,0x33,
		0x33,0x33,0x35,0x66,0x66,0x77,0x66,0x65,
		0x77,0x67,0x77,0x66,0x65,0x33,0x33,0x33,
		0x33,0x33,0x33,0x66,0x67,0x76,0x77,0x76,
		0x77,0x77,0x76,0x66,0x63,0x33,0x33,0x33,
		0x33,0x33,0x33,0x76,0x67,0x76,0x55,0x66,
		0x65,0x56,0x77,0x67,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x67,0x76,0x76,0x67,0x77,
		0x77,0x66,0x76,0x77,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x66,0x67,0x77,0x76,0x66,
		0x67,0x77,0x77,0x67,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x56,0x67,0x77,0x87,0x77,
		0x77,0x78,0x77,0x67,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x45,0x56,0x67,0x77,0x76,
		0x67,0x77,0x76,0x67,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x55,0x55,0x55,0x66,0x55,
		0x66,0x57,0x55,0x77,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x44,0x44,0x44,0x44,0x44,
		0x44,0x54,0x56,0x77,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x55,0x54,0x54,0x45,0x54,
		0x55,0x55,0x77,0x57,0x73,0x33,0x33,0x33,
		0x33,0x33,0x33,0x44,0x45,0x45,0x56,0x56,
		0x56,0x57,0x77,0x75,0x53,0x33,0x33,0x33,
		0x33,0x33,0x33,0x54,0x44,0x55,0x66,0x67,
		0x76,0x56,0x76,0x75,0x53,0x33,0x33,0x33,
		0x33,0x33,0x33,0x45,0x55,0x55,0x67,0x66,
		0x77,0x66,0x76,0x55,0x53,0x33,0x33,0x33
	};

		void lcd_gs_pixel(int x, int y, int amt);
		void lcd_gs_setup(char **xpm);
		void draw(int current_screen);
		bool hasMemoryCard();
		bool getcanSave();
		void setcanSave(bool s);
		int DC_SaveToVMU(char* score);
		int DC_LoadFromVMU();
	    vmu();
};
#endif