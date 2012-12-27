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
	STATE_INTRO_TRANSITION_FADE,
	STATE_INTRO,
	STATE_TITLE_TRANSITION,
	STATE_TITLE_FALL,
	STATE_TITLE_OPTIONS,
	STATE_TITLE,
	STATE_GAME,
};

int currentState;
int nextState;
int running;
int alpha;

// Word Fall logo globals
int wTitleY;
int oTitleY;
int rTitleY;
int dTitleY;
int fTitleY;
int aTitleY;
int lTitleY;
int l2TitleY;
int wordY;
int fallY;

// options highlight globals. These are currently global due to a bug where
// the back button on the options screen will stay yellow until the mouse is
// moved. May be able to figure out how to make these local later.
int soundOnHighlight;
int soundOffHighlight;
int backHighlight;
int playRectHighlight;
int optionsRectHighlight;

int init();
void quit();
int load_content();
void trainsition(int miliseconds);

// ============= SDL Surfaces =====================
// Everything is loaded at startup
// These are essentially all global variables. There should actually be a
// function in each state where I do loading and initialization, but I am kind of
// too far in to implement that now. I might have to implement it in the future
// if the main game states get too complicated, but the way I am currently
// implementing states is very stupid. I am copy pasting code, and it is turning
// into spaghetti.
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

SDL_Surface *container[7];
SDL_Surface *letters[27];

SDL_Surface *grass;
SDL_Surface *play;
SDL_Surface *options;
SDL_Surface *optionsSound;
SDL_Surface *optionsSoundOn;
SDL_Surface *optionsSoundOff;
SDL_Surface *optionsBack;
SDL_Surface *pause;
SDL_Surface *submit;


TTF_Font *playFont;
TTF_Font *optionsFont;
TTF_Font *optionsSoundFont;
TTF_Font *optionsSoundFontOn;
TTF_Font *optionsSoundFontOff;
TTF_Font *optionsBackFont;
TTF_Font *pauseFont;
// =================================================
SDL_Event event;

#endif
