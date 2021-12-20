#include <gb/gb.h>
#include <gbdk/gbdecompress.h>
#include <rand.h>
#include <time.h>
#include "utils.h"
#include "duel.h"
#include "levels.h"
#include "sound.h"
#include "text.h"
#include "backgrounds/duelBackground.h"
#include "sprites/duelCharactersSprites.h"
#include "tiles/numbers.h"
#include "tiles/bigTextUITiles.h"
#include "maps/bigTextUIMaps.h"

void game_mode_duel_loop() {
    if (duelState == STATE_DUEL_ENTERING) {
        if (spriteXPosition != 72) {
            if (spriteXPosition % 2 == 0) {
                for (UINT8 i = 0; i != 32; i++) {
                    scroll_sprite(i, -2, 0);
                }
            }
            if (spriteXPosition == 172) {
                scroll_sprite(30, 0, -1); 
                scroll_sprite(31, 0, -1); 
            }
            if (spriteXPosition % 4 == 0) {
                scroll_sprite(28, 0, -1);
                scroll_sprite(29, 0, -1); 
                scroll_sprite(30, 0, 1); 
                scroll_sprite(31, 0, 1); 
                play_beep_sound();
            } else if (spriteXPosition % 4 == 2) {
                scroll_sprite(28, 0, 1);
                scroll_sprite(29, 0, 1); 
                scroll_sprite(30, 0, -1); 
                scroll_sprite(31, 0, -1);
            }
        } else {
            scroll_sprite(30, 0, 1); 
            scroll_sprite(31, 0, 1); 
            set_state_duel_wait();
        }
        spriteXPosition--;
    }

    if (joypad() == J_A) {
        if (duelState == STATE_DUEL_WAIT) {
            set_state_duel_foul();
        }
        if (duelState == STATE_DUEL_READY) { 
            play_shoot_sound();                       
            set_state_duel_animate_win();
        }            
    }
    if (duelState == STATE_DUEL_WAIT && duelTime == readyTime && decimalTimer == 0) {
        set_state_duel_ready();
        set_sprite_tile(16, 16 + 18*character);
        set_sprite_tile(20, 17 + 18*character);
        print_decimal(enemyFireTime, 5, 1);
        duelTime = 0;
        decimalTimer = 0;
    }

    if (duelState == STATE_DUEL_READY && duelTime == enemyFireTime) {
        set_state_duel_lost();            
    }

    if (duelState == STATE_DUEL_ANIMATE_WIN && decimalTimer % 2== 0) {
        if (characterAnimationTimer != 0) {
            animate_win();
        } else {
            set_state_duel_won();
        }
    }
    
    if (duelState == STATE_DUEL_LOST || duelState == STATE_DUEL_FOUL) {
        performant_delay(120);   
        check_rounds();
    } else if (duelState == STATE_DUEL_WON) {
        performant_delay(60);       
        check_rounds();
    }      

    
    add_time_duel();
}

void generate_random_numbers() {
    randomSeed = clock();
    initrand(randomSeed);
    if (isSurvivalMode == FALSE) {
        readyTime = generate_random_number_range(duelLevels[levels[currentLevel].index].minReadyTime, duelLevels[levels[currentLevel].index].maxReadyTime);
        enemyFireTime = generate_random_number_range(duelLevels[levels[currentLevel].index].minEnemyFireTime, duelLevels[levels[currentLevel].index].maxEnemyFireTime);
    } else {
        readyTime = generate_random_number_range(10, 40);
        UINT8 maxEnemyFiretime = 15 - (roundsWon / 10);
        if (maxEnemyFiretime > 15 || maxEnemyFiretime < 5) {
            maxEnemyFiretime = 5;
        }
        enemyFireTime = generate_random_number_range(4, maxEnemyFiretime);
    }
    
}

void load_duel_sprites() {    
    for (UINT8 i = 0; i != 8; i++) {
        set_sprite_tile(i*4, i*2 + 18*character);
        set_sprite_tile((i*4) + 1, (i*2) + 1 + 18*character);
        set_sprite_tile((i*4) + 2, (i*2) + 1 + 18*character);
        set_sprite_tile((i*4) + 3, i*2 + 18*character);
        set_sprite_prop((i*4) + 2, S_FLIPX);
        set_sprite_prop((i*4) + 3, S_FLIPX);
        move_sprite(i*4, 172, 77 + (i*8));
        move_sprite((i*4) + 1, 180, 77 + (i*8));
        move_sprite((i*4) + 2, 188, 77 + (i*8));
        move_sprite((i*4) + 3, 196, 77 + (i*8));
    }
}

void add_time_duel() {
    if (decimalTimer == 0) {
        duelTime++;
        skyScroll++;
    }    
    if (decimalTimer == 0 && duelState == STATE_DUEL_READY) {
        playerFireTime++;  
        print_decimal(playerFireTime, 5, 0);          
    }
    if (decimalTimer % 2 == 0 && duelState == STATE_DUEL_ANIMATE_WIN) {
        characterAnimationTimer--;
    }
}

void set_state_duel_won() {
    timeLeft += enemyFireTime - playerFireTime;
    roundsWon++;
    duelState = STATE_DUEL_WON;
    for (UINT8 i = 11; i < 20; i++) {
        set_bkg_tile_xy(i, 0, 0);
        set_bkg_tile_xy(i, 1, 0);
    }    
}

void set_state_duel_lost() {
    playerFireTime++;  
    print_decimal(playerFireTime, 5, 0);  
    roundsLost++;
    duelState = STATE_DUEL_LOST;
    for (UINT8 i = 11; i < 20; i++) {
        set_bkg_tile_xy(i, 0, 0);
        set_bkg_tile_xy(i, 1, 0);
    }
    play_take_damage_sound();
    fade_out_white();
    fade_in_white();
}

void animate_win() {  
    for (UINT8 i = 0; i != 8; i++) {
        set_sprite_tile(i*4, i*2 + 90);
        set_sprite_tile((i*4) + 1, (i*2) + 91);
        set_sprite_tile((i*4) + 2, (i*2) + 91);
        set_sprite_tile((i*4) + 3, i*2 + 90);
        set_sprite_prop((i*4) + 2, S_FLIPX);
        set_sprite_prop((i*4) + 3, S_FLIPX);
        scroll_sprite(i*4, 0, 2);
        scroll_sprite((i*4) + 1, 0, 2);
        scroll_sprite((i*4) + 2, 0, 2);
        scroll_sprite((i*4) + 3, 0, 2);
    }     
}

void set_state_duel_animate_win() {
    for (UINT8 i = 0; i != 12; i++) {
        set_sprite_tile(i, i + 90);
        move_sprite(i + 24, 0, 0);
    }
    duelState = STATE_DUEL_ANIMATE_WIN;
}

void check_rounds() {
    if (isSurvivalMode == FALSE) {
        if (roundsWon == 3) {        
        hide_all_sprites();
        print_duel_score();
        performant_delay(120);
        roundsLost = 0;
        roundsWon = 0;
        load_level_complete();
        } else if (roundsLost == 3) {            
            hide_all_sprites();
            print_duel_score();
            performant_delay(120);
            roundsLost = 0;
            roundsWon = 0;
            lose_game();
        } else {
            load_level();
        }
    } else {
        if (roundsLost != 0 || roundsWon == 255) {
            lose_game();
        } else {
            load_level();
        }
    }
    
}

void print_duel_text() {
    for (UINT8 y = 0; y != 18; y++) {
        for (UINT8 x = 0; x != 32; x++) {
            set_bkg_tile_xy(x, y, 0x00);
            set_bkg_tile_xy(x, 17 - y, 0x00);            
        }
    }
    UINT8 i = 0;      

    if (isSurvivalMode == FALSE) {
        while(round_text[i] != '\0') {
            if (round_text[i] > 64 && round_text[i] < 91) {
                set_bkg_tile_xy(6+i, 4, round_text[i] + 111);                    
            }
            i++;
        }   
        set_bkg_tile_xy(6+i, 4, 245 + roundsLost + roundsWon + 1); 
        print_duel_score();
    } else {
        while(round_text[i] != '\0') {
            if (round_text[i] > 64 && round_text[i] < 91) {
                set_bkg_tile_xy(5+i, 4, round_text[i] + 111);                    
            }
            i++;
        }   
        print_integer(roundsWon + 1, 5+i, 4);
    }
}

void print_duel_score() {
    for (UINT8 y = 6; y != 13; y++) {
        for (UINT8 x = 0; x != 32; x++) {
            set_bkg_tile_xy(x, y, 0x00);       
        }
    }
    UINT8 i = 0;
    while(you_text[i] != '\0') {
        if (you_text[i] > 64 && you_text[i] < 91) {
            set_bkg_tile_xy(6+i, 7, you_text[i] + 111);                    
        } else if (you_text[i] == '-') {
            set_bkg_tile_xy(6+i, 7, 204);  
        }
        i++;
    }
    set_bkg_tile_xy(6+i, 7, 245 + roundsWon); 

    i = 0;
    while(enemy_text[i] != '\0') {
        if (enemy_text[i] > 64 && enemy_text[i] < 91) {
            set_bkg_tile_xy(4+i, 9, enemy_text[i] + 111);                    
        } else if (enemy_text[i] == '-') {
            set_bkg_tile_xy(4+i, 9, 204);  
        }
        i++;
    } 
    set_bkg_tile_xy(4+i, 9, 245 + roundsLost); 
    i = 0;
    if (roundsWon == 3) {
        while(you_win_text[i] != '\0') {
            if (you_win_text[i] > 64 && you_win_text[i] < 91) {
                set_bkg_tile_xy(6+i, 11, you_win_text[i] + 111);                    
            } else if (you_win_text[i] == '!') {
                set_bkg_tile_xy(6+i, 11, 205);  
            }
            i++;
        } 
    } else if (roundsLost == 3) {
        while(you_lose_text[i] != '\0') {
            if (you_lose_text[i] > 64 && you_lose_text[i] < 91) {
                set_bkg_tile_xy(5+i, 11, you_lose_text[i] + 111);                    
            } else if (you_lose_text[i] == '!') {
                set_bkg_tile_xy(5+i, 11, 205);  
            }
            i++;
        } 
    }
}

