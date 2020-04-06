# NOTICE: This is a development script which uses clang++ to compile and run
# the engine for debugging purposes only. It assumes you have sdl and sdl_image
# installed in default locations and you are running on a mac.

clang++ src/**/*.cpp src/**/**/*.cpp --std=c++2a -F/Library/Frameworks -framework SDL2 -framework SDL2_image
./a.out
rm a.out
