/*
This file is part of Word Fall.

Word Fall is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Word Fall is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Word Fall.  If not, see <http://www.gnu.org/licenses/>.
*/

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
void sanitize(char *word);
char *strdup(const char *s);
#endif
