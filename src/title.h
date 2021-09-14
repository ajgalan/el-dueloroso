#ifndef __title_h
#define __title_h

enum TITLE_STATES {
    TITLE_STATE_START,
    TITLE_STATE_MOVING_WINDOW,
    TITLE_STATE_MAIN_MENU,
    TITLE_STATE_ARCADE_MENU,
    TITLE_STATE_PRACTICE_MENU,
};

enum MAIN_MENU_OPTIONS {
    MAIN_MENU_OPTION_ARCADE_MODE,
    MAIN_MENU_OPTION_PRACTICE_MODE,
    MAIN_MENU_OPTION_SURVIVAL_MODE,
    MAIN_MENU_OPTION_BLANK,
    MAIN_MENU_OPTION_HIGH_SCORES,
    MAIN_MENU_OPTION_CREDITS,
};

typedef struct menu_option
{
  UINT8 option;
} menu_option;

extern const menu_option mainMenuOptions[];
extern UINT8 horseAnimation;
extern BOOLEAN startPressed;
extern UINT8 titleFadeoutTimer;
extern UINT8 titleState;
extern UINT8 windowYPosition;
extern UINT8 menuCursorIndex;
extern UINT8 previousMenuCursorIndex;
extern UINT8 buttonReleased;
extern UINT8 nBackgroundTiles;

void load_game_mode_title();
void game_mode_title_loop();
void interrupt_LCD_title();
void load_press_start();
void load_main_menu_text();
void update_menu_cursor();
void load_arcade_menu_text();
void load_practice_menu_text();
void title_state_start_loop();
void title_state_moving_window_loop();
void title_state_main_menu_loop();
void title_state_arcade_menu_loop();
void title_state_practice_menu_loop();

#endif