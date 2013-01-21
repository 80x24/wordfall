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
int letter1 = 0;
int letter2 = 0;
int randomLetter = 0;
int randomFallSpot = 0;

int lettersY[4][26];
int lettersX[4][26];

SDL_Rect lettersRect[4][26];
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
				for(int i = 0; i < 4; i++) {
					for(int j = 0; j < 26; j++) {
						if((event.motion.x > lettersRect[i][j].x) &&
							(event.motion.x < lettersRect[i][j].x + lettersRect[i][j].w) &&
							(event.motion.y > lettersRect[i][j].y) &&
							(event.motion.y < lettersRect[i][j].y + lettersRect[i][j].h)) {
							letterDrag = 1;
							letter1 = i;
							letter2 = j;
						}
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

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 26; j++) {
				lettersX[i][j] = (i*75)+15;
				lettersY[i][j] = 45;
				lettersRect[i][j].x = lettersX[i][j];
				lettersRect[i][j].y = lettersY[i][j];
				lettersRect[i][j].w = letters[i][j]->clip_rect.w;
				lettersRect[i][j].h = letters[i][j]->clip_rect.h;
			}
		}
		randomFallSpot = rand() % 4;
		randomLetter = rand() % 26;
		lettersY[randomFallSpot][randomLetter]++;
		printf("Random init letter is [%d][%d]\n", randomFallSpot, randomLetter);
		gameInit += 1;
	}

	// This is going to be a problem if it randomly picks a letter that
	// is already on the screen, but I will deal with that later.
	// Basically if it picks a letter that is already on the screen all it
	// is going to do is add one to the letter instead of introducing another
	// letter. Preliminary testing is showing that this isn't going to be
	// a problem, but this could definitely be improved with some sort of list
	// that is storing the current letters.
	if(SDL_GetTicks() - timeStart >= 1000) {
		randomFallSpot = rand() % 4;
		randomLetter = rand() % 26;
		lettersY[randomFallSpot][randomLetter]++;
		printf("Random letter chosen from timer [%d][%d]\n", randomFallSpot, randomLetter);
		timeStart = SDL_GetTicks();
	}

	if(letterDrag) {
		drag_letter(letter1, letter2);
	}

	// This for loop within the main loop might be bad.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			lettersRect[i][j].x = lettersX[i][j];
			lettersRect[i][j].y = lettersY[i][j];
		}
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			if(lettersY[i][j] != 45) {
				lettersY[i][j]++;
			}
			if(lettersY[i][j] >= 640) {
				lettersY[i][j] = 45;
			}
		}
	}
}

void game_render(void)
{	
	render_image(0,0,background,screen);

	if(gameInit) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 26; j++) {
				if(lettersY[i][j] <= GRASS_Y) {
					render_image(lettersX[i][j], lettersY[i][j], letters[i][j], screen);
				}
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
	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	render_image(pauseX, pauseY, pause, screen);
	
	if(letterDrag) { 
		if(lettersY[letter1][letter2] >= GRASS_Y - lettersRect[0][0].h){
			render_image(lettersX[letter1][letter2], lettersY[letter1][letter2], letters[letter1][letter2], screen);
		}
	}

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}

void drag_letter(int letter1, int letter2)
{
	// There are serious issues with this code right now
	// but it is good enough for now. For the majority of the
	// time the user isn't going to be dragging the letter
	// off of the screen.
	if(event.motion.x >= 360 - lettersRect[0][0].w) {
		event.motion.x = 360 - lettersRect[0][0].w;
	}
	else if(event.motion.y >= 640 - lettersRect[0][0].h) {
		event.motion.y = 640 - lettersRect[0][0].h;
	}
	if(event.motion.x && event.motion.y != 0) {
		lettersX[letter1][letter2] = event.motion.x;
		lettersY[letter1][letter2] = event.motion.y;
		lettersRect[letter1][letter2].x = event.motion.x;
		lettersRect[letter1][letter2].y = event.motion.y;
	}
}