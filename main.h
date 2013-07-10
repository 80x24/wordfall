/*
This file is part of Word Fall.

Word Fall is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Word Fall is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Word Fall.  If not, see <http://www.gnu.org/licenses/>.
*/

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

// user preference globals
extern int highscore;
extern int soundPref;

// sound global
extern int sound;
extern int soundStarted;

extern int alpha;
extern int finalScore;

int init();
void quit();
int load_content();
void write_pref(int value, char *location);

// ============= SDL Surfaces =====================
// Everything is loaded at startup
// These are essentially all global variables.

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
extern SDL_Surface *highscoreSurface;

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
extern TTF_Font *highscoreFont;

extern Mix_Music *backgroundMusic;
extern Mix_Chunk *win;
extern Mix_Chunk *click;
extern Mix_Chunk *error;

extern SDL_Event event;
extern cloud cloudPos1;
extern cloud cloudPos2;
extern cloud cloudPos3;

#endif
