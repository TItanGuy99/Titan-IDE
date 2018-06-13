./download.sh --no-deps
./unpack.sh --no-deps
make
cd ../..
cp doc/environ.sh.sample ./environ.sh
chmod u+x environ.sh
source environ.sh
make
cd ../kos-ports
cd utils
./build-all
cd ..
cd ..
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
../kos-ports/utils/build-all.sh
cd Projects
dir
mkdir Projects
cd Projects
dir
cd png
make
cd ..
cd ..
cd ..
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd png
make clean
make
cd ..
cd png
dir
make clean
make
cd ..
cd sdl_engine
make
make clean
cd ..
cd ..
cd ..
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
dir
cd Projects
dir
cd sdl_engine
make clean
make
make clean
make
make clean
make clean
make
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd sdl_engine
make
make clean
make
cd ..
dir
cd png
dir
make
make clean
make
cd ..
dir
cd framerate
dir
make
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd ..
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd png
make
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd ..
cd ..
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd sdl_engine
make clean
make
make clean
make
cd ..
dir
cd sdl
make
make
cd ..
dir
cd vmu
make
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd ..
cd ..
dr
dir
cd Projects
dir
make
make clean
make
cd sdl_engine
dir
make
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
dir
make
make
cd Projects
dir
cd png
make
dir
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd sdl_engine
make clean
make
make
make
cd ..
cd ..
cd ..
cd ..
make clean
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd png
dir
make clean
make
cd ..
cd sdl_engine
make
make clean
make clean
make
make clean
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd png
dir
make
dir
dir
make
dir
cd ..
cd sdl
dir
make
cd ..
dir
dir
cd parallax
make
make 
cd ..
dir
cd hello
dir
make
cd ..
dir
cd openggs
dir
make
cd ..
dir
dir
make
cd ..
cd ..
cd ..
mkdir dc2
cd dc2
dir
git clone git://git.code.sf.net/p/cadcdev/kallistios kos
git clone git://git.code.sf.net/p/cadcdev/kos-ports
cd kos-ports
git submodule update --init
cd ../kos/utils/dc-chain
./download.sh --no-deps
make
./unpack.sh --no-deps
make
cd ../..
cp doc/environ.sh.sample ./environ.sh
chmod u+x environ.sh
source environ.sh
make
cd ../kos-ports
cd utils
./build-all
cd ..
cd ..
cd ..
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
dir
cd png
make
make
make
make
make
cd..
cd ..
cd ..
cd ..
cd ..
cd dc2
cd kos
chmod u+x environ.sh
source environ.sh
make
../kos-ports/utils/build-all.sh
cd Projects
cd examples
dir
cd dreamcast
cd png
make
cd ..
cd ..
cd..
cd..
cd ..
cd ..
cd ..
dir
clean
clear
dir
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
cd Projects
cd png
make
cd ..
cd sdl_engine
make clean
make
sh-elf-objcopy -R .stack -O binary example.elf output.bin
dir
sh-elf-objcopy -R .stack -O binary main.elf output.bin
../../utils/scramble/scramble output.bin 1st_read.bin
dreamcast.sh
dir
dreamcast.sh
cd dc
cd kos
chmod u+x environ.sh
source environ.sh
make
../kos-ports/utils/build-all.sh
cd Projects
cd sdl_engine
make clean
make
cd ..
cd ..
cd ..
cd ..
cd ..
c d..
cd ..
cd ..
dir
cd ..
dir
cd..
cd ..
cd ..
cd .
cd .
cd ..
cd ..
cd ..
cd home
cd c:
dir
dir
dir
git clone https://github.com/kubilus1/gendev.git
dir
cd gendev
make
make
dir
cd examples
dir
cd 3d_example
dir
make
cd ..
cd ..
make
dir
cd gendev
dir
cd examples
dir
cd 3d_example_2
dir
make
cd ..
cd ..
make
dir
rmdir gendev
rm -rf gendev
rmdir gendev
dir
clear
git clone https://github.com/kubilus1/gendev.git
dir
cd gendev
dir
make
make install
dir
cd gendev
dir
cd examples
dir
cd 3d_example_2
make
cd ..
cd ..
cd ..
dir
cd dendev
cd gendev
dir
cd examples
dir
cd 3d_example_2
make
make
make
dir
cd gendev
dir
cd examples
dir
cd 3d_example_2
dir
make
make
cd ..
cd ..
dir
cd examples
dir
cd 3d_example
dir
make
make
dir
cd gendev
make
dir
cd gendev
dir
make
cd ..
dir
dir
dir
cd gendev
make
make
cd ..
dir
cd gendev
make
cd ..
dir
git clone https://github.com/kubilus1/gendev.git
git clone https://github.com/kubilus1/gendev.git
git clone https://github.com/kubilus1/gendev.git
cd gendev
dir
make
make
dir
cd examples
dir
cd 3d_example
dir
make
make
cd ..
cd ..
make
make
make
make
make
exit
exit
exit
exi
exit
exit
exit
cd ..
cd my_game_pc
g
g++ *.cpp -lSDL
clear
exit
exit
