CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
LDFLAGSOSX=-framework SDL -framework SDL_image -framework SDL_ttf -framework SDL_mixer -framework Cocoa
LDFLAGSLINUX=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJECTS=main.o load.o render.o state.o intro-state.o intro-transition-state.o \
title-state.o title-transition-state.o title-fall-state.o title-options-state.o \
game-state.o game-transition-state.o pause-state.o
OBJECTSOSX=SDLMain.o
OBJECTSLINUX=
CFILES=main.c load.c render.c state.c intro-state.c intro-transition-state.c \
title-state.c title-transition-state.c title-fall-state.c title-options-state.c \
game-state.c game-transition-state.c pause-state.c
OSXEXTRA=SDLMain.m
LINUXEXTRA=
all:
	@echo "usage: make osx or make linux"
osx:
	$(CC) $(CFLAGS) -c $(CFILES) $(OSXEXTRA)
	$(CC) $(CFLAGS) $(LDFLAGSOSX) $(OBJECTS) $(OBJECTSOSX) -o word-fall
linux:
	$(CC) $(CFLAGS) -c $(CFILES) $(LINUXEXTRA)
	$(CC) $(CFLAGS) $(LDFLAGSLINUX) $(OBJECTS) $(OBJECTSLINUX) -o word-fall
clean:
	rm -rf $(OBJECTS) $(OBJECTSLINUX) $(OBJECTSOSX)
install:
	cp word-fall /usr/local/bin
