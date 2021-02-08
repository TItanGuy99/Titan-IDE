/*Code and engine made by Titan Game Studios 2016/2017 coded by Luiz Nai.*/
#include "vmu.h"

/* Only this XPM will work with this code.. it's too cheap to actually
   do any parsing =) */
#include "vmu/graphic.xpm"
#include "vmu/graphic2.xpm"

///Main class for the VMU
vmu::vmu()
{
	addr = maple_enum_type(0, MAPLE_FUNC_LCD);
    vmu::draw(1);
    letSaving = false;

    if(hasMemoryCard()) {
        letSaving = true;
    }
}

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
void vmu::lcd_gs_setup(char **xpm) 
{
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

void vmu::draw(int current_screen) {
	int frame = 0;

    switch (current_screen)
    {
        case 1:
            lcd_gs_setup(graphic_xpm + 12);
            break;
        
        case 2:
            lcd_gs_setup(graphic_xpm2 + 12);
            break;

        case 3:
            //lcd_gs_setup(graphic_xpm3 + 12);
            break;

        case 4:
            //lcd_gs_setup(graphic_xpm4 + 12);
            break;

        case 5:
            //lcd_gs_setup(graphic_xpm5 + 12);
            break;
    }

    if(addr) {
        int rv = vmu_draw_lcd(addr, lcd_disp + frame);

        if(rv < 0)
            printf("got error %d\n", rv);
        else {
            frame=0;
        }
    }
}

bool vmu::hasMemoryCard() {
    if(maple_enum_type_ex(0, MAPLE_FUNC_MEMCARD, 0x00020000)) {
        return true;
    }
    else {
        return false;
    }
}

void vmu::setcanSave(bool l) {
    if(hasMemoryCard()) {
        letSaving = l;
    }
    else {
        letSaving = false;
    }
}

bool vmu::getcanSave() {
    if(hasMemoryCard()) {
        return letSaving;
    }
    else {
        return false;
    }
}

int vmu::DC_SaveToVMU(char* score) {
    if(hasMemoryCard() && letSaving) {
        fs_rmdir("/ram/yourfile.dat");
        file_t myfile;
        myfile = fs_open("/ram/yourfile.dat", O_RDWR);
        int myfilesize = fs_total(myfile);
        fs_write(myfile, score, strlen(score) + 1);
        fs_close(myfile);

        vmu_pkg_t pkg;
        uint8 *pkg_out;
        int pkg_size;
        file_t ft;

        // Temporal for reading the file
        file_t file;
        int data_size;
        unsigned long zipsize = 0;
        uint8 *datasave;
        uint8 *zipdata;
        
        // Open file and copy to buffer
        file = fs_open("/ram/yourfile.dat", O_RDONLY);
        data_size = fs_total(file);
        datasave = (uint8 *)malloc(data_size+1);
        fs_read(file, datasave, data_size);
        fs_close(file);
        
        // Allocate some memory for compression
        zipsize = data_size * 2;
        zipdata = (uint8*)malloc(zipsize);

        // The compressed save
        compress(zipdata, &zipsize, datasave, data_size);

        // Make the package to the VMU.
        strcpy(pkg.desc_short, "metalcanary");
        strcpy(pkg.desc_long, "Metal Canary");
        strcpy(pkg.app_id, "metalcanary");
        pkg.icon_cnt = 1;
        memcpy((void *)&pkg.icon_pal[0],icon_data,32);
        pkg.icon_data = icon_data;
        pkg.icon_anim_speed = 0;
        pkg.eyecatch_type = VMUPKG_EC_NONE;
        pkg.data_len = zipsize;
        pkg.data = zipdata;
        vmu_pkg_build(&pkg, &pkg_out, &pkg_size);

        // Write at A1 port
        fs_unlink("/vmu/a1/metalcanary");
        ft = fs_open("/vmu/a1/metalcanary", O_RDWR);
        if (!ft) {
            return -1;
        }
        fs_write(ft, pkg_out, pkg_size);
        fs_close(ft);

        // Free unused memory
        free(pkg_out);
        free(datasave);
        free(zipdata);
        
        return 0;
    }
    else {
        return -1;
    }
}

int vmu::DC_LoadFromVMU() {
   if(hasMemoryCard()) { 
        char *dst = "metalcanary";
        char src[32];
        int file;
        int filesize;
        unsigned long unzipsize;
        uint8* data;
        uint8* unzipdata;
        vmu_pkg_t pkg;
        // Our VMU + full save name
        strcpy(src, "/vmu/a1/");
        strcat(src, dst);
        // Remove VMU header
        file = fs_open(src, O_RDONLY);
        if(file <= 0) return -1;
        filesize = fs_total(file);
        if(filesize <= 0) return -1;
        data = (uint8*)malloc(filesize);
        fs_read(file, data, filesize);
        vmu_pkg_parse(data, &pkg);
        fs_close(file);
        // Allocate memory for the uncompressed data
        unzipdata = (uint8 *)malloc(524288); //512KB
        unzipsize = 524288;
        uncompress(unzipdata, &unzipsize, (uint8 *)pkg.data, pkg.data_len);

        // Save buffer into a RAM file
        file_t fd2;
        if ((fd2 = fs_open("/ram/yourfile.dat", O_RDWR)) == -1)
        {
            printf("Can't create RAM file from VMU.\n");
            return -1;
        }
        fs_write(fd2, unzipdata, unzipsize);
        fs_close(fd2);

        // Free unused memory
        free(unzipdata);

        return 0;
   }
   else {
       return -1;
   }
}