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
#include "title-state.h"
#include "game-state.h"

int timeStart = 0;

int playX = 148;
int playY = 300;

int pauseX = 5;
int pauseY = -25;

int optionsX = 115;
int optionsY = 350;

int containerX[7] = {0+2, 45+2, 90+2, 135+2, 180+2, 225+2, 270+2};
int containerY = 685;

int submitX = 320;
int submitY = 685;

void game_transition_init(void)
{
	timeStart = 0;
	playX = 148;
	playY = 300;
	pauseX = 5;
	pauseY = -25;
	optionsX = 115;
	optionsY = 350;
	for(int i = 0; i < 7; i++) {
		if(i == 0) {
			containerX[i] = 2;
		}
		else {
			containerX[i] = containerX[i-1] + 45;
		}
	}
	containerY = 685;
	submitX = 320;
	submitY = 685;
	timeStart = SDL_GetTicks();
}


void game_transition_events(void)
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

void game_transition_logic(void)
{	
	if(SDL_GetTicks() - timeStart >= 1250) {
		set_next_state(STATE_GAME);
	}

	for(int i = 0; i < 8; i++) {
		titleY[i] += 5;
	}

	playX -= 6;
	optionsX += 6;
	if(containerY > 580) {
		containerY -= 5;
	}
	else if(containerY <= 580) {
		containerY = 580;
	}
	if(submitY > 590) {
		submitY -= 5;
	}
	else if(submitY <= 590) {
		submitY = 590;
	}
	if(pauseY < 5) {
		pauseY += 5;
	}
	else if(pauseY >= 5) {
		pauseY = 5;
	}

}

void game_transition_render(void)
{	
	render_image(0,0,background,screen);
	
	render_image(cloudPos1.x, cloudPos1.y, cloud1, screen);
	render_image(cloudPos2.x, cloudPos2.y, cloud2, screen);
	render_image(cloudPos3.x, cloudPos3.y, cloud3, screen);
	
	// Word Fall Title fly down
	for(int i = 0; i < 8; i++) {
		render_image(titleX[i], titleY[i], title[i], screen);
	}
	
	render_image(0,GRASS_Y,grass,screen);

	// Containers Fly up
	for(int i = 0; i < 7; i++) {
		render_image(containerX[i], containerY, container[i], screen);
	}

	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	//render_image(pauseX, pauseY, pause, screen);

	SDL_Color playColor = {0,0,0};

	// Transition for Play and Options to float away.
	play = render_font(playFont, "Play", playColor);
	render_image(playX, playY, play, screen);

	options = render_font(optionsFont, "Options", playColor);
	render_image(optionsX, optionsY, options, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}
