#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include <rand.h>
#include <time.h>
#include "utils.h"
#include "sound.h"
#include "riding.h"
#include "levels.h"
#include "backgrounds/ridingBackground.h"
#include "sprites/ridingSprites.h"
#include "sprites/shootingSprites.h"
#include "tiles/numbers.h"
#include "tiles/iconsUI.h"
#include "tiles/pausedUITiles.h"
#include "maps/pausedUIMap.h"

UINT8 cameraXPosition;
UINT8 horseXPosition;
UINT8 horseYPosition;
UINT8 carriageXPosition;
UINT8 carriageYPosition;
UINT8 barrelXPosition;
UINT8 barrelYPosition;
UINT8 backgroundAnimation;
UINT8 carriageXPositionTarget;
UINT8 carriageState;
UINT8 carriageTimer;
UINT8 canPlayerBeHurted;
UINT8 enemyHealth;
UINT8 crosshairXPositionRiding;
INT8 crosshairXSpeed;
UINT8 isAiming;
INT8 xSpeedBarrel;
UINT8 isAButtonReleased;
UINT8 enemyRecoveryCooldown;

const UINT8 carriageXPositions[5] = { 76, 100, 124, 148, 172 };
const UINT8 barrelYLimit = 180;

void load_game_mode_riding() {
    randomSeed = clock();
    initrand(randomSeed);
    canPause = TRUE;
    carriageXPosition = 124;
    carriageYPosition = 72;
    cameraXPosition = 48;
    barrelXPosition = 180;
    barrelYPosition = 175;
    horseXPosition = 124;
    horseYPosition = 136;
    carriageXPositionTarget = generate_random_number() % 5;
    carriageTimer = 0;
    canPlayerBeHurted = TRUE;
    if (difficulty == EASY) {
        health = 6;
    } else if (difficulty == NORMAL) {
        health = 5;
    } else if (difficulty == HARD) {
        health = 3;
    } else if (difficulty == EXTREME) {
        health = 1;
    }
    UINT8 bank = _current_bank;  
    SWITCH_ROM_MBC1(2);
    gb_decompress_bkg_data(0, RidingBackground_tile_data);
    gb_decompress(RidingBackground_map_data, buffer);
    set_bkg_tiles(0, 0, RidingBackground_tile_map_width,RidingBackground_tile_map_height, buffer);
    set_bkg_data(RidingBackground_tile_count, 1, heartTile);
    set_bkg_data(RidingBackground_tile_count +1, 4, enemyHealthTiles); 
    for (UINT8 i = 0; i != health; i++) {
        set_bkg_tile_xy(19 - i, 1, RidingBackground_tile_count);
    }
    gb_decompress_bkg_data(245, Numbers);
    gb_decompress_sprite_data(0, RidingSprites);   
    gb_decompress_win_data(220, pausedUITiles);
    gb_decompress(pausedUIMap, buffer);
    set_win_tiles(0, 0, 20, 18, buffer);
    timeLeft = ridingLevels[levels[currentLevel].index].timeLeft;
    print_integer(timeLeft--, 16, 0);
    load_riding_mode_sprites();
    SWITCH_ROM_MBC1(bank);
    move_horse_sprites(76, horseYPosition);  
    add_LCD(interrupt_LCD_riding);
    enable_interrupts();
    move_carriage_sprites(carriageXPosition - cameraXPosition);
    carriageState = STATE_CARRIAGE_MOVING;
    carriageTimer = generate_random_number();
    enemyHealth = ridingLevels[levels[currentLevel].index].enemyHealth;
    isAiming = FALSE;
    update_enemy_health();
    DISPLAY_ON;
    fade_in_white();
    set_riding_song();
    gameMode = GAME_MODE_RIDING;        
}

void interrupt_LCD_riding() {
    switch (LYC_REG)
    {
        case 0x00:
            move_bkg(0, 0);
            LYC_REG = 0x10;
            break;
        case 0x10:
            move_bkg(cameraXPosition, 0);
            LYC_REG = 0x38;
            break;
        case 0x38:            
            if (backgroundAnimation == 0) {
                move_bkg(cameraXPosition, 88);                
            } else {
                move_bkg(cameraXPosition, 0);
            }
            LYC_REG = 0x00;
            break;
    }
}



