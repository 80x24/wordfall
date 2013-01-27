#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestates.h"
#include "state.h"
#include "render.h"
#include "main.h"
#include "game-state.h"

int gameInit = 0;
int letterDrag = 0;
int letter1 = 0;
int letter2 = 0;
int randomLetter = 0;
int randomFallSpot = 0;
char containerAscii[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};

int lettersY[4][26] = {{0}};
int lettersX[4][26] = {{0}};

SDL_Rect lettersRect[4][26];
SDL_Rect submitRect;
SDL_Rect containerRect[7];

int fallStart = 0;

void game_events(void)
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
				if((event.motion.x > submitRect.x) &&
					(event.motion.x < submitRect.x + submitRect.w) &&
					(event.motion.y > submitRect.y) &&
					(event.motion.y < submitRect.y + submitRect.h)) {
					char *safeWord = containerAscii;
					safeWord = sanitize(safeWord);
					if(isword(safeWord) == 1){
						printf("Word!!\n");
					}
					else {
						printf("Not a word!\n");
					}
				}
				for(int i = 0; i < 4; i++) {
					for(int j = 0; j < 26; j++) {
						if((event.motion.x > lettersRect[i][j].x) &&
							(event.motion.x < lettersRect[i][j].x + lettersRect[i][j].w) &&
							(event.motion.y > lettersRect[i][j].y) &&
							(event.motion.y < lettersRect[i][j].y + lettersRect[i][j].h)) {
							letterDrag = 1;
							letter1 = i;
							letter2 = j;
						}
					}
				}
			}
			if(event.button.button == SDL_BUTTON_RIGHT) {
				for(int i = 0; i < 7; i++) {
					if((event.motion.x > containerRect[i].x) &&
					(event.motion.x < containerRect[i].x + containerRect[i].w) &&
					(event.motion.y > containerRect[i].y) &&
					(event.motion.y < containerRect[i].y + containerRect[i].h)) {
						containerLetters[i] = 0;
						containerAscii[i] = 32;
					}
				}
			}
		}
		else if(event.type == SDL_MOUSEBUTTONUP) {
			for(int i = 0; i < 7; i++) {
				if((lettersX[letter1][letter2] > containerRect[i].x) &&
				(lettersX[letter1][letter2] < containerRect[i].x + containerRect[i].w) &&
				(lettersY[letter1][letter2]+lettersRect[0][0].h > containerRect[i].y) &&
				(lettersY[letter1][letter2]+lettersRect[0][0].h < containerRect[i].y + containerRect[i].h)) {
					lettersX[letter1][letter2] = containerRect[i].x;
					lettersY[letter1][letter2] = containerRect[i].y;
					containerLetters[i] = letters[letter1][letter2];
					containerAscii[i] = letter2+97;
				}
				else if((lettersX[letter1][letter2] > containerRect[i].x) &&
				(lettersX[letter1][letter2] < containerRect[i].x + containerRect[i].w) &&
				(lettersY[letter1][letter2] > containerRect[i].y) &&
				(lettersY[letter1][letter2] < (containerRect[i].y + containerRect[i].h))) {
					lettersX[letter1][letter2] = containerRect[i].x;
					lettersY[letter1][letter2] = containerRect[i].y;
					containerLetters[i] = letters[letter1][letter2];
					containerAscii[i] = letter2+97;
				}
			}
			letterDrag = 0;
		}
	}
}

void game_logic(void)
{
	if(!gameInit) {
		timeStart = SDL_GetTicks();
		// I'm currently using this for one time
		// initialization which is bad. 
		submitRect.x = submitX;
		submitRect.y = submitY;
		submitRect.w = submit->clip_rect.w;
		submitRect.h = submit->clip_rect.h;
		for(int i = 0; i < 7; i++) {
			containerRect[i].x = containerX[i];
			containerRect[i].y = containerY;
			containerRect[i].w = container[i]->clip_rect.w;
			containerRect[i].h = container[i]->clip_rect.h;
		}

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 26; j++) {
				lettersX[i][j] = (i*75)+15;
				lettersY[i][j] = 45;
				lettersRect[i][j].x = lettersX[i][j];
				lettersRect[i][j].y = lettersY[i][j];
				lettersRect[i][j].w = letters[i][j]->clip_rect.w;
				lettersRect[i][j].h = letters[i][j]->clip_rect.h;
			}
		}
		/*randomFallSpot = rand() % 4;
		randomLetter = rand() % 26;
		lettersY[randomFallSpot][randomLetter]++;
		printf("Random init letter is [%d][%d]\n", randomFallSpot, randomLetter);*/
		gameInit += 1;
	}

	// This is going to be a problem if it randomly picks a letter that
	// is already on the screen, but I will deal with that later.
	// Basically if it picks a letter that is already on the screen all it
	// is going to do is add one to the letter instead of introducing another
	// letter. Preliminary testing is showing that this isn't going to be
	// a problem, but this could definitely be improved with some sort of list
	// that is storing the current letters.
	if(SDL_GetTicks() - timeStart >= 1000) {
		randomFallSpot = rand() % 4;
		randomLetter = rand() % 26;
		lettersY[randomFallSpot][randomLetter]++;
		//printf("Random letter chosen from timer [%d][%d]\n", randomFallSpot, randomLetter);
		timeStart = SDL_GetTicks();
	}

	if(letterDrag) {
		drag_letter(letter1, letter2);
	}

	// This for loop within the main loop might be bad.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 26; j++) {
			lettersRect[i][j].x = lettersX[i][j];
			lettersRect[i][j].y = lettersY[i][j];
			if(lettersY[i][j] != 45) {
				lettersY[i][j]++;
			}
			if((lettersY[i][j] >= (GRASS_Y+lettersRect[i][j].h+20)) && letters[i][j] != letters[letter1][letter2]) {
				lettersY[i][j] = 45;
			}
		}
	}
	/*for(int i = 0; i < 7; i++) {
		printf("%c", *(containerAscii + i));
	}*/
}

void game_render(void)
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

	render_image(-5,-5,cloud1,screen);
	render_image(215,-5,cloud3,screen);
	render_image(105,5,cloud2,screen);

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
	
	if(letterDrag) { 
		if(lettersY[letter1][letter2] >= GRASS_Y - lettersRect[0][0].h) {
			render_image(lettersX[letter1][letter2], lettersY[letter1][letter2], letters[letter1][letter2], screen);
		}
	}

	if(SDL_Flip(screen) != 0) {
		fprintf(stderr, "screen update failed\n");
	}
}

void drag_letter(int letter1, int letter2)
{
	// There are serious issues with this code right now
	// but it is good enough for now. For the majority of the
	// time the user isn't going to be dragging the letter
	// off of the screen.
	if(event.motion.x >= 360 - lettersRect[0][0].w) {
		event.motion.x = 360 - lettersRect[0][0].w;
	}
	
	if(event.motion.y >= 640 - lettersRect[0][0].h) {
		event.motion.y = 640 - lettersRect[0][0].h;
	}
	lettersX[letter1][letter2] = event.motion.x;
	lettersY[letter1][letter2] = event.motion.y;

	lettersRect[letter1][letter2].x = event.motion.x;
	lettersRect[letter1][letter2].y = event.motion.y;
}

char *sanitize(char *word)
{
	char *newWord = 0;
	int i = 0;
	int numSpaces = 0;
	for(i = 6; i >= 0; i--) {
		if(isspace(word[i])) {
			numSpaces++;
		}
	}
	unsigned long size = strlen(word) - numSpaces;
	newWord = malloc(sizeof(char)*size);
	strncpy(newWord, word, strlen(newWord));
	newWord[size] = '\0';
	word = newWord;
	free(newWord);
	newWord = 0;
	return word;
}

int isword(char *word)
{
	int isWord = 0;
	for(int i = 0; i < dictNum; i++) {
		if(strcmp(dict[i], word) == 0) {
			isWord = 1;
			break;
		}
	}
	if(isWord == 1) {
		return 1;
	}
	else {
		return 0;
	}
}