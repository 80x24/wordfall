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
int letter = 0;
int randomLetter = 0;

char words[7] = {0,0,0,0,0,0,0};

char lettersAscii[26];

int lettersY[26];
int lettersX [26];

SDL_Rect lettersRect[26];
SDL_Rect submitRect;

int fallStart = 0;

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
				for(int i = 0; i < 26; i++) {
					if((event.motion.x > lettersRect[i].x) &&
						(event.motion.x < lettersRect[i].x + lettersRect[i].w) &&
						(event.motion.y > lettersRect[i].y) &&
						(event.motion.y < lettersRect[i].y + lettersRect[i].h)) {
						letterDrag = 1;
						letter = i;
					}
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
		timeStart = SDL_GetTicks();
		// I'm currently using this for one time
		// initialization which is bad. 
		submitRect.x = submitX;
		submitRect.y = submitY;
		submitRect.w = submit->clip_rect.w;
		submitRect.h = submit->clip_rect.h;

		for(int i = 0; i < 26; i++) {
			lettersAscii[i] = 97+i;
			lettersX[i] = 75;
			lettersY[i] = 50;
			lettersRect[i].x = lettersX[i];
			lettersRect[i].y = lettersY[i];
			lettersRect[i].w = letters[i]->clip_rect.w;
			lettersRect[i].h = letters[i]->clip_rect.h;
		}

		randomLetter = rand() % 25;
		printf("randomLetter: %d\n", randomLetter);
		lettersY[randomLetter]++;
		// between 50-360
		int randomXPos = rand() % 260+50;
		lettersX[randomLetter] = randomXPos;
		gameInit += 1;
	}
	if(letterDrag) {
		drag_letter(letter);
	}

	// This for loop within the main loop might be bad.
	for(int i = 0; i < 26; i++) {
		lettersRect[i].x = lettersX[i];
		lettersRect[i].y = lettersY[i];
	}
	lettersY[randomLetter]++;
}

void game_render(void)
{	
	render_image(0,0,background,screen);

	if(gameInit) {
		for(int i = 0; i < 26; i++) {
			if(lettersY[i] <= GRASS_Y - lettersRect[0].h) {
				render_image(lettersX[i], lettersY[i], letters[i], screen);
			}
		}
	}

	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);

	render_image(0,GRASS_Y,grass,screen);

	// Containers
	for(int i = 0; i < 7; i++) {
		render_image(containerX[i], containerY, container[i], screen);
	}
	
	for(int i = 0; i < 26; i++) {
		if(lettersY[i] >= GRASS_Y - lettersRect[0].h){
			render_image(lettersX[i], lettersY[i], letters[i], screen);
		}
	}

	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	render_image(pauseX, pauseY, pause, screen);

	

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}

void drag_letter(int letter)
{
	// There are serious issues with this code right now
	// but it is good enough for now. For the majority of the
	// time the user isn't going to be dragging the letter
	// off of the screen.
	if(event.motion.x >= 360 - lettersRect[0].w) {
		event.motion.x = 360 - lettersRect[0].w;
	}
	else if(event.motion.y >= 640 - lettersRect[0].h) {
		event.motion.y = 640 - lettersRect[0].h;
	}
	if(event.motion.x && event.motion.y != 0) {
		lettersX[letter] = event.motion.x;
		lettersY[letter] = event.motion.y;
		lettersRect[letter].x = event.motion.x;
		lettersRect[letter].y = event.motion.y;
	}
}