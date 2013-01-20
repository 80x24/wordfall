#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

extern int alpha;

void title_transition_events(void)
{
	//printf("title transition\n");
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
}

void title_transition_logic(void)
{
	//printf("title alpha: %d\n", alpha);
	alpha -= 5;
	if(alpha <= 0) {
		set_next_state(STATE_TITLE_FALL);
	}
}

void title_transition_render(void)
{
	SDL_SetAlpha(introTransition, SDL_SRCALPHA, alpha);
	
	render_image(0,0,background, screen);
	render_image(0,0,introTransition,screen);
	
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}