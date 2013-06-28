#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "title-state.h"



// highlights
int soundOnHighlight =  0;
int soundOffHighlight = 0;
int backHighlight = 0;
int playRectHighlight = 0;
int optionsRectHighlight = 0;

SDL_Rect playRect;
SDL_Rect optionsRect;
SDL_Rect soundOnRect;
SDL_Rect soundOffRect;
SDL_Rect optionsBackRect;

void title_init(void)
{

	// Line below might be an issue.
	soundOnHighlight = 0;
	soundOffHighlight = 0;
	backHighlight = 0;
	playRectHighlight = 0;
	optionsRectHighlight = 0;
}

void title_events(void)
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

void title_logic(void)
{
	backHighlight = 0;
}

void title_render(void)
{

	// Collision rects for play and option buttons
	// This is horribly inefficient. Most of these values
	// can be pre-computed and would not have to be calculated each time.
	playRect.x = 148;
	playRect.y = 300;
	playRect.w = play->clip_rect.w;
	playRect.h = play->clip_rect.h;
	optionsRect.x = 115;
	optionsRect.y = 350;
	optionsRect.w = options->clip_rect.w;
	optionsRect.h = options->clip_rect.h;

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
		render_image((360 - play->clip_rect.w)/2, 300, play, screen); // x was 148
	}
	if(playRectHighlight != 1) {
		play = render_font(playFont, "Play", playColor);
		render_image((360 - play->clip_rect.w)/2, 300, play, screen);
	}
	if(optionsRectHighlight == 1) {
		options = render_font(optionsFont, "Options", hoverColor);
		render_image((360 - options->clip_rect.w)/2, 350, options, screen); // was 115
	}
	if(optionsRectHighlight != 1) {
		options = render_font(optionsFont, "Options", playColor);
		render_image((360 - options->clip_rect.w)/2, 350, options, screen);
	}

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}
