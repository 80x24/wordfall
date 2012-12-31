#ifndef _title_state_h
#define _title_state_h

// Word Fall Logo
extern int titleX[];
extern int titleY[];

extern int soundOnHighlight;
extern int soundOffHighlight;
extern int backHighlight;
extern int playRectHighlight;
extern int optionsRectHighlight;

SDL_Rect playRect;
SDL_Rect optionsRect;
SDL_Rect soundOnRect;
SDL_Rect soundOffRect;
SDL_Rect optionsBackRect;

#endif