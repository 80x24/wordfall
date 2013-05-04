#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "game-state.h"

SDL_Rect resumeRect;
int resumeX,resumeY,pauseFontX,pauseFontY = 0;

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

	if(gameInit) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 26; j++) {
				if(lettersY[i][j] <= GRASS_Y) {
					render_image(lettersX[i][j], lettersY[i][j], letters[i][j], screen);
				}
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
	render_image(32, ((score->clip_rect.h - pause->clip_rect.h)/2), score, screen);

	pauseFontSurface = render_font(pauseFont, "Paused", scoreColor);
	resume = render_font(resumeFont, "Resume", scoreColor);

	pauseFontX = (360 - pauseFontSurface->clip_rect.w)/2;
	pauseFontY = 200;
	resumeX = (360 - resume->clip_rect.w)/2;
	resumeY = pauseFontY+75;

	// May be inefficient 
	resumeRect.x = resumeX;
	resumeRect.y = resumeY;
	resumeRect.w = resume->clip_rect.w;
	resumeRect.h = resume->clip_rect.h;

	pauseRect.x = pauseX;
	pauseRect.y = pauseY;
	pauseRect.w = pause->clip_rect.w;
	pauseRect.h = pause->clip_rect.h;

	render_image(pauseFontX, pauseFontY, pauseFontSurface, screen);
	render_image(resumeX, resumeY, resume, screen);

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}