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
#include "title-state.h"

const int wordY = 165;
const int fallY = 215;
int playButtonY = 700;
int optionsButtonY = 750;
unsigned int buttonsFall = 1;
// word fall titles
int titleX[] = {75, 118, 161, 204, 118, 161, 204, 247};
int titleY[] = {-50, -75, -100, -125, -175, -200, -225, -250};

void title_fall_init(void)
{
	playButtonY = 700;
	optionsButtonY = 750;
	buttonsFall = 1;
	for(int i = 0; i < 8; i++) {
		if(i == 0) {
			titleY[i] = -50;
		}
		else {
			titleY[i] = (titleY[i-1] - 25);
		}
	}
	for(int i = 0; i < 4; i++) {
		if(i == 0) {
			titleX[i] = 75;
		}
		else {
			titleX[i] = titleX[i - 1] + 43;
		}
	}
	for(int i = 4; i < 8; i++) {
		if(i == 4) {
			titleX[i] = 118;
		}
		else {
			titleX[i] = titleX[i - 1] + 43;
		}
	}
}

void title_fall_events(void)
{	
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
		else if(event.type == SDL_MOUSEMOTION) {
			// turn highlighting on
			if((event.motion.x > playRect.x) &&
				(event.motion.x < playRect.x + playRect.w) &&
				(event.motion.y > playRect.y) &&
				(event.motion.y < playRect.y + playRect.h)) {
				playRectHighlight = 1;
			}
			else if((event.motion.x > optionsRect.x) &&
				(event.motion.x < optionsRect.x + optionsRect.w) &&
				(event.motion.y > optionsRect.y) &&
				(event.motion.y < optionsRect.y + optionsRect.h)) {
				optionsRectHighlight = 1;
			}
			// turn off highlighting
			if((event.motion.x < playRect.x) ||
				(event.motion.x > playRect.x + playRect.w) ||
				(event.motion.y < playRect.y) ||
				(event.motion.y > playRect.y + playRect.h)) {
				playRectHighlight = 0;
			}
			if((event.motion.x < optionsRect.x) ||
				(event.motion.x > optionsRect.x + optionsRect.w) ||
				(event.motion.y < optionsRect.y) ||
				(event.motion.y > optionsRect.y + optionsRect.h)) {
				optionsRectHighlight = 0;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				if((event.motion.x > playRect.x) &&
					(event.motion.x < playRect.x + playRect.w) &&
					(event.motion.y > playRect.y) &&
					(event.motion.y < playRect.y + playRect.h)) {
					//set_next_state(STATE_GAME_TRANSITION);
				}
				else if((event.motion.x > optionsRect.x) &&
					(event.motion.x < optionsRect.x + optionsRect.w) &&
					(event.motion.y > optionsRect.y) &&
					(event.motion.y < optionsRect.y + optionsRect.h)) {
					set_next_state(STATE_TITLE_OPTIONS);
					//printf("options button clicked\n");
				}
			}
		}
	}
}

void title_fall_logic(void)
{
	for(int i = 0; i < 4; i++) {
		titleY[i] += 5;
		if(titleY[i] > wordY) {
			titleY[i] = wordY;
		}
	}
	for(int i = 4; i < 8; i++) {
		titleY[i] += 5;
		if(titleY[i] > fallY) {
			titleY[i] = fallY;
		}
	}
	if(titleY[7] == fallY) {
		set_next_state(STATE_TITLE);
	}

	if(playButtonY <= 300 || optionsButtonY <= 350) {
		playButtonY = 300;
		optionsButtonY = 350;
		buttonsFall = 0;
	}

	if(buttonsFall) {
		playButtonY -= 8;
		optionsButtonY -= 8;
	}
}

void title_fall_render(void)
{	
	render_image(0,0,background,screen);
	
	render_image(cloudPos1.x, cloudPos1.y, cloud1, screen);
	render_image(cloudPos2.x, cloudPos2.y, cloud2, screen);
	render_image(cloudPos3.x, cloudPos3.y, cloud3, screen);
	
	for(int i = 0; i < 8; i++) {
		render_image(titleX[i], titleY[i], title[i], screen);
	}
	
	render_image(0,GRASS_Y,grass,screen);
	
	SDL_Color playColor = {0,0,0};
	SDL_Color hoverColor = {254,210,6};
	if(playRectHighlight == 1) {
		play = render_font(playFont, "Play", hoverColor);
		render_image((360 - play->clip_rect.w)/2, playButtonY, play, screen);
	}
	if(playRectHighlight != 1) {
		play = render_font(playFont, "Play", playColor);
		render_image((360 - play->clip_rect.w)/2, playButtonY, play, screen);
	}
	if(optionsRectHighlight == 1) {
		options = render_font(optionsFont, "Options", hoverColor);
		render_image((360 - options->clip_rect.w)/2, optionsButtonY, options, screen);
	}
	if(optionsRectHighlight != 1) {
		options = render_font(optionsFont, "Options", playColor);
		render_image((360 - options->clip_rect.w)/2, optionsButtonY, options, screen);
	}

	// Collision rects for play and option buttons
	playRect.x = 148;
	playRect.y = 300;
	playRect.w = play->clip_rect.w;
	playRect.h = play->clip_rect.h;
	optionsRect.x = 115;
	optionsRect.y = 350;
	optionsRect.w = options->clip_rect.w;
	optionsRect.h = options->clip_rect.h;

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}

	SDL_FreeSurface(play);
	play = NULL;
	SDL_FreeSurface(options);
	options = NULL;
}
