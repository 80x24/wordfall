#ifndef _main_h
#define _main_h

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

enum gameStates {
	STATE_NULL,
	STATE_EXIT,
	STATE_INTRO_TRANSITION,
	STATE_INTRO,
	STATE_INTRO_TRANSITION_FADE,
	STATE_TITLE_TRANSITION,
	STATE_TITLE,
	
};

int currentState;
int nextState;
int running;
int alpha;

int init();
void quit();
int load_content();
void trainsition(int miliseconds);

// ============= SDL Surfaces =====================
// Everything is loaded at startup
SDL_Surface *screen;
SDL_Surface *introBackground;
SDL_Surface *introTransition;
SDL_Surface *background;
SDL_Surface *cloud1;
SDL_Surface *cloud2;
SDL_Surface *cloud3;

SDL_Surface *wTitle;
SDL_Surface *oTitle;
SDL_Surface *rTitle;
SDL_Surface *dTitle;

SDL_Surface *fTitle;
SDL_Surface *aTitle;
SDL_Surface *lTitle;
SDL_Surface *l2Title;

SDL_Surface *grass;

SDL_Surface *play;
SDL_Surface *options;
TTF_Font *playFont;
TTF_Font *optionsFont;
// =================================================
SDL_Event event;

#endif
