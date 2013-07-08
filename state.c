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
#include "state.h"
#include "main.h"
#include "gamestates.h"

void set_next_state(int newState)
{
	nextState = newState;
}

void change_state(void)
{
	if(nextState != STATE_NULL) {
		
		switch(nextState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_init();
				currentState = STATE_INTRO_TRANSITION;
				break;
			case STATE_INTRO:
				intro_init();
				currentState = STATE_INTRO;
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_init();
				currentState = STATE_INTRO_TRANSITION_FADE;
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_init();
				currentState = STATE_TITLE_TRANSITION;
				break;
			case STATE_TITLE_FALL:
				title_fall_init();
				currentState = STATE_TITLE_FALL;
				break;
			case STATE_TITLE_OPTIONS:
				title_options_init();
				currentState = STATE_TITLE_OPTIONS;
				break;
			case STATE_TITLE:
				title_init();
				currentState = STATE_TITLE;
				break;
			case STATE_GAME:
				if(currentState != STATE_PAUSE) {
					game_init();
				}
				currentState = STATE_GAME;
				break;
			case STATE_GAME_TRANSITION:
				game_transition_init();
				currentState = STATE_GAME_TRANSITION;
				break;
			case STATE_PAUSE:
				pause_init();
				currentState = STATE_PAUSE;
				break;
			case STATE_EXIT:
				currentState = STATE_EXIT;
				break;
		}
		
		nextState = STATE_NULL;
	}
}
