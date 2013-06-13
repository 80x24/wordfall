/*
############################################################################
 _       _     _     ____     ___       _____   ____    _      _
| |  _  | |  /   \  |  _  \  |  _ \    | ____| /    \  | |    | |
| | | | | | | / \ | | |_| /  | | | \   | __|  |  /\  | | |    | |
 \ \|_|/ /  | \ / | | | \ \  | |_| /   | |    | |  | | | |__  | |__
  \_/ \_/    \ _ /  |_|  \_| |___ /    |_|    |_|  |_| |____| |____| 
############################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "state.h"
#include "load.h"
#include "gamestates.h"
#define FPS 60

// state globals
int currentState = STATE_INTRO_TRANSITION;
int nextState = STATE_NULL;

int sound = 0;
int soundStarted = 0;

int highscore = 0;
int soundPref = 0;

// Surface Globals
// These should probably be reduced in scope
SDL_Surface *screen = 0;
SDL_Surface *introBackground = 0;
SDL_Surface *introTransition = 0;
SDL_Surface *background = 0;
SDL_Surface *cloud1 = 0;
SDL_Surface *cloud2 = 0;
SDL_Surface *cloud3 = 0;

SDL_Surface *title[8] = {0};

SDL_Surface *container[7] = {0};
SDL_Surface *letters[4][26] = {{0}};
SDL_Surface *containerLetters[7] = {0};

SDL_Surface *grass = 0;
SDL_Surface *play = 0;
SDL_Surface *options = 0;
SDL_Surface *optionsSound = 0;
SDL_Surface *optionsSoundOn = 0;
SDL_Surface *optionsSoundOff = 0;
SDL_Surface *optionsBack = 0;
SDL_Surface *pause = 0;
SDL_Surface *submit = 0;
SDL_Surface *notWord = 0;
SDL_Surface *score = 0;
SDL_Surface *scorePopup = 0;
SDL_Surface *pauseFontSurface = 0;
SDL_Surface *resume = 0;
SDL_Surface *returnMenu = 0;
SDL_Surface *highscoreSurface = 0;

TTF_Font *playFont = 0;
TTF_Font *optionsFont = 0;
TTF_Font *optionsSoundFont = 0;
TTF_Font *optionsSoundFontOn = 0;
TTF_Font *optionsSoundFontOff = 0;
TTF_Font *optionsBackFont = 0;
TTF_Font *scoreFontPopup = 0;
TTF_Font *notWordFont = 0;
TTF_Font *scoreFont = 0;
TTF_Font *pauseFont = 0;
TTF_Font *resumeFont = 0;
TTF_Font *returnMenuFont = 0;
TTF_Font *highscoreFont = 0;

Mix_Music *backgroundMusic = 0;
Mix_Chunk *win = 0;
Mix_Chunk *click = 0;
Mix_Chunk *error = 0;

// cloud position global because fuck the clouds.
cloud cloudPos1;
cloud cloudPos2;
cloud cloudPos3;

SDL_Event event;

int main(int argc, char *argv[])
{
	int start = 0;
	int finish = 0;
	int running = 1;

	if(init() != 0) {
		fprintf(stderr, "Initialization failed\n");
		return 1;
	}

	while(running == 1) {
		start = SDL_GetTicks();
		// ==============================
		// Events
		// ==============================
		switch(currentState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_events();
				break;
			case STATE_INTRO:
				intro_events();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_events();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_events();
				break;
			case STATE_TITLE_FALL:
				title_fall_events();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_events();
				break;
			case STATE_TITLE:
				title_events();
				break;
			case STATE_GAME_TRANSITION:
				game_transition_events();
				break;
			case STATE_GAME:
				game_events();
				break;
			case STATE_PAUSE:
				pause_events();
				break;
		}
		
		// =============================
		// Logic
		// =============================
		switch(currentState) {
			case STATE_EXIT:
				running = 0;
			case STATE_INTRO_TRANSITION:
				intro_transition_logic();
				break;
			case STATE_INTRO:
				intro_logic();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_logic();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_logic();
				break;
			case STATE_TITLE_FALL:
				title_fall_logic();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_logic();
				break;
			case STATE_TITLE:
				title_logic();
				break;
			case STATE_GAME_TRANSITION:
				game_transition_logic();
				break;
			case STATE_GAME:
				game_logic();
				break;
			case STATE_PAUSE:
				pause_logic();
				break;
		}
		
		change_state();
		
		// ============================
		// Rendering
		// ============================
		switch(currentState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_render();
				break;
			case STATE_INTRO:
				intro_render();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_render();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_render();
				break;
			case STATE_TITLE_FALL:
				title_fall_render();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_render();
				break;
			case STATE_TITLE:
				title_render();
				break;
			case STATE_GAME_TRANSITION:
				game_transition_render();
				break;
			case STATE_GAME:
				game_render();
				break;
			case STATE_PAUSE:
				pause_render();
				break;
		}
		
		finish = SDL_GetTicks();
		if((1000/FPS) > (finish - start)) {
		    SDL_Delay(1000/FPS - (finish - start));
		}
	}

	// write user preferences to file
	if(Mix_PlayingMusic() == 1) {
		sound = 1;
	}
	if(Mix_PlayingMusic() == 0) {
		sound = 0;
	}
	if(finalScore > highscore) {
		highscore = finalScore;
	}
	write_pref(highscore, "assets/userpref1.txt");
	write_pref(sound, "assets/userpref2.txt");
	quit();

	return 0;
}

int init()
{
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "SDL Initialization failed\n %s\n", SDL_GetError());
		return 1;
	}
	
	if(TTF_Init() == -1) {
		fprintf(stderr, "SDL TTF initialization failed\n %s\n", TTF_GetError());
		return 1;
	}

	if(Mix_Init(MIX_INIT_MP3) == -1) {
		fprintf(stderr, "SDL Mixer initialization failed\n%s\n", Mix_GetError());
		return 1;
	}
	// 4KB buffer might not be enough.
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		fprintf(stderr, "SDL Mix open audio failed\n%s\n", Mix_GetError());
		return 1;
	}
	
	screen = SDL_SetVideoMode(360,640,32,SDL_HWSURFACE);
	if(screen == NULL) {
		fprintf(stderr, "Video initialization failed\n %s\n", SDL_GetError());
		return 1;
	}
	
	// changing the null value you can set an icon for when the window is
	// minimized
	SDL_WM_SetCaption("Word Fall", NULL);
	
	//SDL_WM_SetIcon will set the icon for the window.
	
	/*if(load_content() != 0) {
		fprintf(stderr, "File loading failed\n");
		return 1;
	}*/

	// ===== Intro Assets called before load_content() =====
	introTransition = load_image_noalpha("assets/images/intro-transition.png");
	if(introTransition == NULL) {
		fprintf(stderr, "introTransition image not found\n%s\n", IMG_GetError());
		return 1;
	}
	
	introBackground = load_image_noalpha("assets/images/intro.png");
	if(introBackground == NULL) {
		fprintf(stderr,"Intro background image not found\n %s \n", IMG_GetError());
		return 1;
	}

	cloudPos1.x = -5;
	cloudPos1.y = 23;
	cloudPos2.x = 105;
	cloudPos2.y = 2;
	cloudPos3.x = 215;
	cloudPos3.y = 20;

	return 0;
}

int load_content()
{
	
	background = load_image_noalpha("assets/images/background.png");
	if(background == NULL) {
		fprintf(stderr, "Background image loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	// --- CLOUDS ---
	cloud1 = load_image("assets/images/clouds.png");
	if(cloud1 == NULL) {
		fprintf(stderr, "cloud 1 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	cloud2 = load_image("assets/images/clouds.png");
	if(cloud2 == NULL) {
		fprintf(stderr, "cloud 2 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	cloud3 = load_image("assets/images/clouds.png");
	if(cloud3 == NULL) {
		fprintf(stderr, "cloud 3 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	// --- TITLE WORD FALL ---
	title[0] = load_image("assets/images/letters/W.png");
	if(title[0] == NULL) {
		fprintf(stderr, "w title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[1] = load_image("assets/images/letters/O.png");
	if(title[1] == NULL) {
		fprintf(stderr, "o title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[2] = load_image("assets/images/letters/R.png");
	if(title[2] == NULL) {
		fprintf(stderr, "r title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[3] = load_image("assets/images/letters/D.png");
	if(title[3] == NULL) {
		fprintf(stderr, "d title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[4] = load_image("assets/images/letters/F.png");
	if(title[4] == NULL) {
		fprintf(stderr, "f title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[5] = load_image("assets/images/letters/A.png");
	if(title[5] == NULL) {
		fprintf(stderr, "a title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[6] = load_image("assets/images/letters/L.png");
	if(title[6] == NULL) {
		fprintf(stderr, "l title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	title[7] = load_image("assets/images/letters/L.png");
	if(title[7] == NULL) {
		fprintf(stderr, "L2 title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	
	grass = load_image("assets/images/grass-medium.png");
	if(grass == NULL) {
		fprintf(stderr, "grass loading failed\n%s\n",IMG_GetError());
		return 1;
	}

	submit = load_image("assets/images/yellow-check-yellow-small.png");
	if(submit == NULL) {
		fprintf(stderr, "Check submit button loading failed\n%s\n", IMG_GetError());
		return 1;
	}

	pause = load_image("assets/images/pause-black.png");
	if(submit == NULL) {
		fprintf(stderr, "Pause button loading failed\n%s\n", IMG_GetError());
		return 1;
	}

	// =========== CHECK USER PREFERENCES =========
	// highscore
	FILE *userPref1;
	char getPref1[64];

	userPref1 = fopen("assets/userpref1.txt", "r");
	if(userPref1 == NULL) {
		fprintf(stderr, "Error: user preference file 1 not found\n");
		return 1;
	}
	if(fgets(getPref1, 16, userPref1) != NULL) {
			highscore = atoi(getPref1);
	}
	if(highscore > 100000) {
		highscore = 100000;
	}
	fclose(userPref1);

	// sound
	FILE *userPref2;
	char getPref2[64];

	userPref2 = fopen("assets/userpref2.txt", "r");
	if(userPref2 == NULL) {
		fprintf(stderr, "Error: user preference file 2 not found\n");
		return 1;
	}
	if(fgets(getPref2, 16, userPref2) != NULL) {
		sound = atoi(getPref2);
	}
	fclose(userPref2);

	// =========== LOADING FOR LETTERS AND CONTAINERS =================
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			// This converts the array number to the corresponding ascii value.
			int asciiCode = j+65;
			// I really have no idea how this line works so I should probably
			// do some more invesitgating.
			char *letter = (char*)&asciiCode;
			char *location = "assets/images/letters/";
			char *png = ".png";
			char *final = malloc(sizeof(char)*strlen(location)+strlen(png)+1);
			strcpy(final, location);
			strcat(final, letter);
			strcat(final, png);
			letters[i][j] = load_image(final);
			if(letters[i][j] == NULL) {
				fprintf(stderr, "Letter loading failed\n%s\n", IMG_GetError());
				return 1;
			}
			free(final);
		}
	}

	for(int i = 0; i < 7; i++) {
		container[i] = load_image("assets/images/container-2.png");
		if(container[i] == NULL) {
			fprintf(stderr, "Container loading failed\n%s\n", IMG_GetError());
			return 1;
		}
	}

	playFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(playFont == NULL) {
		fprintf(stderr, "play font loading failed\n%s\n",TTF_GetError());
		return 1;
	}
	
	optionsFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsFont == NULL) {
		fprintf(stderr, "options font loading failed\n%s\n",TTF_GetError());
		return 1;
	}

	optionsSoundFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFont == NULL) {
		fprintf(stderr, "options sound font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	optionsSoundFontOn = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFontOn == NULL) {
		fprintf(stderr, "options sound font on loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	optionsSoundFontOff = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFontOff == NULL) {
		fprintf(stderr, "options sound font off loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	highscoreFont = load_font("assets/fonts/Roboto-Bold.ttf", 32);
	if(highscoreFont == NULL) {
		fprintf(stderr, "highscore font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	optionsBackFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsBackFont == NULL) {
		fprintf(stderr, "options back font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	scoreFontPopup = load_font("assets/fonts/Roboto-Bold.ttf", 20);
	if(scoreFontPopup == NULL) {
		fprintf(stderr, "score font popup loading failed\n%s\n", TTF_GetError());
		return 1;
	}
	notWordFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(notWordFont == NULL) {
		fprintf(stderr, "not word font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	scoreFont = load_font("assets/fonts/Roboto-Bold.ttf", 20);
	if(scoreFont == NULL) {
		fprintf(stderr, "score font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	pauseFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(pauseFont == NULL) {
		fprintf(stderr, "pause font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	resumeFont = load_font("assets/fonts/Roboto-Bold.ttf", 24);
	if(resumeFont == NULL) {
		fprintf(stderr, "resume font loading failed\n%s\n", TTF_GetError());
		return 1;
	}
	
	returnMenuFont = load_font("assets/fonts/Roboto-Bold.ttf", 20);
	if(returnMenuFont == NULL) {
		fprintf(stderr, "Return to main menu font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	// --- Load Sounds ---
	backgroundMusic = Mix_LoadMUS("assets/sounds/background-music/super-friendly.mp3");
	if(backgroundMusic == NULL) {
		fprintf(stderr, "background music loading failed\n%s\n", Mix_GetError());
		return 1;
	}
	
	win = Mix_LoadWAV("assets/sounds/effects/pling.wav");
	if(win == NULL) {
		fprintf(stderr, "Win music loading failed\n%s\n", Mix_GetError());
		return 1;
	}

	click = Mix_LoadWAV("assets/sounds/effects/click.wav");
	if(click == NULL) {
		fprintf(stderr, "Click music loading failed\n%s\n", Mix_GetError());
		return 1;
	}

	error = Mix_LoadWAV("assets/sounds/effects/error.wav");
	if(error == NULL) {
		fprintf(stderr, "error music loading failed\n%s\n", Mix_GetError());
		return 1;
	}

	return 0;
}

void quit()
{
	//printf("I'm quitting!!\n");
	Mix_HaltMusic();
	Mix_FreeChunk(win);
	Mix_FreeChunk(click);
	Mix_FreeChunk(error);
	Mix_FreeMusic(backgroundMusic);

	// There must be a better way to do this
	SDL_FreeSurface(background);
	SDL_FreeSurface(cloud1);
	SDL_FreeSurface(cloud2);
	SDL_FreeSurface(cloud3);
	SDL_FreeSurface(grass);
	SDL_FreeSurface(play);
	SDL_FreeSurface(options);
	SDL_FreeSurface(optionsSound);
	SDL_FreeSurface(optionsSoundOn);
	SDL_FreeSurface(optionsSoundOff);
	SDL_FreeSurface(optionsBack);
	SDL_FreeSurface(introBackground);
	SDL_FreeSurface(introTransition);
	SDL_FreeSurface(pause);
	SDL_FreeSurface(submit);
	SDL_FreeSurface(score);
	SDL_FreeSurface(scorePopup);
	SDL_FreeSurface(notWord);
	SDL_FreeSurface(pauseFontSurface);
	SDL_FreeSurface(resume);
	SDL_FreeSurface(returnMenu);
	SDL_FreeSurface(highscoreSurface);

	for(int i = 0; i < 8; i++) {
		SDL_FreeSurface(title[i]);
	}
	
	for(int i = 0; i < 7; i++) {
		SDL_FreeSurface(container[i]);
	}
	
	// Free all of the letters
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			SDL_FreeSurface(letters[i][j]);
		}
	}
	// Free Letters in the containers
	for(int i = 0; i < 7; i++) {
		SDL_FreeSurface(containerLetters[i]);
	}
	
	SDL_FreeSurface(screen);

	TTF_CloseFont(playFont);
	TTF_CloseFont(optionsFont);
	TTF_CloseFont(optionsSoundFont);
	TTF_CloseFont(optionsSoundFontOn);
	TTF_CloseFont(optionsSoundFontOff);
	TTF_CloseFont(optionsBackFont);
	TTF_CloseFont(scoreFontPopup);
	TTF_CloseFont(notWordFont);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(pauseFont);
	TTF_CloseFont(resumeFont);
	TTF_CloseFont(returnMenuFont);
	TTF_CloseFont(highscoreFont);

	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void write_pref(int value, char *location)
{
	FILE *fp;
	char buffer[64];
	sprintf(buffer, "%d", value);
	fp = fopen(location, "w");
	fputs(buffer, fp);
	fclose(fp);
}
