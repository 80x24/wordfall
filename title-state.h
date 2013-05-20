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

extern const int wordY, fallY;

extern SDL_Rect playRect;
extern SDL_Rect optionsRect;
extern SDL_Rect soundOnRect;
extern SDL_Rect soundOffRect;
extern SDL_Rect optionsBackRect;

extern int alpha;

#endif