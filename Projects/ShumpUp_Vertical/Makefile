TARGET = main.elf
OBJS = main.o game.o base.o player.o enemy.o vmu.o item.o bullet.o

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

KOS_CFLAGS += -Wno-write-strings  -ml -m4-single-only -pipe -I../../include/SDL-1.2.13/include -I../include/zlib-1.2.3 -I../libpng-1.2.8

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) romdisk.o $(OBJEXTRA) -L$(KOS_BASE)/lib -lgcc -lSDL_gfx -lSDL_1213 -lSDLPVR_image -lpng -lz -ljpeg -loggvorbisplay -lstdc++ -lmp3 -lm  $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)