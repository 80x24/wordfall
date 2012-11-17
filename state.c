#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "main.h"
#include "render.h"

void set_next_state(int newState)
{
	nextState = newState;
}

void change_state()
{
	if(nextState != STATE_NULL) {
		
		switch(nextState) {
			case STATE_INTRO_TRANSITION:
				currentState = STATE_INTRO_TRANSITION;
				break;
			case STATE_INTRO:
				currentState = STATE_INTRO;
				break;
			case STATE_INTRO_TRANSITION_FADE:
				currentState = STATE_INTRO_TRANSITION_FADE;
				break;
			case STATE_TITLE_TRANSITION:
				currentState = STATE_TITLE_TRANSITION;
				break;
			case STATE_TITLE_FALL:
				currentState = STATE_TITLE_FALL;
				break;
			case STATE_TITLE_OPTIONS:
				currentState = STATE_TITLE_OPTIONS;
				break;
			case STATE_TITLE:
				currentState = STATE_TITLE;
				break;
			case STATE_EXIT:
				currentState = STATE_EXIT;
				running = 0;
				break;
		}
		
		nextState = STATE_NULL;
	}
}