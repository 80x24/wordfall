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
#include <string.h>
#include "load.h"

SDL_Surface *load_image(const char *location)
{
	SDL_Surface *loadImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	
	loadImage = IMG_Load(location);
	if(loadImage != NULL) {
		optimizedImage = SDL_DisplayFormatAlpha(loadImage);
		SDL_FreeSurface(loadImage);
	}
	else {
		fprintf(stderr, "Image loading and conversion failed\n %s\n",
		IMG_GetError());
	}
	
	return optimizedImage;
}

SDL_Surface *load_image_noalpha(const char *location)
{
	SDL_Surface *loadImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	
	loadImage = IMG_Load(location);
	if(loadImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadImage);
		SDL_FreeSurface(loadImage);
	}
	else {
		fprintf(stderr, "Image loading and conversion failed\n %s\n",
				IMG_GetError());
	}
	
	return optimizedImage;
}

Mix_Music *load_music(const char *location)
{
	Mix_Music *music = NULL;
	music = Mix_LoadMUS(location);
	if(music == NULL) {
		fprintf(stderr, "Music loading failed\n %s\n", Mix_GetError());
	}
	
	return music;
}

TTF_Font *load_font(const char *location, int fontSize)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(location, fontSize);
	if(font == NULL) {
		fprintf(stderr, "Font loading failed\n %s \n", TTF_GetError());
	}
	
	return font;
}
