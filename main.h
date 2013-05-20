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

#define GRASS_Y 540

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
	STATE_GAME_TRANSITION,
	STATE_PAUSE,
};

typedef struct {
	int x;
	int y;
}cloud;

// state globals
extern int currentState;
extern int nextState;

// Dictionary globals
extern char **dict;
extern int dictNum;

// sound global
extern int sound;

extern int alpha;

int init();
void quit();
int load_content();

// ============= SDL Surfaces =====================
// Everything is loaded at startup
// These are essentially all global variables. There should actually be a
// function in each state where I do loading and initialization, but I am kind
// of too far in to implement that now. I might have to implement it in the
// future if the main game states get too complicated, but the way I am
// currently implementing states is very stupid.

extern SDL_Surface *screen;
extern SDL_Surface *introBackground;
extern SDL_Surface *introTransition;
extern SDL_Surface *background;
extern SDL_Surface *cloud1;
extern SDL_Surface *cloud2;
extern SDL_Surface *cloud3;

extern SDL_Surface *title[8];

extern SDL_Surface *container[7];
extern SDL_Surface *letters[4][26];
extern SDL_Surface *containerLetters[7];

extern SDL_Surface *grass;
extern SDL_Surface *play;
extern SDL_Surface *options;
extern SDL_Surface *optionsSound;
extern SDL_Surface *optionsSoundOn;
extern SDL_Surface *optionsSoundOff;
extern SDL_Surface *optionsBack;
extern SDL_Surface *pause;
extern SDL_Surface *submit;
extern SDL_Surface *scorePopup;
extern SDL_Surface *notWord;
extern SDL_Surface *score;
extern SDL_Surface *pauseFontSurface;
extern SDL_Surface *resume;
extern SDL_Surface *returnMenu;

extern TTF_Font *playFont;
extern TTF_Font *optionsFont;
extern TTF_Font *optionsSoundFont;
extern TTF_Font *optionsSoundFontOn;
extern TTF_Font *optionsSoundFontOff;
extern TTF_Font *optionsBackFont;
extern TTF_Font *scoreFontPopup;
extern TTF_Font *notWordFont;
extern TTF_Font *scoreFont;
extern TTF_Font *pauseFont;
extern TTF_Font *resumeFont;
extern TTF_Font *returnMenuFont;

extern Mix_Music *backgroundMusic;
extern Mix_Chunk *win;
extern Mix_Chunk *click;
extern Mix_Chunk *error;

// =================================================
extern SDL_Event event;
extern cloud cloudPos1;
extern cloud cloudPos2;
extern cloud cloudPos3;

#endif
