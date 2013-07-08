/*
Word Fall
Copyright (C) 2013  Kyle Schreiber

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "render.h"

void render_image(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	// temp rect to hold offsets
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
		
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

