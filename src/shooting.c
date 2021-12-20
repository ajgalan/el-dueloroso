#include <gbdk/platform.h>
#include <gbdk/gbdecompress.h>
#include <rand.h>
#include <time.h>
#include "utils.h"
#include "sound.h"
#include "levels.h"
#include "shooting.h"
#include "backgrounds/shootingBackground.h"
#include "sprites/shootingSprites.h"
#include "tiles/numbers.h"
#include "tiles/iconsUI.h"
#include "tiles/pausedUITiles.h"
#include "maps/pausedUIMap.h"

const enemySpawn shootingEnemySpawns[6] = {
    { 40, 56 }, { 80, 56 }, { 120, 56 }, 
    { 40, 88 }, { 120, 88 }, { 80, 88 }, 
};

UINT8 crosshairXPosition;
UINT8 crosshairYPosition;
BOOLEAN canShoot;
BOOLEAN canReload;
BOOLEAN shootingEnemySpawnsInUse[6];
explosive explosives[6];
UINT8 enemiesLeft;
UINT8 enemiesToSpawn;
UINT8 spawnEnemyTimer[6];
UINT8 ammo;
BOOLEAN showBoom;
UINT8 ammoTile;

void load_game_mode_shooting() {
    canPause = TRUE;
    randomSeed = clock();
    initrand(randomSeed);
    canShoot = TRUE;
    canReload = TRUE;
    ammo = 6;
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
    gb_decompress_bkg_data(0, ShootingBackground_tile_data);
    set_bkg_data(ShootingBackground_tile_count, 1, bulletTile);
    set_bkg_data(ShootingBackground_tile_count + 1, 1, heartTile);
    gb_decompress(ShootingBackground_map_data, buffer);
    set_bkg_tiles(0, 0, ShootingBackground_tile_map_width, ShootingBackground_tile_map_height, buffer);
    gb_decompress_bkg_data(245, Numbers);
    ammoTile = ShootingBackground_tile_count;
    for (UINT8 i = 0; i != 6; i++) {
        shootingEnemySpawnsInUse[i] = FALSE;
        explosives[i].assigned = FALSE;   
        explosives[i].active = FALSE;        
        explosives[i].timer = 0;
        explosives[i].x = 0;
        explosives[i].y = 0;
        explosives[i].animationIndex = 0;
        explosives[i].exploded = FALSE;
        explosives[i].exploding = FALSE;
        explosives[i].defused = FALSE;
        spawnEnemyTimer[i] = shootingLevels[levels[currentLevel].index].spawnEnemyCooldown;
        set_bkg_tile_xy(11 - i, 1, ammoTile);        
    }   
    for (UINT8 i = 0; i != health; i++) {
        set_bkg_tile_xy(19 - i, 1, ShootingBackground_tile_count + 1);
    }
    gb_decompress_sprite_data(0, ShootingSprites);
    gb_decompress_win_data(220, pausedUITiles);
    gb_decompress(pausedUIMap, buffer);
    set_win_tiles(0, 0, 20, 18, buffer);
    load_shooting_sprites();
    SWITCH_ROM_MBC1(bank);
    timeLeft = shootingLevels[levels[currentLevel].index].timeLeft;
    enemiesLeft = shootingLevels[levels[currentLevel].index].enemies;
    enemiesToSpawn = enemiesLeft;   
    print_integer(enemiesLeft, 2, 0);
    print_integer(timeLeft, 16, 0);
    add_LCD(interrupt_LCD_shooting);    
    showBoom = FALSE;
    enable_interrupts();    
    DISPLAY_ON;
    fade_in_white();  
    set_shooting_song();
    gameMode = GAME_MODE_SHOOTING;     
    decimalTimer = 0;
}

void interrupt_LCD_shooting()  {
    switch (LYC_REG)
    {
        case 0x00:
            move_bkg(0, 0);
            LYC_REG = 0x78;
            break;
        case 0x78:
            if (showBoom == TRUE && decimalTimer % 2 == 0) {
                move_bkg(0, 24);
            } else {
                move_bkg(0, 0);
            }            
            LYC_REG = 0x00;
            break;
    }
}