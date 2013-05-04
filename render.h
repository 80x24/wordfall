#ifndef _render_h
#define _render_h

#if __APPLE__
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#endif

void render_image(int x, int y, SDL_Surface *source, SDL_Surface *destination);
SDL_Surface *render_font(TTF_Font *font, const char *text, SDL_Color color);
void render_music(Mix_Music *music, int loops);

#endif
