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
int scoreValues[26] = {1,4,4,2,1,4,3,3,1,10,5,2,4,2,1,4,10,1,1,1,2,5,4,8,3,10};
int scoreArray[7] = {-1,-1,-1,-1,-1,-1,-1};
// This is the scrabble distribution for letters
int letterDistribution[] = {
0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,5,5,6,6,6,7,7,8,8,8,8,8,8,8,8,8,
9,10,11,11,11,11,12,12,13,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,16,
17,17,17,17,17,17,18,18,18,18,19,19,19,19,19,19,20,20,20,20,21,21,22,22,23,24,24,25
};
int addScore = 0;
int addScoreFail = 0;
int addTransition = 0;
float addTransitionY = 550;

int lettersY[4][26] = {{0}};
int lettersX[4][26] = {{0}};

SDL_Rect lettersRect[4][26];
SDL_Rect submitRect;
SDL_Rect containerRect[7];

int fallStart = 0;
int theScore = 0;
int finalScore = 0;

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
					printf("containerAscii: %s\n", containerAscii);
					printf("safeWord before sanitize: %s\n", safeWord);
					safeWord = sanitize(safeWord);
					printf("safeWord after sanitize: %s\n", safeWord);
					if(isword(safeWord) == 1){
						printf("Word!!\n");
						//printf("%d\n", sparta);
						// TODO: Add transition for letter disappear
						// after submit. Currently, it disappears instantly
						// Might not do at all because making the letters
						// rapidly smaller is hard to do.
						printf("scores:{");
						addScore = 1;
						for(int i = 0; i < 7; i++) {
							if(scoreArray[i] != -1) {
								theScore += scoreValues[scoreArray[i]];
							}
							containerLetters[i] = 0;
							containerAscii[i] = 32;
							printf("%d,", scoreArray[i]);
							scoreArray[i] = -1;
						}
						finalScore += theScore;
						printf("}\n");
						printf("final score: %d\n", finalScore);
					}
					else {
						printf("Not a word!\n");
						addScore = 1;
						addScoreFail = 1;
						for(int i = 0; i < 7; i++) {
							scoreArray[i] = -1;
							containerLetters[i] = 0;
							containerAscii[i] = 32;
						}
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
						scoreArray[i] = -1;
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
					scoreArray[i] = letter2;
				}
				else if((lettersX[letter1][letter2] > containerRect[i].x) &&
				(lettersX[letter1][letter2] < containerRect[i].x + containerRect[i].w) &&
				(lettersY[letter1][letter2] > containerRect[i].y) &&
				(lettersY[letter1][letter2] < (containerRect[i].y + containerRect[i].h))) {
					lettersX[letter1][letter2] = containerRect[i].x;
					lettersY[letter1][letter2] = containerRect[i].y;
					containerLetters[i] = letters[letter1][letter2];
					containerAscii[i] = letter2+97;
					scoreArray[i] = letter2;
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
		randomLetter = rand() % 98;
		//printf("randomLetter: %d\n", randomLetter);
		int randomLetterSpot = letterDistribution[randomLetter];
		//printf("randomLetterSpot: %d: %c\n", randomLetterSpot, randomLetterSpot+65);
		lettersY[randomFallSpot][randomLetterSpot]++;
		//printf("Random letter chosen from timer [%d][%d]\n", randomFallSpot, randomLetter);
		timeStart = SDL_GetTicks();
	}

	if(letterDrag) {
		drag_letter(letter1, letter2);
	}

	if(addScore) {
		static int called = 0;
		if(!called) {
			addTransition = SDL_GetTicks();
			called += 1;
		}
		if(SDL_GetTicks() - addTransition <= 250) {
			addTransitionY -= 0.25;
		}
		if(SDL_GetTicks() - addTransition >= 250) {
			addTransitionY = 550;
			called -= 1;
			addScore = 0;
			theScore = 0;
			if(addScoreFail == 1) {
				addScoreFail = 0;
			}
			addTransition = SDL_GetTicks();
		}
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

	// Score
	SDL_Color blackColor = {0,0,0};
	char finalScoreString[16];
	sprintf(finalScoreString, "Score: %d", finalScore);
	score = render_font(scoreFont, finalScoreString, blackColor);
	render_image(32, 8, score, screen);

	if(letterDrag) { 
		if(lettersY[letter1][letter2] >= GRASS_Y - lettersRect[0][0].h) {
			render_image(lettersX[letter1][letter2], lettersY[letter1][letter2], letters[letter1][letter2], screen);
		}
	}
	if(addScore) {
		if(!addScoreFail) {
			SDL_Color scoreColor = {0,0,0};
			char tmpScore[16];
			sprintf(tmpScore, "+%d", theScore);
			scorePopup = render_font(scoreFontPopup, tmpScore, scoreColor);
			render_image(310, addTransitionY, scorePopup, screen);
		}
		else {
			SDL_Color failColor = {255,0,0};
			notWord = render_font(notWordFont, "X", failColor);
			render_image(320, addTransitionY, notWord, screen);
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
	printf("word in sanitize: %s\n", word);
	// Get the location of the first space.
	char *strchrLoc = strchr(word, ' ');
	int spaceLocation = strchrLoc - word;
	printf("spaceLocation: %d\n", spaceLocation);
	// This is a performance bottleneck and
	// could be sped up if needed.
	// This loop checks if there is a space between
	// the submitted word.
	for(int i = 0; i < 26; i++) {
		char *tmp = strchr(word, i+97);
		int letterLocation = tmp - word;
		if(letterLocation > spaceLocation) {
			//printf("there was a space between the letters\n");
			// Should return an empty string which will be invalid.
			return "";
		}
	}
	char *word2 = malloc(sizeof(char)*spaceLocation);
	strncpy(word2, word, sizeof(word2));
	word2[spaceLocation] = '\0';
	printf("word2: %s\n", word2);
	return word2;
}

int isword(char *word)
{
	if(strlen(word) < 1) {
		return 0;
	}
	int isWord = 0;
	for(int i = 0; i < dictNum; i++) {
		if(strncmp(dict[i], word, strlen(word)) == 0) {
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