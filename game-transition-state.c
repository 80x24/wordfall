#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"

int wTitleX = 75;
int oTitleX = 118;
int rTitleX = 161;
int dTitleX = 204;
int fTitleX = 118;
int aTitleX = 161;
int lTitleX = 204;
int l2TitleX = 247;
int timeStart = 0;

int playX = 148;
int playY = 300;

int optionsX = 115;
int optionsY = 350;

void game_transition_events()
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

void game_transition_logic()
{
	
	static int tmp = 1;
	if(tmp == 1) {
		timeStart = SDL_GetTicks();
		tmp -= 1;
	}
	
	if(SDL_GetTicks() - timeStart >= 1250) {
		set_next_state(STATE_GAME);
	}

	/*wTitleX -= 1;
	dTitleX += 1;
	fTitleX -= 1;
	l2TitleX += 1;*/

	wTitleY += 5;
	oTitleY += 5;
	rTitleY += 5;
	dTitleY += 5;
	fTitleY += 5;
	aTitleY += 5;
	lTitleY += 5;

	playX -= 6;
	optionsX += 6;

}

void game_transition_render()
{	
	render_image(0,0,background,screen);
	
	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);
	
	render_image(wTitleX,wTitleY,wTitle,screen);
	render_image(oTitleX,oTitleY,oTitle,screen);
	render_image(rTitleX,rTitleY,rTitle,screen);
	render_image(dTitleX,dTitleY,dTitle,screen);
	
	render_image(fTitleX,fTitleY,fTitle,screen);
	render_image(aTitleX,aTitleY,aTitle,screen);
	render_image(lTitleX,lTitleY,lTitle,screen);
	render_image(l2TitleX,lTitleY,l2Title,screen);
	
	render_image(0,560,grass,screen);

	SDL_Color playColor = {0,0,0};

	play = render_font(playFont, "Play", playColor);
	render_image(playX, playY, play, screen);

	options = render_font(optionsFont, "Options", playColor);
	render_image(optionsX, optionsY, options, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}