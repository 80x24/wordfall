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

// title highlight
void title_highlight_play_events();
void title_highlight_play_logic();
void title_highlight_play_render();

void title_highlight_options_events();
void title_highlight_options_logic();
void title_highlight_options_render();

// title options menu
void title_options_events();
void title_options_logic();
void title_options_render();

#endif