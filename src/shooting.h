#ifndef __shooting_h
#define __shooting_h

typedef struct enemySpawn {
    UINT8 x;
    UINT8 y;
} enemySpawn;

typedef struct explosive {
    UINT8 x;
    UINT8 y;
    BOOLEAN assigned;
    BOOLEAN active;
    BOOLEAN exploding;
    BOOLEAN exploded;
    BOOLEAN hidden;
    BOOLEAN defused;
    UINT8 timer;
    UINT8 spriteIndex;
    UINT8 animationIndex;
} explosive;

extern const enemySpawn shootingEnemySpawns[6];

extern UINT8 crosshairXPosition;
extern UINT8 crosshairYPosition;
extern BOOLEAN canShoot;
extern BOOLEAN canReload;
extern BOOLEAN shootingEnemySpawnsInUse[6];
extern UINT8 spawnEnemyTimer[6];
extern explosive explosives[6];
extern UINT8 enemiesLeft;
extern UINT8 enemiesToSpawn;
extern UINT8 ammo;
extern BOOLEAN showBoom;
extern UINT8 ammoTile;

void load_game_mode_shooting();
void interrupt_LCD_shooting();
void game_mode_shooting_loop() BANKED;
void move_crosshair(UINT8 x, UINT8 y) BANKED;
void load_shooting_sprites() BANKED;
void spawn_enemy() BANKED;
void shoot() BANKED;
void update_timers_shooting() BANKED; 
UINT8 get_explosive_sprite_index(UINT8 enemySpawnIndex) BANKED;
BOOLEAN is_explosive_assigned(UINT8 index) BANKED;
void explosives_logic(UINT8 i) BANKED;
void crosshair_logic() BANKED;
void spawn_explosive(UINT8 index) BANKED;
void update_health_ui() BANKED;
void update_ammo_ui() BANKED;
void animate_explosive(UINT8 index) BANKED;
BOOLEAN are_all_explosives_defused() BANKED;
void defuse_explosive(UINT8 i) BANKED;

#endif