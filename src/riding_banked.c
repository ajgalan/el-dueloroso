#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "utils.h"
#include "sound.h"
#include "riding.h"
#include "levels.h"
#include "backgrounds/ridingBackground.h"
#include "sprites/ridingSprites.h"
#include "sprites/shootingSprites.h"
#include "tiles/numbers.h"
#include "tiles/iconsUI.h"

void game_mode_riding_loop() {   
    if (canPlayerBeHurted == TRUE && barrelYPosition > 149 && barrelYPosition < 165 && horseXPosition > barrelXPosition - 25 && horseXPosition - 9 < barrelXPosition) {
        take_damage();
    } 

    if (joypad() & J_LEFT){
        stopAiming();
        if (cameraXPosition != 0 && horseXPosition > 75 && horseXPosition < 173) {
            cameraXPosition--;
        }
        if (horseXPosition != 25) {
            horseXPosition--;
        }
    } else if (joypad() & J_RIGHT) {
        stopAiming();
        if (cameraXPosition != 96 && horseXPosition > 75 && horseXPosition < 173) {
            cameraXPosition++;
        }
        if (horseXPosition != 223) {
            horseXPosition++;
        }
    } else if (joypad() & J_A && isAiming == FALSE && isAButtonReleased == TRUE) {
        isAiming = TRUE;       
        crosshairXPositionRiding = 8;
        crosshairXSpeed = 3;
    } else if (joypad() & J_A && isAiming == TRUE && isAButtonReleased == TRUE) {
        stopAiming();
        play_shoot_sound();
        if (enemyRecoveryCooldown == 0 && crosshairXPositionRiding > carriageXPosition - cameraXPosition - 12 && crosshairXPositionRiding < carriageXPosition - cameraXPosition + 16) {             
            enemyRecoveryCooldown = 100;
            for (UINT8 i = 25; i != 31; i++) {
                set_sprite_prop(i, S_PALETTE);
            }
            for (UINT8 i = 31; i != 34; i++) {
                set_sprite_prop(i, S_FLIPX | S_PALETTE);
            }           
            enemyHealth--;
            update_enemy_health();
            play_carriage_damaged_sound();
        }        
    }

    isAButtonReleased = !(joypad() & J_A);     

    if (decimalTimer == 0 && timer % 2 == 0) {
        horseYPosition = 140;   
        carriageYPosition = 72;    
    } else if (decimalTimer == 0) {
        horseYPosition = 136;
        carriageYPosition = 71; 
    }   

    carriage_logic();
    move_horse_sprites(horseXPosition - cameraXPosition, horseYPosition); 
    move_carriage_sprites(carriageXPosition - cameraXPosition);    
    barrel_logic(); 

    if (isAiming == TRUE) {
        move_sprite(18, crosshairXPositionRiding, 72);
        move_sprite(19, crosshairXPositionRiding + 8, 72);
        move_sprite(20, crosshairXPositionRiding, 80);
        move_sprite(21, crosshairXPositionRiding + 8, 80);
        if (crosshairXPositionRiding == 8 && crosshairXSpeed == -3) {
            crosshairXSpeed = 3;
        } else if (crosshairXPositionRiding == 152 && crosshairXSpeed == 3) {
            crosshairXSpeed = -3;
        }
        crosshairXPositionRiding += crosshairXSpeed;
    }

    if (decimalTimer == 0 && OBP1_REG == 255) {
        OBP1_REG = 170;
    } else if (decimalTimer == 0 && OBP1_REG == 170) {
        OBP1_REG = 255;
    } 
    
    update_timers_riding();     

    if (timeLeft == 0 || health == 0) {
        stop_music();
        performant_delay(120);  
        lose_game();
    } else if (enemyHealth == 0) {
        stop_music();
        performant_delay(60);  
        load_level_complete();
    }

    CRITICAL {
        if (decimalTimer == 0) {
            if (backgroundAnimation == 0) {
                backgroundAnimation = 1; 
            } else {
                backgroundAnimation = 0;
            }                               
        } 
    }
}

void load_riding_mode_sprites() {   
    //Horse 
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    set_sprite_tile(4, 4);
    set_sprite_tile(5, 5);
    set_sprite_tile(6, 0);
    set_sprite_prop(6, S_FLIPX);
    set_sprite_tile(7, 1);
    set_sprite_prop(7, S_FLIPX);
    set_sprite_tile(8, 2);
    set_sprite_prop(8, S_FLIPX);

    //BarrelFar
    set_sprite_tile(9, 6);

    //BarrelMedium
    set_sprite_tile(10, 7);
    set_sprite_tile(11, 7);

    //BarrelClose
    set_sprite_prop(14, S_FLIPX);
    set_sprite_prop(15, S_FLIPY);
    set_sprite_prop(16, S_FLIPY);
    set_sprite_prop(17, S_FLIPX | S_FLIPY);

    //Crosshair
    set_sprite_tile(18, 18);
    set_sprite_tile(19, 18);
    set_sprite_prop(19, S_FLIPX);    
    set_sprite_tile(20, 18);
    set_sprite_prop(20, S_FLIPY);
    set_sprite_tile(21, 18);
    set_sprite_prop(21, S_FLIPX | S_FLIPY);

    //Carriage
    set_sprite_tile(25, 12);
    set_sprite_tile(26, 13);
    set_sprite_tile(27, 14);
    set_sprite_tile(28, 15);
    set_sprite_tile(29, 16);
    set_sprite_tile(30, 17);
    set_sprite_tile(31, 12);
    set_sprite_prop(31, S_FLIPX);
    set_sprite_tile(32, 13);
    set_sprite_prop(32, S_FLIPX);
    set_sprite_tile(33, 14);
    set_sprite_prop(33, S_FLIPX);
}

void move_horse_sprites(UINT8 x, UINT8 y) {
    move_sprite(0, x, y);
    move_sprite(1, x, y + 8);
    move_sprite(2, x, y + 16);
    move_sprite(3, x + 8, y);
    move_sprite(4, x + 8, y + 8);
    move_sprite(5, x + 8, y + 16);
    move_sprite(6, x + 16, y);
    move_sprite(7, x + 16, y + 8);
    move_sprite(8, x + 16, y + 16);
}

void move_carriage_sprites(UINT8 x) {
    move_sprite(25, x, carriageYPosition);
    move_sprite(26, x, carriageYPosition + 8);
    move_sprite(27, x, carriageYPosition + 16);
    move_sprite(28, x + 8, carriageYPosition);
    move_sprite(29, x + 8, carriageYPosition + 8);
    move_sprite(30, x + 8, carriageYPosition + 16);
    move_sprite(31, x + 16, carriageYPosition);
    move_sprite(32, x + 16, carriageYPosition + 8);
    move_sprite(33, x + 16, carriageYPosition + 16);
}

void barrel_logic() {   
    if (decimalTimer % 2 == 0) {
        barrelXPosition += 1 * xSpeedBarrel;
    }
    if (barrelYPosition == barrelYLimit) {
        if (canPlayerBeHurted == FALSE) {
            canPlayerBeHurted = TRUE;
            for (UINT8 i = 0; i != 6; i++) {
                set_sprite_prop(i, 0);
            }
            for (UINT8 i = 6; i != 9; i++) {
                set_sprite_prop(i, S_FLIPX);
            }
        }
        if (carriageState == STATE_CARRIAGE_IDLE) {
            spawn_barrel();
        }
    } else if (barrelYPosition == 102) {
        move_sprite(9, 0, 0);
    } else if (barrelYPosition == 127) {
        move_sprite(10, 0, 0);
        move_sprite(11, 0, 0);  
    }
    if (barrelYPosition < 102) {
        move_sprite(9, barrelXPosition - cameraXPosition, barrelYPosition);
    } else if (barrelYPosition < 127){
        move_sprite(10, barrelXPosition - cameraXPosition - 4, barrelYPosition);
        move_sprite(11, barrelXPosition - cameraXPosition + 4, barrelYPosition);        
    } else if (barrelYPosition < barrelYLimit) {
        move_sprite(12, barrelXPosition - cameraXPosition - 8, barrelYPosition - 8);
        move_sprite(13, barrelXPosition - cameraXPosition, barrelYPosition - 8);
        move_sprite(14, barrelXPosition - cameraXPosition + 8, barrelYPosition - 8);
        move_sprite(15, barrelXPosition - cameraXPosition - 8, barrelYPosition);
        move_sprite(16, barrelXPosition - cameraXPosition, barrelYPosition);
        move_sprite(17, barrelXPosition - cameraXPosition + 8, barrelYPosition);        
    } 
    if (barrelYPosition != barrelYLimit) {
        barrelYPosition++;
    }
    
    if (decimalTimer == 0) {
        set_sprite_prop(9, 0);

        set_sprite_prop(10, 0);
        set_sprite_prop(11, S_FLIPX);

        set_sprite_tile(12, 8);
        set_sprite_tile(13, 10);
        set_sprite_tile(14, 8);
        set_sprite_tile(15, 9);
        set_sprite_tile(16, 11);
        set_sprite_tile(17, 9);
    }  else if (decimalTimer == 3) {
        set_sprite_prop(9, S_FLIPY );

        set_sprite_prop(10, S_FLIPY);
        set_sprite_prop(11, S_FLIPX | S_FLIPY);

        set_sprite_tile(12, 9);
        set_sprite_tile(13, 11);
        set_sprite_tile(14, 9);
        set_sprite_tile(15, 8);
        set_sprite_tile(16, 10);
        set_sprite_tile(17, 8);
    }        
}

void spawn_barrel() {    
    if (generate_random_number() % 2 == 0) {
        xSpeedBarrel = 0;
    } else {
        if (horseXPosition < carriageXPosition) {
            xSpeedBarrel = -1;
        } else {
            xSpeedBarrel = 1;
        }
    }    
    barrelXPosition = carriageXPosition + 8;
    barrelYPosition = 92;    
}

void carriage_logic() {
    switch (carriageState) {
        case STATE_CARRIAGE_IDLE:
            if (carriageTimer != 0) {
                carriageTimer--;
            } else {
                carriageXPositionTarget = generate_random_number() % 5;                
                carriageState = STATE_CARRIAGE_MOVING;
            }        
            break;
        
        case STATE_CARRIAGE_MOVING:
            if (carriageXPositions[carriageXPositionTarget] == carriageXPosition) {
                carriageTimer = generate_random_number();
                carriageState = STATE_CARRIAGE_IDLE;
            } else if (carriageXPositions[carriageXPositionTarget] < carriageXPosition) {
                carriageXPosition--;
            }
            else if (carriageXPositions[carriageXPositionTarget] > carriageXPosition) {
                carriageXPosition++;
            }
            break;
    }    
}

void update_timers_riding() {
    if (secondTimer == 0) {
        print_integer(timeLeft--, 16, 0);
    }    
    if (enemyRecoveryCooldown == 1) {
        for (UINT8 i = 25; i != 31; i++) {
            set_sprite_prop(i, 0);
        }
        for (UINT8 i = 31; i != 34; i++) {
            set_sprite_prop(i, S_FLIPX);
        } 
    }  
    if (enemyRecoveryCooldown != 0) {
        enemyRecoveryCooldown--;
    }    
}

void take_damage() {
    stopAiming();
    for (UINT8 i = 0; i != 6; i++) {
        set_sprite_prop(i, S_PALETTE);
    }
    for (UINT8 i = 6; i != 9; i++) {
        set_sprite_prop(i, S_FLIPX | S_PALETTE);
    }
    canPlayerBeHurted = FALSE;
    if (isPracticeMode == FALSE) { health--; }
    set_bkg_tile_xy(19 - health, 1, 0);
    play_take_damage_sound();
}

void update_enemy_health() {
    UINT8 n = enemyHealth;
    for (UINT8 i = 0; i != 9; i++) {
        if (n == 0) {
            set_bkg_tile_xy(i, 1, 0x00);         
        } else if (n == 1) {
            set_bkg_tile_xy(i, 1, 0x60);            
        } else if (n == 2) {
            set_bkg_tile_xy(i, 1, 0x61);
        } else if (n == 3) {
            set_bkg_tile_xy(i, 1, 0x62);
        } else {
            set_bkg_tile_xy(i, 1, 0x63);            
        }
        if (n > 3) {
            n = n - 4;
        } else {
            n = 0;
        }
    }
}

void stopAiming() {
    isAiming = FALSE;
    for (UINT8 i = 18; i != 22; i++) {
        move_sprite(i, 0, 0);
    }
}