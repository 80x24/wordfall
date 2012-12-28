#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"


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

	for(int i = 0; i < 8; i++) {
		titleY[i] += 5;
	}

	playX -= 6;
	optionsX += 6;

}

void game_transition_render()
{	
	render_image(0,0,background,screen);
	
	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);
	
	for(int i = 0; i < 8; i++) {
		render_image(titleX[i], titleY[i], title[i], screen);
	}
	
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