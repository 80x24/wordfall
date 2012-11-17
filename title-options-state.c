#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

SDL_Rect soundOnRect;
SDL_Rect soundOffRect;
SDL_Rect optionsBackRect;

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
			// turn on highlighting
			if((event.motion.x > soundOnRect.x) &&
				(event.motion.x < soundOnRect.x + soundOnRect.w) &&
				(event.motion.y > soundOnRect.y) &&
				(event.motion.y < soundOnRect.y + soundOnRect.h)) {
				soundOnHighlight = 1;
			}
			if((event.motion.x > soundOffRect.x) &&
				(event.motion.x < soundOffRect.x + soundOffRect.w) &&
				(event.motion.y > soundOffRect.y) &&
				(event.motion.y < soundOffRect.y + soundOffRect.h)) {
				soundOffHighlight = 1;
			}
			if((event.motion.x > optionsBackRect.x) &&
				(event.motion.x < optionsBackRect.x + optionsBackRect.w) &&
				(event.motion.y > optionsBackRect.y) &&
				(event.motion.y < optionsBackRect.y + optionsBackRect.h)) {
				backHighlight = 1;
			}
			// Turn off Highlighting
			if((event.motion.x < soundOnRect.x) ||
				(event.motion.x > soundOnRect.x + soundOnRect.w) ||
				(event.motion.y < soundOnRect.y) ||
				(event.motion.y > soundOnRect.y + soundOnRect.h)) {
				soundOnHighlight = 0;
			}
			if((event.motion.x < soundOffRect.x) ||
				(event.motion.x > soundOffRect.x + soundOffRect.w) ||
				(event.motion.y < soundOffRect.y) ||
				(event.motion.y > soundOffRect.y + soundOffRect.h)) {
				soundOffHighlight = 0;
			}
			if((event.motion.x < optionsBackRect.x) ||
				(event.motion.x > optionsBackRect.x + optionsBackRect.w) ||
				(event.motion.y < optionsBackRect.y) ||
				(event.motion.y > optionsBackRect.y + optionsBackRect.h)) {
				backHighlight = 0;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				// back button to title screen
				if((event.motion.x > optionsBackRect.x) &&
					(event.motion.x < optionsBackRect.x + optionsBackRect.w) &&
					(event.motion.y > optionsBackRect.y) &&
					(event.motion.y < optionsBackRect.y + optionsBackRect.h)) {
					set_next_state(STATE_TITLE);
					//printf("back button clicked\n");
				}
				// click sound on
				else if((event.motion.x > soundOnRect.x) &&
					(event.motion.x < soundOnRect.x + soundOnRect.w) &&
					(event.motion.y > soundOnRect.y) &&
					(event.motion.y < soundOnRect.y + soundOnRect.h)) {
					printf("sound turned on\n");
				}
				// click sound off
				else if((event.motion.x > soundOffRect.x) &&
					(event.motion.x < soundOffRect.x + soundOffRect.w) &&
					(event.motion.y > soundOffRect.y) &&
					(event.motion.y < soundOffRect.y + soundOffRect.h)) {
					printf("sound turned off\n");
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
	playRectHighlight = 0;
	optionsRectHighlight = 0;
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
	
	SDL_Color optionsColor = {0,0,0};
	SDL_Color hoverColor = {254,210,6};
	optionsSound = render_font(optionsSoundFont, "Sound:", optionsColor);
	render_image(60, 275, optionsSound, screen);

	if(soundOnHighlight == 1) {
		optionsSoundOn = render_font(optionsSoundFontOn, "On", hoverColor);
		render_image(180, 275, optionsSoundOn, screen);
	}
	if(soundOnHighlight != 1) {
		optionsSoundOn = render_font(optionsSoundFontOn, "On", optionsColor);
		render_image(180, 275, optionsSoundOn, screen);
	}
	if(soundOffHighlight == 1) {
		optionsSoundOff = render_font(optionsSoundFontOff, "Off", hoverColor);
		render_image(230, 275, optionsSoundOff, screen);
	}
	if(soundOffHighlight != 1) {
		optionsSoundOff = render_font(optionsSoundFontOff, "Off", optionsColor);
		render_image(230, 275, optionsSoundOff, screen);
	}
	if(backHighlight == 1) {
		optionsBack = render_font(optionsBackFont, "Back", hoverColor);
		render_image(140, 500, optionsBack, screen);
	}
	if(backHighlight != 1) {
		optionsBack = render_font(optionsBackFont, "Back", optionsColor);
		render_image(140, 500, optionsBack, screen);
	}
	
	// Collision rects
	soundOnRect.x = 180;
	soundOnRect.y = 275;
	soundOnRect.w = optionsSoundOn->clip_rect.w;
	soundOnRect.h = optionsSoundOn->clip_rect.h;

	soundOffRect.x = 230;
	soundOffRect.y = 275;
	soundOffRect.w = optionsSoundOff->clip_rect.w;
	soundOffRect.h = optionsSoundOff->clip_rect.h;

	optionsBackRect.x = 140;
	optionsBackRect.y = 500;
	optionsBackRect.w = optionsBack->clip_rect.w;
	optionsBackRect.h = optionsBack->clip_rect.h;

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}