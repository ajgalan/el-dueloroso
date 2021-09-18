#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include <rand.h>
#include "utils.h"
#include "sound.h"
#include "levels.h"
#include "shooting.h"
#include "backgrounds/shootingBackground.h"
#include "sprites/shootingSprites.h"
#include "tiles/numbers.h"
#include "tiles/iconsUI.h"

void game_mode_shooting_loop()  {     
    if (decimalTimer == 0 && generate_random_number() < shootingLevels[levels[currentLevel].index].spawnRate && enemiesToSpawn > 0) {
        spawn_enemy();
    }
    crosshair_logic();
    move_crosshair(crosshairXPosition, crosshairYPosition);
    if (joypad() & J_A) {
        shoot();
    } else if (joypad() & J_B) {
        if (ammo != 6 && canReload == TRUE) {
            ammo++;
            update_ammo_ui();
            canReload = FALSE;
            play_reload_sound();
        }        
    } else if (canShoot == FALSE) {
        canShoot = TRUE;
    } else if (canReload == FALSE) {
        canReload = TRUE;
    }

    for (UINT8 i = 0; i < 6; i++) {
        explosives_logic(i);
    }
    
    update_timers_shooting();      

    if (timeLeft == 0 || health == 0) {
        stop_music();
        performant_delay(120);  
        lose_game();
    } else if (enemiesLeft == 0 && are_all_explosives_defused() == TRUE) {
        stop_music();
        performant_delay(60);  
        load_level_complete();
    }
}

void move_crosshair(UINT8 x, UINT8 y)  {
    UINT8 i = 0;
    for (i = 0; i < 4; i++) {
        move_sprite(0, x, y);
        move_sprite(1, x + 8, y);
        move_sprite(2, x, y + 8);
        move_sprite(3, x + 8, y + 8);
    }
}

void load_shooting_sprites()  {
    UINT8 i = 0;    
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 0);
    set_sprite_prop(1, S_FLIPX);    
    set_sprite_tile(2, 0);
    set_sprite_prop(2, S_FLIPY);
    set_sprite_tile(3, 0);
    set_sprite_prop(3, S_FLIPX | S_FLIPY);

    for (i = 4; i <= 28; i = i + 4) {
        set_sprite_tile(i, 1);
        set_sprite_tile(i + 1, 2);
        set_sprite_tile(i + 2, 1);
        set_sprite_tile(i + 3, 2);     
        if (i > 27) {
            set_sprite_tile(i, 3);
            set_sprite_tile(i + 1, 4);
            set_sprite_tile(i + 2, 3);
            set_sprite_tile(i + 3, 4); 
        }   
        if (i < 24) {
            set_sprite_prop(i, S_PRIORITY);
            set_sprite_prop(i + 1, S_PRIORITY);
            set_sprite_prop(i + 2, S_FLIPX | S_PRIORITY);
            set_sprite_prop(i + 3, S_FLIPX | S_PRIORITY);
        } else {
            set_sprite_prop(i + 2, S_FLIPX);
            set_sprite_prop(i + 3, S_FLIPX);
        }        
    }
}

void spawn_enemy()  {
    UINT8 i = 0;      
    BOOLEAN allSpawnPointsTaken = TRUE;
    for (i = 0; i < 6; i++) {
        if (shootingEnemySpawnsInUse[i] == FALSE) {
            allSpawnPointsTaken = FALSE;
            break;
        }        
    }    
    if (!allSpawnPointsTaken) {
        UINT8 spawnIndex = generate_random_number() % 6;  
        while (shootingEnemySpawnsInUse[spawnIndex] == TRUE) { 
            spawnIndex = generate_random_number() % 6;
        }
        if (spawnEnemyTimer[spawnIndex] == 0) {
            move_sprite((4 * spawnIndex) + 4 , shootingEnemySpawns[spawnIndex].x, shootingEnemySpawns[spawnIndex].y);
            move_sprite((4 * spawnIndex) + 5, shootingEnemySpawns[spawnIndex].x, shootingEnemySpawns[spawnIndex].y + 8);
            move_sprite((4 * spawnIndex) + 6, shootingEnemySpawns[spawnIndex].x + 8, shootingEnemySpawns[spawnIndex ].y);
            move_sprite((4 * spawnIndex) + 7, shootingEnemySpawns[spawnIndex].x + 8, shootingEnemySpawns[spawnIndex].y + 8);
            if (spawnIndex == 5) {
                move_sprite((4 * spawnIndex) + 8 , shootingEnemySpawns[spawnIndex].x, shootingEnemySpawns[spawnIndex].y + 16);
                move_sprite((4 * spawnIndex) + 9, shootingEnemySpawns[spawnIndex].x, shootingEnemySpawns[spawnIndex].y + 24);
                move_sprite((4 * spawnIndex) + 10, shootingEnemySpawns[spawnIndex].x + 8, shootingEnemySpawns[spawnIndex ].y + 16);
                move_sprite((4 * spawnIndex) + 11, shootingEnemySpawns[spawnIndex].x + 8, shootingEnemySpawns[spawnIndex].y + 24);
            }
            shootingEnemySpawnsInUse[spawnIndex] = TRUE;
            enemiesToSpawn--;
            if (is_explosive_assigned(spawnIndex) == FALSE) { explosives[spawnIndex].assigned = TRUE; }
            if (explosives[spawnIndex].assigned == TRUE && explosives[spawnIndex].active == FALSE) { 
                spawn_explosive(spawnIndex);
            }
        }                 
    }
}

void shoot()  {
    UINT8 i = 0;
    if (canShoot == TRUE && ammo != 0) {
        ammo--;
        update_ammo_ui();
        for (i = 0; i != 6; i++) {
            if ((joypad() & J_DOWN) && explosives[i].exploding == TRUE && explosives[i].x == crosshairXPosition - 1) {                
                defuse_explosive(i);
            } else if (shootingEnemySpawnsInUse[i] == TRUE && shootingEnemySpawns[i].x == crosshairXPosition && shootingEnemySpawns[i].y == crosshairYPosition) {
                print_integer(--enemiesLeft, 2, 0);
                move_sprite((4 * i) + 4 , 0, 0);
                move_sprite((4 * i) + 5 , 0, 0);
                move_sprite((4 * i) + 6 , 0, 0);
                move_sprite((4 * i) + 7 , 0, 0);
                if (i == 5) {
                    move_sprite((4 * i) + 8 , 0, 0);
                    move_sprite((4 * i) + 9 , 0, 0);
                    move_sprite((4 * i) + 10 , 0, 0);
                    move_sprite((4 * i) + 11 , 0, 0);
                }
                shootingEnemySpawnsInUse[i] = FALSE;
                spawnEnemyTimer[i] = shootingLevels[levels[currentLevel].index].spawnEnemyCooldown;
                if (explosives[i].assigned == TRUE && explosives[i].active == FALSE) {
                    explosives[i].assigned = FALSE;
                }
                break;            
            }            
        }      
        if (ammo == 0) {
            play_last_bullet_shoot_sound();
        } else {
            play_shoot_sound(); 
        } 
        canShoot = FALSE;     
    } else if (canShoot == TRUE && ammo == 0) {
        play_empty_sound();
        canShoot = FALSE;
    }
}

void explosives_logic(UINT8 i) {
    if (explosives[i].assigned == TRUE) {
        if (explosives[i].active == FALSE) {
            explosives[i].timer -= 1;
            if (explosives[i].timer == 0) {
                explosives[i].active = TRUE;     
            }
        } else {
            if (decimalTimer == 0 && explosives[i].defused == FALSE) {
                if (explosives[i].exploding == FALSE && explosives[i].exploded == FALSE) {
                    if (explosives[i].y < 126) {
                        animate_explosive(i);
                        explosives[i].y++;
                    } else {
                        move_sprite(explosives[i].spriteIndex, explosives[i].x, explosives[i].y);
                        move_sprite(explosives[i].spriteIndex + 1, explosives[i].x + 8, explosives[i].y);
                        set_sprite_tile(explosives[i].spriteIndex, 5);
                        set_sprite_tile(explosives[i].spriteIndex + 1, 7);
                        if (explosives[i].animationIndex == 0 || explosives[i].animationIndex == 2) {                             
                            set_sprite_prop(explosives[i].spriteIndex, 0);
                            set_sprite_prop(explosives[i].spriteIndex + 1, 0);
                        } else {
                            set_sprite_prop(explosives[i].spriteIndex, S_FLIPY);
                            set_sprite_prop(explosives[i].spriteIndex + 1, 0);
                        }
                    }         
                    explosives[i].y++;
                    explosives[i].animationIndex++;
                    if (explosives[i].animationIndex == 4) {
                        explosives[i].animationIndex = 0;
                    }                  
                    if (explosives[i].y == 138) {
                        play_almost_exploding_sound();
                        explosives[i].exploding = TRUE;
                        explosives[i].timer = 30;
                    }
                }    
                else if (explosives[i].exploding == TRUE || explosives[i].exploded == TRUE) {
                    if (explosives[i].hidden == FALSE) {
                        explosives[i].hidden = TRUE;
                        move_sprite(explosives[i].spriteIndex, 0, 0);
                        move_sprite(explosives[i].spriteIndex + 1, 0, 0);
                    } else if (explosives[i].exploded == FALSE){
                        explosives[i].hidden = FALSE;
                        move_sprite(explosives[i].spriteIndex, explosives[i].x, explosives[i].y);
                        move_sprite(explosives[i].spriteIndex + 1, explosives[i].x + 8, explosives[i].y);
                    }                    
                    explosives[i].timer--;
                    if (explosives[i].exploding == TRUE && explosives[i].timer == 0) {
                        explosives[i].exploding = FALSE;
                        explosives[i].exploded = TRUE;
                        explosives[i].timer = 10;
                        showBoom = TRUE;                        
                        move_sprite(explosives[i].spriteIndex, 0, 0);
                        move_sprite(explosives[i].spriteIndex + 1, 0, 0);   
                        if (isPracticeMode == FALSE) { health--; }
                        update_health_ui(); 
                        for (UINT8 i = 0; i !=6; i++) {
                            if (explosives[i].exploding == TRUE) {
                                defuse_explosive(i);
                            }
                        }
                        play_explosion_sound();
                    } else if (explosives[i].exploded == TRUE && explosives[i].timer == 0) {                      
                        explosives[i].exploded = FALSE;
                        explosives[i].exploding = FALSE;                       
                        if (shootingEnemySpawnsInUse[i] == TRUE) {
                            spawn_explosive(i);
                        } else {
                            explosives[i].assigned = FALSE;
                            explosives[i].active = FALSE;
                        }
                        showBoom = FALSE;                       
                    }                   
                }                  
            }  else if (explosives[i].defused == TRUE) {                
                if (explosives[i].x > 168) {
                    explosives[i].defused = FALSE;
                    move_sprite(explosives[i].spriteIndex, 0, 0);
                    move_sprite(explosives[i].spriteIndex + 1, 0, 0);
                    if (shootingEnemySpawnsInUse[i] == TRUE) {
                        spawn_explosive(i);
                    } else {
                        explosives[i].assigned = FALSE;
                        explosives[i].active = FALSE;
                    } 
                } else {  
                    explosives[i].animationIndex++;
                    if (explosives[i].animationIndex == 4) {
                        explosives[i].animationIndex = 0;
                    }                               
                    explosives[i].y--;
                    if (i % 2 == 0) {
                        explosives[i].x = explosives[i].x-2;
                    } else {
                        explosives[i].x = explosives[i].x+2;
                    } 
                    animate_explosive(i);                   
                }     
            }
        }
    }
}

void crosshair_logic()  {
    if (joypad() & J_LEFT && joypad() & J_UP) {
        crosshairXPosition = shootingEnemySpawns[0].x;
        crosshairYPosition = shootingEnemySpawns[0].y;
    } else if (joypad() & J_RIGHT && joypad() & J_UP) {
        crosshairXPosition = shootingEnemySpawns[2].x;
        crosshairYPosition = shootingEnemySpawns[2].y;
    } else if (joypad() & J_LEFT && joypad() & J_DOWN) {
        crosshairXPosition = 40;
        crosshairYPosition = 134;
    } else if (joypad() & J_RIGHT && joypad() & J_DOWN) {
        crosshairXPosition = 120;
        crosshairYPosition = 134;
    } else if (joypad() & J_UP) {
        crosshairXPosition = shootingEnemySpawns[1].x;
        crosshairYPosition = shootingEnemySpawns[1].y;
    } else if (joypad() & J_DOWN) {
        crosshairXPosition = 80;
        crosshairYPosition = 134;
    } else if (joypad() & J_LEFT) {
        crosshairXPosition = shootingEnemySpawns[3].x;
        crosshairYPosition = shootingEnemySpawns[3].y;
    } else if (joypad() & J_RIGHT) {
        crosshairXPosition = shootingEnemySpawns[4].x;
        crosshairYPosition = shootingEnemySpawns[4].y;
    } else if (!joypad()){
        crosshairXPosition = shootingEnemySpawns[5].x;
        crosshairYPosition = shootingEnemySpawns[5].y;
    }
}

void update_timers_shooting()  {
    if (secondTimer == 0) {
        print_integer(timeLeft--, 16, 0);
    }
    if (decimalTimer == 0) {
        for (UINT8 i = 0; i !=6; i++){
            if (spawnEnemyTimer[i] != 0) { spawnEnemyTimer[i]--; }
        }
    }   
}

UINT8 get_explosive_sprite_index(UINT8 enemySpawnIndex)  {
    switch (enemySpawnIndex) {
        case 0:
        case 3:
            return 32;
            break;
        case 1:
        case 5:
            return 34;
            break;
        case 2:
        case 4:
            return 36;
            break;
        default:
            return 39;
    }
}

BOOLEAN is_explosive_assigned(UINT8 index)  {
    if (explosives[index].assigned == TRUE) {
        return TRUE;
    } else {
        if (index == 0) {
            return explosives[3].assigned;
        } else if (index == 1) {
            return explosives[5].assigned;
        } else if (index == 2) {
            return explosives[4].assigned;
        } else if (index == 3) {
            return explosives[0].assigned;
        } else if (index == 4) {
            return explosives[2].assigned;
        } else if (index == 5) {
            return explosives[1].assigned;
        } else {
            return FALSE;
        }
    }
}

void spawn_explosive(UINT8 index)  {
    explosives[index].active == FALSE;
    explosives[index].timer = generate_random_number();
    explosives[index].x = shootingEnemySpawns[index].x - 1;
    explosives[index].y = shootingEnemySpawns[index].y + 12;
    explosives[index].spriteIndex = get_explosive_sprite_index(index);
    explosives[index].animationIndex = 0;
    explosives[index].exploded = FALSE;
    explosives[index].exploding = FALSE;
    explosives[index].defused = FALSE;
}

void update_health_ui()  {
    set_bkg_tile_xy(19 - health, 1, 3);
}

void update_ammo_ui()  {
    if (ammo != 0) {
        set_bkg_tile_xy(12 - ammo, 1, ammoTile);
    }
    set_bkg_tile_xy(11 - ammo, 1, 3);
}

void animate_explosive(UINT8 index)  {
    switch (explosives[index].animationIndex)
    {
        case 0:
            move_sprite(explosives[index].spriteIndex, explosives[index].x, explosives[index].y);
            move_sprite(explosives[index].spriteIndex + 1, explosives[index].x + 8, explosives[index].y);
            set_sprite_tile(explosives[index].spriteIndex, 5);
            set_sprite_tile(explosives[index].spriteIndex + 1, 7); 
            set_sprite_prop(explosives[index].spriteIndex, 0);
            set_sprite_prop(explosives[index].spriteIndex + 1, 0);
            break;
        case 1:
            move_sprite(explosives[index].spriteIndex, explosives[index].x, explosives[index].y);
            move_sprite(explosives[index].spriteIndex + 1, explosives[index].x, explosives[index].y + 8);
            set_sprite_tile(explosives[index].spriteIndex, 6);
            set_sprite_tile(explosives[index].spriteIndex + 1, 8);
            set_sprite_prop(explosives[index].spriteIndex, S_FLIPX);
            set_sprite_prop(explosives[index].spriteIndex + 1, S_FLIPY);
            break;
        case 2:
            move_sprite(explosives[index].spriteIndex, explosives[index].x, explosives[index].y);
            move_sprite(explosives[index].spriteIndex + 1, explosives[index].x - 8, explosives[index].y);
            set_sprite_tile(explosives[index].spriteIndex, 5);
            set_sprite_tile(explosives[index].spriteIndex + 1, 7); 
            set_sprite_prop(explosives[index].spriteIndex, S_FLIPY);
            set_sprite_prop(explosives[index].spriteIndex + 1, S_FLIPX);
            break;
        case 3:
            move_sprite(explosives[index].spriteIndex, explosives[index].x, explosives[index].y);
            move_sprite(explosives[index].spriteIndex + 1, explosives[index].x, explosives[index].y - 8);
            set_sprite_tile(explosives[index].spriteIndex, 6);
            set_sprite_tile(explosives[index].spriteIndex + 1, 8);
            set_sprite_prop(explosives[index].spriteIndex, S_FLIPY);
            set_sprite_prop(explosives[index].spriteIndex + 1, S_FLIPX);
            break;
        default:
            break;
    }
}

BOOLEAN are_all_explosives_defused()  {
    for (UINT8 i = 0; i != 6; i++) {
        if (explosives[i].active == TRUE || explosives[i].defused == TRUE) {
            return FALSE;
        }
    }
    return TRUE;
}

void defuse_explosive(UINT8 i)  {
    explosives[i].exploding = FALSE;
    explosives[i].defused = TRUE;
    explosives[i].hidden = FALSE;
    move_sprite(explosives[i].spriteIndex, explosives[i].x, explosives[i].y);
    move_sprite(explosives[i].spriteIndex + 1, explosives[i].x + 8, explosives[i].y);
}