#ifndef __utils_h
#define __utils_h

enum GAME_MODES {
    GAME_MODE_TITLE,
    GAME_MODE_DUEL,
    GAME_MODE_SHOOTING,
    GAME_MODE_RIDING,
    GAME_MODE_PRELEVEL,
    GAME_MODE_GAME_OVER,
    GAME_MODE_LEVEL_COMPLETE,
    GAME_MODE_CREDITS,
    GAME_MODE_EASTER_EGG,
};

enum DIFFICULTIES {
    EASY,
    NORMAL,
    HARD,
    EXTREME,
};

extern const UINT8 fadeBlackPalette[4];
extern const UINT8 fadeWhitePalette[4];
extern const UINT8 konamiCode[];

extern UINT8 timer;
extern UINT8 decimalTimer;
extern UINT8 secondTimer;
extern UINT8 gameMode;
extern UINT8 timerFlickerSprites;
extern UINT8 konamiCodeBuffer[11];
extern UINT8 backgroundOffset1x;
extern UINT8 backgroundOffset2x;
extern UINT8 backgroundOffset3x;
extern UINT8 backgroundOffset4x;
extern UINT16 randomSeed;
extern UINT8 buffer[1024];
extern UINT8 timeLeft;
extern UINT8 health;
extern UINT8 canPause;
extern UINT8 isPaused;
extern UINT16 currentScore;

void performant_delay(UINT8 numloops);
void fade_out_white();
void fade_in_white();
void performant_wait_pad_up();
void add_input_to_konami_code_buffer(UINT8 input);
BOOLEAN is_konami_code();
UINT8 generate_random_number_range(UINT8 min, UINT8 max);
UINT8 generate_random_number();
void hide_all_sprites();
void add_time();
void print_integer(UINT8 n, UINT8 x, UINT8 y);
void print_decimal(UINT8 n, UINT8 x, UINT8 y);
BOOLEAN update_score();
void initialize_save_data();
void print_text_bkg(UINT8 x, UINT8 y, unsigned char text[]);
void print_text_win(UINT8 x, UINT8 y, unsigned char text[]);

#endif