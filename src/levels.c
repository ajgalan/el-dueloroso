#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "levels.h"
#include "sound.h"
#include "utils.h"
#include "title.h"
#include "duel.h"
#include "riding.h"
#include "shooting.h"
#include "text.h"
#include "backgrounds/gameOverBackground.h"
#include "backgrounds/easterEgg.h"
#include "tiles/textTiles.h"
#include "tiles/numbers.h"
#include "tiles/iconsUI.h"
#include "tiles/borderTiles.h"
#include "sprites/duelCharactersSprites.h"
#include "maps/borderMaps.h"
#include "saveData.h"

UINT8 currentLevel = 0;
UINT8 lives;
UINT8 difficulty;
UINT8 textScreenTimer;
UINT8 previousGameMode;
UINT8 creditsTextIndex;
UINT8 creditsTextCursor;
UINT8 creditsTimer;
UINT8 creditsLine;
BOOLEAN isPracticeMode;
BOOLEAN isSurvivalMode;
BOOLEAN loadPrelevelScreen;
BOOLEAN showingHowToPlay;
BOOLEAN showingPressAnyKey;
BOOLEAN newRecord;


const level levels[] = {      
    {GAME_MODE_SHOOTING, 0},    
    {GAME_MODE_RIDING, 0},
    {GAME_MODE_DUEL, 0},
    
    {GAME_MODE_SHOOTING, 1},    
    {GAME_MODE_RIDING, 1},
    {GAME_MODE_DUEL, 1},

    {GAME_MODE_SHOOTING, 2},    
    {GAME_MODE_RIDING, 2},
    {GAME_MODE_DUEL, 2},

    {GAME_MODE_SHOOTING, 3},    
    {GAME_MODE_RIDING, 3},
    {GAME_MODE_DUEL, 3},
    
    {GAME_MODE_SHOOTING, 4},    
    {GAME_MODE_RIDING, 4},
    {GAME_MODE_DUEL, 4},
};

const shootingLevel shootingLevels[] = {
    { 100, 20, 10, 30 },
    { 100, 50, 8, 35 },
    { 150, 80, 8, 35 },
    { 200, 100, 5, 50 }, 
    { 250, 150, 5, 80 }, 
};

const duelLevel duelLevels[] = {
    { 10, 40, 10, 15, 0 },
    { 10, 40, 8, 10, 1 },
    { 10, 40, 5, 10, 2 },
    { 10, 40, 5, 7, 3 },
    { 10, 90, 4, 6, 4 },
};

const ridingLevel ridingLevels[] = {
    { 150, 8 },
    { 200, 16 },
    { 200, 20 },
    { 250, 28 },
    { 250, 36 },
};

void load_level() {   
    reset_values();
    if (currentLevel == 15) {
        loadPrelevelScreen = FALSE;
    }
    if (loadPrelevelScreen == TRUE) {
        load_prelevel_screen();
    } else {
        if (currentLevel != 15) {
            switch (levels[currentLevel].gameMode)
            {
                case GAME_MODE_TITLE:
                    load_game_mode_title();
                    break;
                case GAME_MODE_DUEL:
                    load_game_mode_duel();
                    break;
                case GAME_MODE_SHOOTING:
                    load_game_mode_shooting();
                    break;
                case GAME_MODE_RIDING:
                    load_game_mode_riding();
                    break;
                default:
                    break;
            }
        } else {    
            load_credits();
        }
    }   
}

void load_next_level() {
    currentLevel++;
    loadPrelevelScreen = TRUE;
    load_level();
}

void lose_game() {
    if (isPracticeMode == FALSE) {
        if (lives > 0) { lives--; }
        if (lives == 0) {
            load_game_over();
        } else {
            lose_live();
            loadPrelevelScreen = TRUE;            
            load_level();
        }
    } else {
        reset_values();
        load_game_mode_title();
    }    
}

void reset_values() {
    stop_music();   
    fade_out_white();    
    DISPLAY_OFF;
    disable_interrupts();
    switch (gameMode)
    {        
        case GAME_MODE_TITLE:
            remove_LCD(interrupt_LCD_title);
            break;
        case GAME_MODE_DUEL:
            remove_LCD(interrupt_LCD_duel);
            break;
        case GAME_MODE_SHOOTING:
            remove_LCD(interrupt_LCD_shooting);
            break;
        case GAME_MODE_RIDING:
            remove_LCD(interrupt_LCD_riding);
            break;        
        default:
            break;
    }    
    hide_all_sprites();   
    move_bkg(0,0);
    move_win(0,0);
    HIDE_WIN;
    SHOW_SPRITES;
    channel1Timer = 0;
    channel2Timer = 0;
    channel3Timer = 0;
    channel4Timer = 0;
    canPause = FALSE;
}

void game_over_loop() {
    if (textScreenTimer != 0 && decimalTimer == 0) {
        textScreenTimer--;
        if (textScreenTimer == 1) {
            print_text_win(1, 16, press_any_button_text);
            if (newRecord == TRUE) {
                print_text_win(4, 13, new_record_text); 
            }             
        }       
    } else if (joypad() && textScreenTimer == 0) {
        reset_values();
        load_game_mode_title();
    }
}

void load_game_over() {
    reset_values();    
    UINT8 bank = _current_bank;  
    SWITCH_ROM_MBC1(2);
    gb_decompress_bkg_data(0, GameOverBackground_tile_data);
    gb_decompress(GameOverBackground_map_data, buffer);
    set_win_tiles(0, 0, GameOverBackground_tile_map_width, GameOverBackground_tile_map_height, buffer);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers);
    gb_decompress_sprite_data(0, duelCharacters);
    SWITCH_ROM_MBC1(bank);
    for (UINT8 i = 0; i != 3; i++) {
        set_sprite_tile(i*4, i*2 + 90);
        set_sprite_tile((i*4) + 1, (i*2) + 91);
        set_sprite_tile((i*4) + 2, (i*2) + 91);
        set_sprite_tile((i*4) + 3, i*2 + 90);
        set_sprite_prop((i*4) + 2, S_FLIPX);
        set_sprite_prop((i*4) + 3, S_FLIPX);
        move_sprite(i*4, 72, 72 + (i*8));
        move_sprite(i*4 + 1, 80, 72 + (i*8));
        move_sprite(i*4 + 2, 88, 72 + (i*8));
        move_sprite(i*4 + 3, 96, 72 + (i*8));
    }
    if (isSurvivalMode == FALSE) {
        print_current_score(12); 
    } else {
        UINT8 i = 0;
        print_text_win(5, 12, rounds_text);     
        UINT8 value = roundsWon;
        UINT8 digit;
        for (UINT8 x = 0; x != 3; x++) {
            digit = value % 10;
            value = value / 10;            
            set_win_tile_xy(14 - x, 12, 245 + digit);                 
        } 
    }
    newRecord = update_score();   
    enable_interrupts();
    move_win(7,0);
    SHOW_WIN;
    DISPLAY_ON;
    fade_in_white();
    OBP0_REG = 0x90; 
    set_lose_song();
    gameMode = GAME_MODE_GAME_OVER;
    textScreenTimer = 100;
}

void game_mode_level_complete_loop() {       
    if (textScreenTimer != 0 && decimalTimer == 0) {
        textScreenTimer--;
        if (textScreenTimer == 1) {    
            print_text_win(1, 16, press_any_button_text);   
            if (newRecord == TRUE) {
                print_text_win(4, 14, new_record_text); 
            }                   
        } else if (textScreenTimer == 50) {    
            print_text_win(1, 4, bonus_text);       
            print_current_score(13);
            play_reload_sound();
        } else if (textScreenTimer == 40) {
            print_text_win(1, 6, level_text);
            UINT16 levelbonus = (100 * (currentLevel + 1));
            print_number_win(8, 7, levelbonus);
            currentScore += levelbonus;
            print_current_score(13);
            play_reload_sound();
        } else if (textScreenTimer == 30) {
            print_text_win(1, 8, time_text); 
            UINT16 timeLeftScore = timeLeft;
            if (previousGameMode == GAME_MODE_DUEL) {
                timeLeftScore = timeLeftScore * 10;
            }
            print_number_win(8, 9, timeLeftScore);            
            currentScore += timeLeftScore;            
            print_current_score(13);
            play_reload_sound();
        } else if (textScreenTimer == 20) {
            print_text_win(1, 10, difficulty_text);
            UINT16 difficultyBonus = difficulty * 50;
            print_number_win(8, 11, difficultyBonus);
            currentScore += difficultyBonus;            
            print_current_score(13);
            play_reload_sound();
            if (currentLevel == 14) {
                newRecord = update_score();
            } else {
                newRecord = FALSE;
            }
        }
    } else if (joypad() && textScreenTimer == 0) {
        gameMode = previousGameMode;
        load_next_level();
    }    
}

void load_level_complete() {    
    HIDE_SPRITES;
    backgroundOffset1x = 0;
    backgroundOffset2x = 0;
    backgroundOffset3x = 0;
    backgroundOffset4x = 0;
    textScreenTimer = 100;
    showBoom = FALSE;
    backgroundAnimation = 1;    
    canPause = FALSE;
    UINT8 blackTile = gameMode == GAME_MODE_SHOOTING? 0xD5: 0x00;
    for (UINT8 y = 0; y != 18; y++) {
        for (UINT8 x = 0; x != 32; x++) {
            set_bkg_tile_xy(x, y, blackTile);
            set_bkg_tile_xy(x, 17 - y, blackTile);            
        }
        performant_delay(4);
    }
    if (isPracticeMode == FALSE) {

        UINT8 bank =_current_bank;
        SWITCH_ROM_MBC1(2);
        gb_decompress_bkg_data(205, borderTiles);
        gb_decompress_bkg_data(213, TextTiles);
        gb_decompress_bkg_data(245, Numbers);
        set_win_tiles(0, 0, 20, 18, borderScreenMap);
        SWITCH_ROM_MBC1(bank);
        print_text_win(1, 1, level_complete_text);
        enable_interrupts();
        move_win(7, 0);
        SHOW_WIN;
        set_win_song();
        previousGameMode = gameMode;
        gameMode = GAME_MODE_LEVEL_COMPLETE;
    } else {
        reset_values();
        load_game_mode_title();
    }    
}

void print_current_score(UINT8 yPosition) {
    print_text_win(1, yPosition, score_text);
    print_number_win(8, yPosition, currentScore);
}

void print_number_win(UINT8 startingXPosition, UINT8 yPosition, UINT16 number) {
    UINT8 i = startingXPosition;
    UINT16 value = number;
    UINT8 digit;
    for (UINT8 ii = 5; ii != 0; ii--) {
        digit = value % 10;
        value = value / 10;        
        set_win_tile_xy(i + ii, yPosition, 245 + digit);       
    }
    i += 5;
    for (UINT8 ii = 0; ii != 3; ii++) { 
        set_win_tile_xy(i+1, yPosition, 245);   
        i++;
    }
}

void print_number_bkg(UINT8 startingXPosition, UINT8 yPosition, UINT16 number) {
    UINT8 i = startingXPosition;
    UINT16 value = number;
    UINT8 digit;
    for (UINT8 ii = 5; ii != 0; ii--) {
        digit = value % 10;
        value = value / 10;        
        set_bkg_tile_xy(i + ii, yPosition, 245 + digit);       
    }
    i += 5;
    for (UINT8 ii = 0; ii != 3; ii++) { 
        set_bkg_tile_xy(i+1, yPosition, 245);   
        i++;
    }
}

void load_prelevel_screen() {
    move_win(7, 0);
    for (UINT8 x = 0; x != 20; x++) {
        for (UINT8 y = 0; y != 18; y++) {
            set_win_tile_xy(x, y, 0xD5);
        }
    }
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    gb_decompress_bkg_data(205, borderTiles);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers);  
    set_bkg_tiles(0, 0, 20, 18, borderScreenMap);  
    SWITCH_ROM_MBC1(bank);  
    UINT8 i = 0;  
    UINT8 x = 0; 
    UINT8 y = 0; 
    print_text_bkg(1, 1, level_text);
    i = 0;
    while (level_names[currentLevel][i] != '\0') {
        if (level_names[currentLevel][i] > 47 && level_names[currentLevel][i] < 58) {
            set_bkg_tile_xy(14+i, 1, level_names[currentLevel][i] + 197);                    
        } else if (level_names[currentLevel][i] == '-') {
            set_bkg_tile_xy(14+i, 1, 242);  
        }
        i++;
    }
    print_text_bkg(6, 8, lives_text);  
    set_bkg_tile_xy(12, 8, lives + 245); 
    set_bkg_tile_xy(4, 13, 0xF0); 
    print_text_bkg(5, 13, start_text);
    print_text_bkg(5, 14, how_to_play_text);
    i = 0;
    switch (levels[currentLevel].gameMode)
    {
        case GAME_MODE_DUEL:        
            while (duel_texts[levels[currentLevel].index][i] != '\0') {
                if (duel_texts[levels[currentLevel].index][i] > 64 && duel_texts[levels[currentLevel].index][i] < 91) {
                    set_bkg_tile_xy(i+1, 3, duel_texts[levels[currentLevel].index][i] + 149);                    
                } 
                i++;
            }
            i = 0;
            while (how_to_play_duel_text[i] != '\0') {
                if (how_to_play_duel_text[i] > 64 && how_to_play_duel_text[i] < 91) {
                    set_win_tile_xy(x, y, how_to_play_duel_text[i] + 149);                    
                } else if (how_to_play_duel_text[i] == '-') {
                    set_win_tile_xy(x, y, 0xF2);   
                } else if (how_to_play_duel_text[i] == '\n') {
                    y++;
                    x = 255;
                }
                i++;
                x++;
            }
            break;
        case GAME_MODE_RIDING:
            print_text_bkg(1, 3, riding_mode_text);
            i = 0;
            while (how_to_play_riding_text[i] != '\0') {
                if (how_to_play_riding_text[i] > 64 && how_to_play_riding_text[i] < 91) {
                    set_win_tile_xy(x, y, how_to_play_riding_text[i] + 149);                    
                } else if (how_to_play_riding_text[i] == '-') {
                    set_win_tile_xy(x, y, 0xF2);   
                } else if (how_to_play_riding_text[i] == '\n') {
                    y++;
                    x = 255;
                }
                i++;
                x++;
            }
            break;
        case GAME_MODE_SHOOTING:
            print_text_bkg(1, 3, shooting_mode_text);
            i = 0;
            while (how_to_play_shooting_text[i] != '\0') {
                if (how_to_play_shooting_text[i] > 64 && how_to_play_shooting_text[i] < 91) {
                    set_win_tile_xy(x, y, how_to_play_shooting_text[i] + 149);                                       
                } else if (how_to_play_shooting_text[i] == '-') {
                    set_win_tile_xy(x, y, 0xF2);   
                } else if (how_to_play_shooting_text[i] == '\n') {
                    y++;
                    x = 255;
                }
                i++;    
                x++;             
            }
            break;
        default:
            break;
    }
    enable_interrupts();
    DISPLAY_ON;
    fade_in_white();
    buttonReleased = FALSE;
    showingHowToPlay = FALSE;
    gameMode = GAME_MODE_PRELEVEL;
    menuCursorIndex = 0;
}

void game_mode_prelevel_loop() {
    if (showingHowToPlay == FALSE) {
        if (buttonReleased == TRUE && (joypad() == J_UP || joypad() == J_DOWN || joypad() == J_SELECT)) {        
            if (menuCursorIndex == 0) {
                menuCursorIndex = 1;
                set_bkg_tile_xy(4, 14, 0xF0); 
                set_bkg_tile_xy(4, 13, 0xD5); 
            } else {
                menuCursorIndex = 0;
                set_bkg_tile_xy(4, 13, 0xF0);
                set_bkg_tile_xy(4, 14, 0xD5); 
            }
            play_beep_sound();
            buttonReleased = FALSE;
        } else if (buttonReleased == TRUE && (joypad() == J_A || joypad() == J_START)) {
            buttonReleased = FALSE;
            play_reload_sound();
            if (menuCursorIndex == 0) {
                loadPrelevelScreen = FALSE;
                performant_delay(10);
                load_level();
            } else if (menuCursorIndex == 1) {
                SHOW_WIN;
                showingHowToPlay = TRUE;
            }       
        }
    } else {
        if (buttonReleased == TRUE && joypad()) {
            play_reload_sound();
            HIDE_WIN;
            showingHowToPlay = FALSE;
            buttonReleased = FALSE;
        }
    }
    
    if (!joypad()) {
        buttonReleased = TRUE;
    }
}

void load_high_scores_screen() {
    reset_values();
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    gb_decompress_bkg_data(205, borderTiles);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers); 
    set_bkg_tiles(0, 0, 20, 18, borderScreenMap);    
    SWITCH_ROM_MBC1(bank);
    ENABLE_RAM_MBC1;
    print_text_bkg(4, 1, high_scores_text);
    print_text_bkg(1, 3, arcade_menu_option_easy);
    print_number_bkg(8, 4, easyScore);
    print_text_bkg(1, 6, arcade_menu_option_normal);
    print_number_bkg(8, 7, normalScore);
    print_text_bkg(1, 9, arcade_menu_option_hard);
    print_number_bkg(8, 10, hardScore);
    print_text_bkg(1, 12, arcade_menu_option_extreme);
    print_number_bkg(8, 13, extremeScore);    
    print_text_bkg(1, 15, main_menu_option_survival_mode);
    print_integer(survivalScore, 8, 16);
    DISABLE_RAM_MBC1;
    print_text_bkg(13, 16, rounds_text);
    enable_interrupts();
    DISPLAY_ON;
    fade_in_white();
    performant_wait_pad_up();
    while(!joypad()) {
        wait_vbl_done();
    }
    fade_out_white();
    load_game_mode_title();
}

void game_mode_credits_loop() {
    if (creditsTimer == 0 && showingPressAnyKey == FALSE) {        
        if (credits_text[creditsTextIndex] == '\n') {
            creditsLine++;
            creditsTextCursor = 0;
            creditsTimer = 64;
        } else {
            if (credits_text[creditsTextIndex] > 64 && credits_text[creditsTextIndex] < 91) {
                set_bkg_tile_xy(creditsTextCursor, creditsLine, credits_text[creditsTextIndex] + 149);    
            } else if (credits_text[creditsTextIndex] == '-') {
                set_bkg_tile_xy(creditsTextCursor, creditsLine, 0xF2);   
            } else if (credits_text[creditsTextIndex] > 47 && credits_text[creditsTextIndex] < 58) {
                set_bkg_tile_xy(creditsTextCursor, creditsLine, credits_text[creditsTextIndex] + 197);                    
            } else if (credits_text[creditsTextIndex] == '@') {
                set_bkg_tile_xy(creditsTextCursor, creditsLine, 0); 
            } else if (credits_text[creditsTextIndex] == '!') {
                set_bkg_tile_xy(creditsTextCursor, creditsLine, 0xF3); 
            } else if (credits_text[creditsTextIndex] == '\0') {                
                print_text_bkg(1, 16, press_any_button_text);
                showingPressAnyKey = TRUE;
            }
            creditsTextCursor++;
        }
        creditsTextIndex++; 
    } else {
        creditsTimer--;
        if (showingPressAnyKey == TRUE) {
            if (joypad()) {
                reset_values();
                load_game_mode_title();
            }
        }
    }
}

void load_credits() {
    reset_values();
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    set_bkg_data(0, 1, heartTile);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers);    
    SWITCH_ROM_MBC1(bank);
    for (UINT8 x = 0; x != 20; x++) {
        for (UINT8 y = 0; y != 18; y++) {
            set_bkg_tile_xy(x, y, 0xD5);
        }
    }
    enable_interrupts();
    DISPLAY_ON;
    fade_in_white();
    gameMode = GAME_MODE_CREDITS;
    set_riding_song();
    creditsTimer = 0;
    creditsTextCursor = 0;
    creditsTextIndex = 0;
    creditsLine = 0;
    showingPressAnyKey = FALSE;
}

void load_easter_egg() {
    reset_values();
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    gb_decompress(easterEgg_map_data, buffer);
    set_bkg_submap(0, 0, easterEgg_tile_map_width, easterEgg_tile_map_height, buffer, easterEgg_tile_map_width);
    gb_decompress_bkg_data(0 , easterEgg_tile_data);    
    SWITCH_ROM_MBC1(bank);
    enable_interrupts();
    DISPLAY_ON;
    fade_in_white();
    set_win_song();
    creditsTimer = 0;
    gameMode = GAME_MODE_EASTER_EGG;
}

void game_mode_easter_egg_loop() {
    if (creditsTimer == 255) {
        if (joypad()) {
            reset_values();
            load_game_mode_title();
        }
    } else {
        creditsTimer++;
    }    
}

void lose_live() {
    HIDE_SPRITES;   
    backgroundOffset1x = 0;
    backgroundOffset2x = 0;
    backgroundOffset3x = 0;
    backgroundOffset4x = 0;    
    showBoom = FALSE;
    backgroundAnimation = 1;    
    canPause = FALSE;
    UINT8 blackTile = gameMode == GAME_MODE_SHOOTING? 0xD5: 0x00;
    for (UINT8 y = 0; y != 18; y++) {
        for (UINT8 x = 0; x != 32; x++) {
            set_bkg_tile_xy(x, y, blackTile);
            set_bkg_tile_xy(x, 17 - y, blackTile);            
        }
        performant_delay(4);
    }
    cameraXPosition = 0;
    UINT8 bank =_current_bank;
    SWITCH_ROM_MBC1(2);
    gb_decompress_bkg_data(213, TextTiles);
    gb_decompress_bkg_data(245, Numbers); 
    SWITCH_ROM_MBC1(bank);
    print_text_bkg(6, 8, lives_text);  
    set_bkg_tile_xy(12, 8, lives + 1 + 245); 
    performant_delay(30);
    print_text_bkg(6, 8, lives_text);  
    set_bkg_tile_xy(12, 8, lives + 245); 
    play_take_damage_sound();
    performant_delay(90);
}