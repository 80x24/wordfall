#ifndef _game_state_h
#define _game_state_h

extern int timeStart;

extern int playX;
extern int playY;

extern int pauseX;
extern int pauseY;

extern int optionsX;
extern int optionsY;

extern int containerX[];
extern int containerY;

extern int submitX;
extern int submitY;

extern int gameInit;

extern int theScore;
extern int finalScore;
extern int scoreValues[26];
extern int scoreArray[7];
extern int addScore;
extern int addScoreFail;
extern int addTransition;
extern float addTransitionY;

extern SDL_Rect submitRect;
extern SDL_Rect lettersRect[4][26];
extern SDL_Rect containerRect[7];
extern SDL_Rect pauseRect;

extern int lettersY[4][26];
extern int lettersX[4][26];
//extern int letterDistribution[98];

extern int randomLetter;
// This is the first array value for lettersY[][]
extern int randomFallSpot;
extern char containerAscii[8];

void drag_letter(int letter1, int letter2);
int isword(char *word);
char *sanitize(char *word);
#endif