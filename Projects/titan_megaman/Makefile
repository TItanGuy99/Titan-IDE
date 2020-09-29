all: rm-elf main.elf

include $(KOS_BASE)/Makefile.rules

OBJS = main.o game.o base.o player.o bullet.o enemy.o vmu.o dreamroqlib.o

KOS_LOCAL_CFLAGS = -I -Os
	
clean:
	-rm -f main.elf $(OBJS)
	-rm -f romdisk.*

dist:
	-rm -f $(OBJS)
	-rm -f romdisk.*
	$(KOS_STRIP) main.elf
	
rm-elf:
	-rm -f main.elf
	-rm -f romdisk.*

main.elf: $(OBJS) romdisk.o 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $@ $(KOS_START) $^ -lSDL -lstdc++ -lmp3 -lm $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f $@ -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk $@

run: main.elf
	$(KOS_LOADER) $<