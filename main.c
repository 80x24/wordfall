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
		}
		
		finish = SDL_GetTicks();
		if((1000/FPS) > (finish - start)) {
		    SDL_Delay(1000/FPS - (finish - start));
		}
	}

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
	
	screen = SDL_SetVideoMode(360,640,32,SDL_HWSURFACE);
	if(screen == NULL) {
		fprintf(stderr, "Video initialization failed\n %s\n", SDL_GetError());
		return 1;
	}
	
	// changing the null value you can set an icon for when the window is
	// minimized
	SDL_WM_SetCaption("Word Fall", NULL);
	
	//SDL_WM_SetIcon will set the icon for the window.
	
	if(load_content() != 0) {
		fprintf(stderr, "File loading failed\n");
		return 1;
	}

	return 0;
}

int load_content()
{
	// ===== Intro =====
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

	// =========== LOADING FOR LETTERS AND CONTAINERS =================
	for(int i = 0; i < 26; i++) {
		// This function converts the array number to the corresponding
		// ascii value.
		int asciiCode = i+65;
		// I really have no idea how this line works so I should probably
		// do some more invesitgating.
		char *letter = (char*)&asciiCode;
		char *location = "assets/images/letters/";
		char *png = ".png";
		char *final = malloc(sizeof(char)*strlen(location)+strlen(png)+1);
		strcpy(final, location);
		strcat(final, letter);
		strcat(final, png);
		letters[i] = load_image(final);
		if(letters[i] == NULL) {
			fprintf(stderr, "Letter loading failed\n%s\n", IMG_GetError());
			return 1;
		}
		free(final);
	}

	for(int i = 0; i < 7; i++) {
		container[i] = load_image("assets/images/container-2.png");
		if(container[i] == NULL) {
			fprintf(stderr, "Container loading failed\n%s\n", IMG_GetError());
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
	optionsBackFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsBackFont == NULL) {
		fprintf(stderr, "options back font loading failed\n%s\n", TTF_GetError());
		return 1;
	}
	return 0;
}

void quit()
{
	//printf("I'm quitting!!\n");

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

	for(int i = 0; i < 8; i++) {
		SDL_FreeSurface(title[i]);
	}
	
	for(int i = 0; i < 7; i++) {
		SDL_FreeSurface(container[i]);
	}
	
	for(int i = 0; i < 27; i++) {
		SDL_FreeSurface(letters[i]);
	}
	
	SDL_FreeSurface(screen);

	TTF_CloseFont(playFont);
	TTF_CloseFont(optionsFont);
	TTF_CloseFont(optionsSoundFont);
	TTF_CloseFont(optionsSoundFontOn);
	TTF_CloseFont(optionsSoundFontOff);
	TTF_CloseFont(optionsBackFont);

	TTF_Quit();
	SDL_Quit();
}
