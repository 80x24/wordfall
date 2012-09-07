#ifndef _gamestate_h
#define _gamestate_h

// --- INTRO ---
void intro_events();
void intro_logic();
void intro_render();
int introTimeStart;

//  intro transition
void intro_transition_events();
void intro_transition_logic();
void intro_transition_render();

void intro_transition_fade_events();
void intro_transition_fade_logic();
void intro_transition_fade_render();

// --- TITLE ---
void title_events();
void title_logic();
void title_render();

// title transition
void title_transition_events();
void title_transition_logic();
void title_transition_render();

// title words falling
void title_fall_events();
void title_fall_logic();
void title_fall_render();

#endif