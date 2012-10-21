#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"


SDL_Rect playRect;
SDL_Rect optionsRect;


void title_options_events()
{
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
		else if(event.type == SDL_MOUSEMOTION) {
			if((event.motion.x > playRect.x) &&
				(event.motion.x < playRect.x + playRect.w) &&
				(event.motion.y > playRect.y) &&
				(event.motion.y < playRect.y + playRect.h)) {
				//printf("title state play highlight\n");
				set_next_state(STATE_TITLE_HIGHLIGHT_PLAY);
			}
			else if((event.motion.x > optionsRect.x) &&
				(event.motion.x < optionsRect.x + optionsRect.w) &&
				(event.motion.y > optionsRect.y) &&
				(event.motion.y < optionsRect.y + optionsRect.h)) {
				//printf("title state options highlight\n");
				set_next_state(STATE_TITLE_HIGHLIGHT_OPTIONS);
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				if((event.motion.x > playRect.x) &&
					(event.motion.x < playRect.x + playRect.w) &&
					(event.motion.y > playRect.y) &&
					(event.motion.y < playRect.y + playRect.h)) {
					// set_next_state(STATE_PLAY);
					printf("Play button clicked\n");
				}
				else if((event.motion.x > optionsRect.x) &&
					(event.motion.x < optionsRect.x + optionsRect.w) &&
					(event.motion.y > optionsRect.y) &&
					(event.motion.y < optionsRect.y + optionsRect.h)) {
					// set_next_state(STATE_OPTIONS);
					printf("options button clicked\n");
				}
			}
		}
	}
}

void title_options_logic()
{
	if(l2TitleY != fallY) {
		title_fall_logic();
	}
}

void title_options_render()
{	
	render_image(0,0,background,screen);
	
	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);
	
	render_image(75,wTitleY,wTitle,screen);
	render_image(118,oTitleY,oTitle,screen);
	render_image(161,rTitleY,rTitle,screen);
	render_image(204,dTitleY,dTitle,screen);
	
	render_image(118,fTitleY,fTitle,screen);
	render_image(161,aTitleY,aTitle,screen);
	render_image(204,lTitleY,lTitle,screen);
	render_image(247,lTitleY,l2Title,screen);
	
	render_image(0,560,grass,screen);
	
	SDL_Color opitonsColor = {0,0,0};
	//SDL_Color hoverColor = {254,210,6};
	optionsSound = render_font(optionsSound, "Sound:", optionsColor);
	render_image(100, 200, optionsSound, screen);
	optionsSoundOn = render_font(optionsSoundOn, "On", optionsColor);
	render_image(165, 200, optionsSoundOn, screen);
	optionsSoundOff = render_font(optionsSoundOff, "Off", optionsColor);
	render_image(180, 200, optionsSoundOff, screen);
	
	
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