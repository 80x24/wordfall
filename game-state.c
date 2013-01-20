#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "game-state.h"

int gameInit = 0;
int letterDrag = 0;

char words[7] = {0,0,0,0,0,0,0};

char lettersAscii[26];

int lettersY[26];
int lettersX [26];

SDL_Rect lettersRect[26];
SDL_Rect submitRect;

void game_events(void)
{
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				if((event.motion.x > submitRect.x) &&
					(event.motion.x < submitRect.x + submitRect.w) &&
					(event.motion.y > submitRect.y) &&
					(event.motion.y < submitRect.y + submitRect.h)) {
					printf("Submit button clicked\n");
				}
				int i = 0;
				if((event.motion.x > lettersRect[i].x) &&
					(event.motion.x < lettersRect[i].x + lettersRect[i].w) &&
					(event.motion.y > lettersRect[i].y) &&
					(event.motion.y < lettersRect[i].y + lettersRect[i].h)) {
					letterDrag = 1;
				}
			}
		}
		else if(event.type == SDL_MOUSEBUTTONUP) {
			letterDrag = 0;
		}
	}
}

void game_logic(void)
{
	if(!gameInit) {
		// I'm currently using this for one time
		// initialization which is bad. 
		submitRect.x = submitX;
		submitRect.y = submitY;
		submitRect.w = submit->clip_rect.w;
		submitRect.h = submit->clip_rect.h;

		for(int i = 0; i < 26; i++) {
			lettersAscii[i] = 97+i;
			lettersX[i] = 50;
			lettersY[i] = 50;
			lettersRect[i].x = lettersX[i];
			lettersRect[i].y = lettersY[i];
			lettersRect[i].w = letters[i]->clip_rect.w;
			lettersRect[i].h = letters[i]->clip_rect.h;
		}

		gameInit += 1;
	}
	if(letterDrag) {
		//printf("x: %d\n", event.motion.x);
		//printf("y: %d\n", event.motion.y);
		int i = 0;
		lettersX[i] = event.motion.x;
		lettersY[i] = event.motion.y;
		//printf("lettersX[%d] %d\n", i, lettersX[i]);
		//printf("lettersY[%d] %d\n", i, lettersY[i]);
		lettersRect[i].x = event.motion.x;
		lettersRect[i].y = event.motion.y;
	}

	// This for loop within the main loop might be bad.
	for(int i = 0; i < 26; i++) {
		lettersRect[i].x = lettersX[i];
		lettersRect[i].y = lettersY[i];
	}
	//printf("lettersRect[%d].x: %d\n", i, lettersRect[i].x);
	//printf("lettersRect[%d].y: %d\n", i, lettersRect[i].y);
	lettersY[0]++;
}

void game_render(void)
{	
	render_image(0,0,background,screen);

	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);

	if(lettersY[0] <= 500) {
		render_image(lettersX[0], lettersY[0], letters[0], screen);
	}

	render_image(0,GRASS_X,grass,screen);

	// Containers
	for(int i = 0; i < 7; i++) {
		render_image(containerX[i], containerY, container[i], screen);
	}

	if(lettersY[0] >= 500) {
		// Falling Letters
		render_image(lettersX[0], lettersY[0], letters[0], screen);
	}

	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	render_image(pauseX, pauseY, pause, screen);

	

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}