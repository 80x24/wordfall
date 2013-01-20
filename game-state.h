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

extern SDL_Rect submitRect;
extern SDL_Rect lettersRect[26];

extern int lettersY[26];
extern int lettersX[26];

extern int fallStart;
extern int randomLetter;
extern int randomXPos;

void drag_letter(int letter);
/*
--- Note on the Submit Container ---
When the user drops the letter into a container, I am going to have to
check what letter it was based on the array values of the letters variable.
After I check what letter it is, I will store a value of lettersAscii
into the word array. This will give me up to 7 ascii values in a row
forming a string that I will be able to send to the submit button. 
*/
extern char lettersAscii[26];
extern char word[7];

#endif