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
#include "game-state.h"
#include "pause-state.h"

SDL_Rect resumeRect, returnMenuRect;
static loc resumeLoc, returnLoc, pauseFontLoc;

void pause_init(void)
{
}

void pause_events(void)
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
				if((event.motion.x > resumeRect.x) &&
					(event.motion.x < resumeRect.x + resumeRect.w) &&
					(event.motion.y > resumeRect.y) &&
					(event.motion.y < resumeRect.y + resumeRect.h)) {
					set_next_state(STATE_GAME);
				}
				else if((event.motion.x > pauseRect.x) &&
					(event.motion.x < pauseRect.x + pauseRect.w) &&
					(event.motion.y > pauseRect.y) &&
					(event.motion.y < pauseRect.y + pauseRect.h)) {
					set_next_state(STATE_GAME);
				}
				else if((event.motion.x > returnMenuRect.x) &&
				(event.motion.x < returnMenuRect.x + returnMenuRect.w) &&
				(event.motion.y > returnMenuRect.y) &&
				(event.motion.y < returnMenuRect.y + returnMenuRect.h)) {
					set_next_state(STATE_TITLE_FALL);
				}
			}
		}
	}
}

void pause_logic(void)
{
}

void pause_render(void)
{
	render_image(0,0,background,screen);

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			if(lettersY[i][j] <= GRASS_Y) {
				render_image(lettersX[i][j], lettersY[i][j], letters[i][j], screen);
			}
		}
	}

	render_image(cloudPos1.x, cloudPos1.y, cloud1, screen);
	render_image(cloudPos2.x, cloudPos2.y, cloud2, screen);
	render_image(cloudPos3.x, cloudPos3.y, cloud3, screen);

	render_image(0,GRASS_Y,grass,screen);

	// Containers
	for(int i = 0; i < 7; i++) {
		if(containerLetters[i] != NULL) {
			render_image(containerX[i]+2, containerY+2, containerLetters[i], screen);
		}
		render_image(containerX[i], containerY, container[i], screen);
	}
	// Submit check
	render_image(submitX, submitY, submit, screen);

	// Pause button
	render_image(pauseX, pauseY, pause, screen);

	// Score yellow: 254,210,6
	SDL_Color scoreColor = {0,0,0};
	char finalScoreString[16];
	sprintf(finalScoreString, "SCORE: %d", finalScore);
	score = render_font(scoreFont, finalScoreString, scoreColor);

	pauseFontSurface = render_font(pauseFont, "Paused", scoreColor);
	resume = render_font(resumeFont, "Resume", scoreColor);
	returnMenu = render_font(returnMenuFont, "Main Menu", scoreColor);

	pauseFontLoc.x = (360 - pauseFontSurface->clip_rect.w)/2;
	pauseFontLoc.y = 200;
	resumeLoc.x = (360 - resume->clip_rect.w)/2;
	resumeLoc.y = pauseFontLoc.y+75;
	returnLoc.x = (360 - returnMenu->clip_rect.w)/2;
	returnLoc.y = resumeLoc.y+75;

	// May be inefficient
	pauseRect.x = pauseX;
	pauseRect.y = pauseY;
	pauseRect.w = pause->clip_rect.w;
	pauseRect.h = pause->clip_rect.h;

	resumeRect.x = resumeLoc.x;
	resumeRect.y = resumeLoc.y;
	resumeRect.w = resume->clip_rect.w;
	resumeRect.h = resume->clip_rect.h;

	returnMenuRect.x = returnLoc.x;
	returnMenuRect.y = returnLoc.y;
	returnMenuRect.w = returnMenu->clip_rect.w;
	returnMenuRect.h = returnMenu->clip_rect.h;

	
	render_image(32, ((score->clip_rect.h - pause->clip_rect.h)/2), score, screen);
	render_image(pauseFontLoc.x, pauseFontLoc.y, pauseFontSurface, screen);
	render_image(resumeLoc.x, resumeLoc.y, resume, screen);
	render_image(returnLoc.x, returnLoc.y, returnMenu, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}
