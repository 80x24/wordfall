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
