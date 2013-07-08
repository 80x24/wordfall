/*
Word Fall
Copyright (C) 2013  Kyle Schreiber

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

void title_transition_init(void)
{
	if(sound == 1) {
		soundStarted = 1;
		// Set volume to max.
		Mix_Volume(-1, MIX_MAX_VOLUME);
		// Play background music.
		if(Mix_PlayMusic(backgroundMusic, -1) == -1) {
			fprintf(stderr, "Background music playing failed\n%s\n", Mix_GetError());
		}
	}
	alpha = 255;
}

void title_transition_events(void)
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

void title_transition_logic(void)
{
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
