#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "utils.h"
#include "text.h"
#include "sound.h"
#include "title.h"
#include "duel.h"
#include "riding.h"
#include "shooting.h"
#include "levels.h"
#include "backgrounds/titleBackground.h"
#include "sprites/mainMenuSprites.h"
#include "tiles/borderTiles.h"
#include "tiles/textTiles.h"
#include "tiles/numbers.h"
#include "maps/borderMaps.h"

const menu_option mainMenuOptions[] = {
    {MAIN_MENU_OPTION_ARCADE_MODE, &main_menu_options_text[0]},    
    {MAIN_MENU_OPTION_PRACTICE_MODE, &main_menu_options_text[1]},
    {MAIN_MENU_OPTION_SURVIVAL_MODE, &main_menu_options_text[2]},
    {MAIN_MENU_OPTION_BLANK, &main_menu_options_text[3]},
    {MAIN_MENU_OPTION_HIGH_SCORES, &main_menu_options_text[4]},
    {MAIN_MENU_OPTION_CREDITS, &main_menu_options_text[5]},
};

UINT8 horseAnimation;
BOOLEAN startPressed;
UINT8 titleFadeoutTimer;
UINT8 titleState;
UINT8 windowYPosition;
UINT8 menuCursorIndex;
UINT8 previousMenuCursorIndex;
UINT8 buttonReleased;
UINT8 nBackgroundTiles;

void load_game_mode_title() {
    canPause = FALSE;
    currentLevel = 0;
    startPressed = FALSE;
    titleFadeoutTimer = 30;
    decimalTimer = 0;
    backgroundOffset1x = 255;
    backgroundOffset2x = 255;
    backgroundOffset3x = 255;
    backgroundOffset4x = 255;
    horseAnimation = 0;
    UINT8 bank = _current_bank;  
    SWITCH_ROM_MBC1(2);
    nBackgroundTiles = Title_background_tile_count;
    gb_decompress_bkg_data(0, Title_background_tile_data);
    gb_decompress(Title_background_map_data, buffer);
    set_bkg_tiles(0, 0, Title_background_tile_map_width, Title_background_tile_map_height, buffer);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers);
    set_sprite_data(0, 25, MainMenuSprites);
    gb_decompress_win_data(Title_background_tile_count, borderTiles);
    for (UINT8 i = 0; i < 13; i++) {
        set_sprite_tile(i, i);
    }
    set_win_tiles(0, 0, 20, 10, borderMainMenuMap);
    load_main_menu_text();
    SWITCH_ROM_MBC1(bank);
    move_sprite(0, 80, 80);
    move_sprite(1, 88, 80);
    move_sprite(2, 72, 88);
    move_sprite(3, 80, 88);
    move_sprite(4, 88, 88);
    move_sprite(5, 72, 96);
    move_sprite(6, 80, 96);
    move_sprite(7, 88, 96);
    move_sprite(8, 96, 96);
    move_sprite(9, 72, 104);
    move_sprite(10, 80, 104);
    move_sprite(11, 88, 104);
    move_sprite(12, 96, 104);
    load_press_start();
    STAT_REG = 0x45;
    LYC_REG = 0x00;
    windowYPosition = 144;    
    add_LCD(interrupt_LCD_title);
    enable_interrupts();
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;    
    fade_in_white();
    set_title_song();
    gameMode = GAME_MODE_TITLE;    
    titleState = TITLE_STATE_START;
    roundsLost = 0;
    roundsWon = 0;
    buttonReleased = TRUE;
}

void game_mode_title_loop() { 
    
    if (titleState == TITLE_STATE_START) {        
        title_state_start_loop();          
    } else if (titleState == TITLE_STATE_MOVING_WINDOW) {       
        title_state_moving_window_loop();        
    } else if (titleState == TITLE_STATE_MAIN_MENU) {
        title_state_main_menu_loop();      
    } else if (titleState == TITLE_STATE_ARCADE_MENU) {
        title_state_arcade_menu_loop();  
    } else if (titleState == TITLE_STATE_PRACTICE_MENU) {
        title_state_practice_menu_loop();
    }
    
    backgroundOffset1x--;
    backgroundOffset2x -= 2;
    backgroundOffset3x -= 3;
    backgroundOffset4x -= 4;
}

void interrupt_LCD_title() {
    switch (LYC_REG)
    {
        case 0x00:
            move_bkg(0,0);
            LYC_REG = 0x40;
            break;
        case 0x40:
            move_bkg(backgroundOffset1x,0);
            LYC_REG = 0x5F;
            break;
        case 0x5F:
            move_bkg(backgroundOffset2x, 0);
            LYC_REG = 0x67;
            break;
        case 0x67:
            move_bkg(backgroundOffset3x, 0);
            LYC_REG = 0x78;
            break;
        case 0x78:
            move_bkg(backgroundOffset4x,0);
            LYC_REG = 0x00;
            break;            
    }   
}

void load_press_start() {
    set_sprite_tile(13, 19);
    set_sprite_tile(14, 20);
    set_sprite_tile(15, 21);
    set_sprite_tile(16, 22);
    set_sprite_tile(17, 22);   
    set_sprite_tile(18, 22);
    set_sprite_tile(19, 23);
    set_sprite_tile(20, 24);
    set_sprite_tile(21, 20);
    set_sprite_tile(22, 23);

    for (UINT8 i = 0; i != 5; i++) {
        move_sprite(13 + i, 40 + (i*8), 128);
        move_sprite(18 + i, 96 + (i*8), 128);
    }
}

void load_main_menu_text() {
    menuCursorIndex = 0;
    UINT8 xPosition = 4;
    UINT8 yPosition = 2;
    UINT8 ii = 0;
    for (UINT8 i = 0; i != 6; i++) {
        xPosition = 4;
        ii = 0;
        while(main_menu_options_text[i][ii] != '\0') {
            if (main_menu_options_text[i][ii] > 64 && main_menu_options_text[i][ii] < 91) {
                set_win_tile_xy(xPosition, yPosition, main_menu_options_text[i][ii] + 149);                    
            } 
            xPosition++;
            ii++;
        } 
        yPosition++;
    }
}

void load_arcade_menu_text() {
    menuCursorIndex = 0;
    previousMenuCursorIndex = 0;
    UINT8 xPosition = 4;
    UINT8 yPosition = 2;
    UINT8 ii = 0;
    for (UINT8 i = 0; i != 4; i++) {
        xPosition = 4;
        ii = 0;
        while(arcade_menu_options_text[i][ii] != '\0') {
            if (arcade_menu_options_text[i][ii] > 64 && arcade_menu_options_text[i][ii] < 91) {
                set_win_tile_xy(xPosition, yPosition, arcade_menu_options_text[i][ii] + 149);                    
            } 
            xPosition++;
            ii++;
        } 
        yPosition++;
    }
}

void load_practice_menu_text() {
    menuCursorIndex = 0;
    previousMenuCursorIndex = 0;
    UINT8 xPosition;
    UINT8 yPosition = 2;
    UINT8 ii = 0;
    for (UINT8 i = 0; i != 15; i++) {
        xPosition = 4 + 5*(i%3);
        ii = 0;
        while(level_names[i][ii] != '\0') {
            if (level_names[i][ii] > 47 && level_names[i][ii] < 58) {
                set_win_tile_xy(xPosition, yPosition, level_names[i][ii] + 197);                    
            } else if (level_names[i][ii] == '-') {
                set_win_tile_xy(xPosition, yPosition, 242);  
            }
            xPosition++;
            ii++;
        } 
        if ((i +1) % 3 == 0) { yPosition++; }
    }

}

void update_menu_cursor() {
    if (titleState == TITLE_STATE_PRACTICE_MENU) {
        set_win_tile_xy(3 + 5*(previousMenuCursorIndex%3), previousMenuCursorIndex/3 + 2, 0xD5);
        set_win_tile_xy(3 + 5*(menuCursorIndex%3), menuCursorIndex/3 + 2, 0xF0);
        
    } else {
        for (UINT8 i = 0; i != 6; i++) {
            if (i == menuCursorIndex) {
                set_win_tile_xy(3, i + 2, 0xF0);
            } else {
                set_win_tile_xy(3, i + 2, 0xD5);
            }        
        }
    }   
}

void title_state_start_loop() {
    UINT8 i = 0;
    if (decimalTimer == 0 && horseAnimation == 0) {
        set_sprite_tile(10, 13);
        set_sprite_tile(11, 14);
        set_sprite_tile(12, 15);
        scroll_sprite(9, -72, -104);
        for (i = 0; i != 13; i++) {
            scroll_sprite(i, 0, -1);
        }                
        horseAnimation = 1;
    } else if (decimalTimer == 0 && horseAnimation == 1) {
        set_sprite_tile(10, 16);
        set_sprite_tile(11, 17);
        set_sprite_tile(12, 18);;
        for (i = 0; i != 13; i++) {
            scroll_sprite(i, 0, -1);
        }
        horseAnimation = 2;            
    } else if (decimalTimer == 0 && horseAnimation == 2) {
        set_sprite_tile(10, 10);
        set_sprite_tile(11, 11);
        set_sprite_tile(12, 12);
        scroll_sprite(9, 72, 104);
        for (i = 0; i != 13; i++) {
            scroll_sprite(i, 0, 2);
        }
        horseAnimation = 0;
    }

    if (buttonReleased == TRUE) {
        if (joypad()) {
            buttonReleased = FALSE;
            add_input_to_konami_code_buffer(joypad());
        }
        if (joypad() == J_START && titleFadeoutTimer == 30) {                
            startPressed = TRUE;            
            for (i = 0; i != 10; i++) {
                move_sprite(13 + i, 0, 0);
            }
            play_reload_sound(); 
        }
    } else if (!joypad()) {
        buttonReleased = TRUE;
    }    

    if (startPressed == TRUE && titleFadeoutTimer != 0) {
        titleFadeoutTimer--;
        for (i = 0; i != 13; i++) {
            scroll_sprite(i, -4, 0);
        }
    } else if (startPressed == TRUE && titleFadeoutTimer == 0) {
        if (is_konami_code() == FALSE) {
            titleState = TITLE_STATE_MOVING_WINDOW;
            move_win(7, windowYPosition);   
            SHOW_WIN;
        } else {
            load_easter_egg();
        }        
    }
}

void title_state_moving_window_loop() {
    if (windowYPosition != 64) {
        windowYPosition -=2;
        move_win(7, windowYPosition);            
    } else {
        titleState = TITLE_STATE_MAIN_MENU;
        menuCursorIndex = 0;
        update_menu_cursor();
    }
}

void title_state_main_menu_loop() {
    if (buttonReleased == TRUE) {
        if (joypad() == J_UP) {
            if (menuCursorIndex == 4) {
                menuCursorIndex = 2;
            } else if (menuCursorIndex != 0) {
                menuCursorIndex--;
            } else {
                menuCursorIndex = 5;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (joypad() == J_DOWN || joypad() == J_SELECT) {
            if (menuCursorIndex == 2) {
                menuCursorIndex = 4;
            } else if (menuCursorIndex != 5) {
                menuCursorIndex++;
            } else {
                menuCursorIndex = 0;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (joypad() == J_A || joypad() == J_START) { 
            play_reload_sound();            
            if (menuCursorIndex == MAIN_MENU_OPTION_ARCADE_MODE) {                    
                titleState = TITLE_STATE_ARCADE_MENU;
                UINT8 bank = _current_bank;  
                SWITCH_ROM_MBC1(2);
                set_win_tiles(0, 0, 20, 10, borderMainMenuMap);
                SWITCH_ROM_MBC1(bank);
                load_arcade_menu_text();
                menuCursorIndex = 0;
                update_menu_cursor();                    
            } else if (menuCursorIndex == MAIN_MENU_OPTION_PRACTICE_MODE) {
                titleState = TITLE_STATE_PRACTICE_MENU;
                UINT8 bank = _current_bank;  
                SWITCH_ROM_MBC1(2);
                set_win_tiles(0, 0, 20, 10, borderMainMenuMap);
                SWITCH_ROM_MBC1(bank);
                load_practice_menu_text();
                menuCursorIndex = 0;
                update_menu_cursor(); 
            } else if (menuCursorIndex == MAIN_MENU_OPTION_SURVIVAL_MODE) {
                performant_delay(10);
                currentLevel = 2;
                difficulty = EXTREME;
                lives = 1;
                isSurvivalMode = TRUE;
                isPracticeMode = FALSE;                    
                loadPrelevelScreen = FALSE;
                load_level();                    
            } else if (menuCursorIndex == MAIN_MENU_OPTION_HIGH_SCORES) {
                performant_delay(10);
                load_high_scores_screen();
            } else if (menuCursorIndex == MAIN_MENU_OPTION_CREDITS) {
                performant_delay(10);
                load_credits();
            }
            buttonReleased = FALSE;                
        }
    } else if (!joypad()) {
        buttonReleased = TRUE;
    }
}

void title_state_arcade_menu_loop() {
    if (buttonReleased == TRUE) {
        if (joypad() == J_UP) {
            previousMenuCursorIndex = menuCursorIndex;
            if (menuCursorIndex != 0) {
                menuCursorIndex--;
            } else {
                menuCursorIndex = 3;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (joypad() == J_DOWN || joypad() == J_SELECT) {
            previousMenuCursorIndex = menuCursorIndex;
            if (menuCursorIndex != 3) {
                menuCursorIndex++;
            } else {
                menuCursorIndex = 0;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (joypad() == J_A || joypad() == J_START) {
            if (menuCursorIndex == EASY) {                    
                lives = 9;                    
            } else if (menuCursorIndex == NORMAL) {
                lives = 6;
            } else if (menuCursorIndex == HARD) {
                lives = 3;
            } else if (menuCursorIndex == EXTREME) {
                lives = 1;
            }
            difficulty = menuCursorIndex;
            play_reload_sound();
            performant_delay(10);            
            currentScore = 0;
            isPracticeMode = FALSE;
            isSurvivalMode = FALSE;
            loadPrelevelScreen = TRUE;
            load_level();
        } else if (joypad() == J_B) {
            titleState = TITLE_STATE_MAIN_MENU;
            UINT8 bank = _current_bank;  
            SWITCH_ROM_MBC1(2);
            set_win_tiles(0, 0, 20, 10, borderMainMenuMap);
            SWITCH_ROM_MBC1(bank);
            load_main_menu_text();
            update_menu_cursor();
            buttonReleased = FALSE;
            play_empty_sound();
        }
    } else if (!joypad()) {
        buttonReleased = TRUE;
    }
}

void title_state_practice_menu_loop() {
    if (buttonReleased == TRUE) {
        if (joypad() == J_UP || joypad() == J_LEFT) {
            previousMenuCursorIndex = menuCursorIndex;
            if (menuCursorIndex != 0) {
                menuCursorIndex--;
            } else {
                menuCursorIndex = 14;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;                
        } else if (joypad() == J_DOWN || joypad() == J_SELECT || joypad() == J_RIGHT) {
            previousMenuCursorIndex = menuCursorIndex;
            if (menuCursorIndex != 14) {
                menuCursorIndex++;
            } else {
                menuCursorIndex = 0;
            }
            update_menu_cursor();
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (joypad() == J_A || joypad() == J_START) {
            currentLevel = menuCursorIndex;
            difficulty = EASY;
            isPracticeMode = TRUE;
            isSurvivalMode = FALSE;
            loadPrelevelScreen = FALSE;
            play_reload_sound();
            performant_delay(10);
            load_level();
        } else if (joypad() == J_B) {
            titleState = TITLE_STATE_MAIN_MENU;
            UINT8 bank = _current_bank;  
            SWITCH_ROM_MBC1(2);
            set_win_tiles(0, 0, 20, 10, borderMainMenuMap);
            SWITCH_ROM_MBC1(bank);
            load_main_menu_text();   
            menuCursorIndex = 1;   
            update_menu_cursor();
            buttonReleased = FALSE;
            play_empty_sound();
        }
    } else if (!joypad()) {
        buttonReleased = TRUE;
    }
}