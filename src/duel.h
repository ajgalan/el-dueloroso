#ifndef __duel_h
#define __duel_h

enum STATES_DUEL {
    STATE_DUEL_ENTERING,
    STATE_DUEL_WAIT,
    STATE_DUEL_READY,
    STATE_DUEL_WON,
    STATE_DUEL_FOUL,
    STATE_DUEL_LOST,
    STATE_DUEL_ANIMATE_WIN,
};

extern UINT8 duelTime;
extern UINT8 readyTime;
extern UINT8 enemyFireTime;
extern UINT8 playerFireTime;
extern UINT8 duelState;
extern UINT8 skyScroll;
extern UINT8 spriteXPosition;
extern UINT8 character;
extern UINT8 characterAnimationTimer;
extern UINT8 roundsWon;
extern UINT8 roundsLost;

void load_game_mode_duel();
void interrupt_LCD_duel();
void set_state_duel_wait();
void set_state_duel_ready();
void set_state_duel_foul();
void game_mode_duel_loop() BANKED;
void generate_random_numbers() BANKED;
void load_duel_sprites() BANKED;
void add_time_duel() BANKED;
void set_state_duel_won() BANKED;
void set_state_duel_lost() BANKED;
void animate_win() BANKED;
void set_state_duel_animate_win() BANKED;
void check_rounds() BANKED;
void print_duel_text() BANKED;
void print_duel_score() BANKED;
#endif