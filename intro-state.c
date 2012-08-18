#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"


void intro_events()
{
	//printf("intro\n");
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
}

void intro_logic()
{
	static int tmp = 1;
	if(tmp == 1) {
		introTimeStart = SDL_GetTicks();
		tmp -= 1;
	}
	
	if(SDL_GetTicks() - introTimeStart >= 1000) {
		alpha = 255;
		set_next_state(STATE_INTRO_TRANSITION_FADE);
	}
}

void intro_render()
{
	render_image(0,0,introBackground,screen);
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}