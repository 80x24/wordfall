#ifndef _gamestate_h
#define _gamestate_h

// --- INTRO ---
void intro_init(void);
void intro_events(void);
void intro_logic(void);
void intro_render(void);

//  intro transition
void intro_transition_init(void);
void intro_transition_events(void);
void intro_transition_logic(void);
void intro_transition_render(void);

void intro_transition_fade_init(void);
void intro_transition_fade_events(void);
void intro_transition_fade_logic(void);
void intro_transition_fade_render(void);

// --- TITLE ---
void title_init(void);
void title_events(void);
void title_logic(void);
void title_render(void);

// title transition
void title_transition_init(void);
void title_transition_events(void);
void title_transition_logic(void);
void title_transition_render(void);

// title words falling
void title_fall_init(void);
void title_fall_events(void);
void title_fall_logic(void);
void title_fall_render(void);

// title options menu
void title_options_init(void);
void title_options_events(void);
void title_options_logic(void);
void title_options_render(void);

// --- Game ---
void game_init(void);
void game_events(void);
void game_logic(void);
void game_render(void);

void game_transition_init(void);
void game_transition_events(void);
void game_transition_logic(void);
void game_transition_render(void);

void pause_init(void);
void pause_events(void);
void pause_logic(void);
void pause_render(void);

#endif
