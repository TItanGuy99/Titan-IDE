TARGET = main.elf
OBJS = main.o game.o base.o player.o enemy.o vmu.o item.o bullet.o animloop.o rumble.o animfonts.o

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

KOS_CFLAGS += -Wno-write-strings  -ml -m4-single-only -pipe -I../../include/dreamhal/inc

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.* romdisk2.* *.bin

rm-elf:
	-rm -f $(TARGET) romdisk.* romdisk2.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -lgcc -lSDL_gfx -lSDL_1213 -lSDLPVR_image -lpng -lz -lstdc++ -lm -ldreamroq $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d menu -v
	$(KOS_GENROMFS) -f romdisk2.img -d stage1 -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o
	
romdisk2.o: romdisk2.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk2.img romdisk romdisk2.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)