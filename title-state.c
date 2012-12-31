#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "title-state.h"

// word fall titles
int titleX[] = {75, 118, 161, 204, 118, 161, 204, 247};
int titleY[] = {-50, -75, -100, -125, -175, -200, -225, -250};

// highlights
int soundOnHighlight =  0;
int soundOffHighlight = 0;
int backHighlight = 0;
int playRectHighlight = 0;
int optionsRectHighlight = 0;

void title_events()
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
					set_next_state(STATE_GAME_TRANSITION);
					//printf("Play button clicked\n");
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

void title_logic()
{
	backHighlight = 0;
	if(titleY[7] != 200) {
		title_fall_logic();
	}
}

void title_render()
{	
	render_image(0,0,background,screen);
	
	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);

	for(int i = 0; i < 8; i++) {
		render_image(titleX[i], titleY[i], title[i], screen);
	}
	
	render_image(0,GRASS_X,grass,screen);
	
	SDL_Color playColor = {0,0,0};
	SDL_Color hoverColor = {254,210,6};
	if(playRectHighlight == 1) {
		play = render_font(playFont, "Play", hoverColor);
		render_image(148, 300, play, screen);
	}
	if(playRectHighlight != 1) {
		play = render_font(playFont, "Play", playColor);
		render_image(148, 300, play, screen);
	}
	if(optionsRectHighlight == 1) {
		options = render_font(optionsFont, "Options", hoverColor);
		render_image(115, 350, options, screen);
	}
	if(optionsRectHighlight != 1) {
		options = render_font(optionsFont, "Options", playColor);
		render_image(115, 350, options, screen);
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
}