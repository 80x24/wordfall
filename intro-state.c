#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

int introTimeStart = 0;

void intro_init(void) 
{
	introTimeStart = SDL_GetTicks();
	if(load_content() != 0) {
		fprintf(stderr, "File loading failed\n");
		exit(1);
	}
}

void intro_events(void)
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

void intro_logic(void)
{
	if(SDL_GetTicks() - introTimeStart >= 1000) {
		set_next_state(STATE_INTRO_TRANSITION_FADE);
	}
}

void intro_render(void)
{
	render_image(0,0,introBackground,screen);
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}