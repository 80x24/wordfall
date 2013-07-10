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
