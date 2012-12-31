#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "game-state.h"


void game_events()
{	
	printf("current state: %d\n", currentState);
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
}

void game_logic()
{

}

void game_render()
{	
	render_image(0,0,background,screen);
	
	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);
	
	render_image(0,GRASS_X,grass,screen);

	// Containers
	for(int i = 0; i < 7; i++) {
		render_image(containerX[i], containerY, container[i], screen);
	}
	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	render_image(pauseX, pauseY, pause, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}