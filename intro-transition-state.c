/*
This file is part of Word Fall.

Word Fall is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Word Fall is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Word Fall.  If not, see <http://www.gnu.org/licenses/>.
*/

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
