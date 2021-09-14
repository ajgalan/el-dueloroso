#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include <rand.h>
#include "utils.h"
#include "duel.h"
#include "levels.h"
#include "sound.h"
#include "backgrounds/duelBackground.h"
#include "sprites/duelCharactersSprites.h"
#include "tiles/numbers.h"
#include "tiles/textTiles.h"
#include "tiles/bigTextUITiles.h"
#include "maps/bigTextUIMaps.h"

UINT8 duelTime;
UINT8 readyTime;
UINT8 enemyFireTime;
UINT8 playerFireTime;
UINT8 duelState;
UINT8 skyScroll;
UINT8 spriteXPosition;
UINT8 character;
UINT8 characterAnimationTimer;
UINT8 roundsWon = 0;
UINT8 roundsLost = 0;

void load_game_mode_duel() {
    readyTime = 0;
    enemyFireTime = 0;
    playerFireTime = 0;
    skyScroll = 0;
    duelTime = 0;
    decimalTimer = 0;
    if (isSurvivalMode == FALSE) {
        character = duelLevels[levels[currentLevel].index].character;
    } else {
        character = roundsWon % 5;
    }    
    characterAnimationTimer = 20;
    UINT8 bank = _current_bank;  
    SWITCH_ROM_MBC1(2);
    set_bkg_data(0, DuelBackground_tile_count, DuelBackground_tile_data);
    gb_decompress_bkg_data(175, TextTiles);
    gb_decompress_bkg_data(207, bigTextUITiles);
    gb_decompress_bkg_data(245, Numbers);        
    gb_decompress_sprite_data(0, duelCharacters);      
    load_duel_sprites();
    print_duel_text();
    enable_interrupts();    
    DISPLAY_ON; 
    fade_in_white();
    performant_delay(120);
    fade_out_white();
    DISPLAY_OFF;
    disable_interrupts();
    gb_decompress(DuelBackground_map_data, buffer);
    set_bkg_tiles(0, 0, DuelBackground_tile_map_width, DuelBackground_tile_map_height, buffer);  
    SWITCH_ROM_MBC1(bank);
    generate_random_numbers();    
    add_LCD(interrupt_LCD_duel);
    enable_interrupts();    
    DISPLAY_ON;    
    fade_in_white();
    OBP0_REG = 0xD0;
    gameMode = GAME_MODE_DUEL;   
    duelState = STATE_DUEL_ENTERING; 
    spriteXPosition = 172;
    if ((roundsWon + roundsLost) == 0) { timeLeft = 0; }
}

void interrupt_LCD_duel() {
    switch (LYC_REG)
    {
        case 0x00:
            move_bkg(0, 0);
            LYC_REG = 0x10;
            break;
        case 0x10:
            move_bkg(skyScroll, 0);
            LYC_REG = 0x27;
            break;
        case 0x27:
            move_bkg(0, 0);
            LYC_REG = 0x00;
            break;        
    }
}

void set_state_duel_wait() {
    duelTime = 0;
    decimalTimer = 0;
    duelState = STATE_DUEL_WAIT;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    set_bkg_tiles(12, 0, 8, 2, wait_map);
    SWITCH_ROM_MBC1(bank);
}

void set_state_duel_ready() {
    duelState = STATE_DUEL_READY;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    set_bkg_tiles(11, 0, 9, 2, fire_map);
    SWITCH_ROM_MBC1(bank);    
    play_reload_sound(); 
}

void set_state_duel_foul() {
    duelState = STATE_DUEL_FOUL;
    roundsLost++;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(2);
    set_bkg_tiles(11, 0, 9, 2, foul_map);
    SWITCH_ROM_MBC1(bank); 
    play_take_damage_sound();
}

