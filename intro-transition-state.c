#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

int alpha = 255;

void intro_transition_init(void)
{
	alpha = 255;
}

void intro_transition_events(void)
{
	//printf("fade in\n");
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
	
}

void intro_transition_logic(void)
{
	alpha -= 5;
	//printf("alpha: %d\n",alpha);
	if(alpha <= 0) {
		set_next_state(STATE_INTRO);
	}
}

void intro_transition_render(void)
{
	SDL_SetAlpha(introTransition, SDL_SRCALPHA, alpha);
	
	render_image(0,0,introBackground, screen);
	render_image(0,0,introTransition,screen);
	
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}

void intro_transition_fade_init(void)
{
	
}

void intro_transition_fade_events(void)
{
	//printf("fade out\n");
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
}

void intro_transition_fade_logic(void)
{
	//printf("transition fade alpha: %d\n",alpha);
	alpha -= 5;
	if(alpha <= 0) {
		alpha = 255;
		set_next_state(STATE_TITLE_TRANSITION);
	}
}

void intro_transition_fade_render(void)
{
	SDL_SetAlpha(introBackground, SDL_SRCALPHA, alpha);
	
	render_image(0,0,introTransition,screen);
	render_image(0,0,introBackground, screen);
	
	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}