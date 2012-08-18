#include <stdio.h>
#include <stdlib.h>
#include "render.h"

void render_image(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	// temp rect to hold offsets
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	// I think the NULL is an SDL Rect that can be used for sprite sheets.
	
	if(SDL_BlitSurface(source, NULL, destination, &offset) != 0) {
		fprintf(stderr, "Blitting failed\n %s\n",SDL_GetError());
	}
}

SDL_Surface *render_font(TTF_Font *font, const char *text, SDL_Color color)
{
	return TTF_RenderText_Blended(font,text,color);
}

void render_music(Mix_Music *music, int loops)
{
	if(Mix_PlayMusic(music, loops) == -1) {
		fprintf(stderr, "Music failed\n %s \n", Mix_GetError());
	}
}

