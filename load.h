#ifndef _load_h
#define _load_h
#if __APPLE__
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>
#include <SDL_mixer/SDL_mixer.h>
	
#else

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#endif

SDL_Surface *load_image(const char *location);
SDL_Surface *load_image_noalpha(const char *location);
Mix_Music *load_sound(const char *location);
TTF_Font *load_font(const char *location, int fontSize);

#endif
