#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

int wTitleY = -50;
int oTitleY = -75;
int rTitleY = -100;
int dTitleY = -125;
int fTitleY = -175;
int aTitleY = -200;
int lTitleY = -225;
int l2TitleY = -250;
int wordY = 150;
int fallY = 200;

void title_fall_events()
{	
	while(SDL_PollEvent(&event)) {
		printf("Title Fall State\n");
		if(event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE) {
			set_next_state(STATE_EXIT);
		}
	}
}

void title_fall_logic()
{
	// The code below is atrocious but I don't know how to fix it.
	if(wTitleY < wordY)
		wTitleY += 5;
	if(wTitleY > wordY)
		wTitleY = wordY;
	
	if(oTitleY < wordY)
		oTitleY += 5;
	if(oTitleY > wordY)
		oTitleY = wordY;
	
	if(rTitleY < wordY)
		rTitleY += 5;
	if(rTitleY > wordY)
		rTitleY = wordY;
	
	if(dTitleY < wordY)
		dTitleY += 5;
	if(dTitleY > wordY)
		dTitleY = wordY;
	
	if(fTitleY < fallY)
		fTitleY += 5;
	if(fTitleY > fallY)
		fTitleY = fallY;
	
	if(aTitleY < fallY)
		aTitleY += 5;
	if(aTitleY > fallY)
		aTitleY = fallY;
	
	if(lTitleY < fallY)
		lTitleY += 5;
	if(lTitleY > fallY)
		lTitleY = fallY;
	
	if(l2TitleY < fallY)
		l2TitleY += 5;
	if(l2TitleY > fallY)
		l2TitleY = fallY;

	if(l2TitleY == fallY) {
		set_next_state(STATE_TITLE);
	}

}

void title_fall_render()
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
	render_image(247,l2TitleY,l2Title,screen);
	
	render_image(0,560,grass,screen);
	
	SDL_Color playColor = {0,0,0};
	play = render_font(playFont, "Play", playColor);
	render_image(148, 300, play, screen);
	options = render_font(optionsFont, "Options", playColor);
	render_image(115, 350, options, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}