
#ifndef __riding_h
#define __riding_h

enum STATES_CARRIAGE {
    STATE_CARRIAGE_IDLE,
    STATE_CARRIAGE_MOVING,
    STATE_CARRIAGE_TAKING_DAMAGE,
    STATE_CARRIAGE_BROKEN,
};

extern UINT8 cameraXPosition;
extern UINT8 horseXPosition;
extern UINT8 horseYPosition;
extern UINT8 carriageXPosition;
extern UINT8 carriageYPosition;
extern UINT8 barrelXPosition;
extern UINT8 barrelYPosition;
extern UINT8 backgroundAnimation;
extern UINT8 carriageXPositionTarget;
extern UINT8 carriageState;
extern UINT8 carriageTimer;
extern INT8 xSpeedBarrel;
extern UINT8 canPlayerBeHurted;
extern UINT8 enemyHealth;
extern UINT8 crosshairXPositionRiding;
extern INT8 crosshairXSpeed;
extern UINT8 isAiming;
extern UINT8 isAButtonReleased;
extern UINT8 enemyRecoveryCooldown;

extern const UINT8 barrelYLimit;
extern const UINT8 carriageXPositions[5];

void load_game_mode_riding();
void interrupt_LCD_riding();
void game_mode_riding_loop() BANKED;
void load_riding_mode_sprites() BANKED;
void move_horse_sprites(UINT8 x, UINT8 y) BANKED;
void barrel_logic() BANKED;
void spawn_barrel() BANKED;
void move_carriage_sprites(UINT8 x) BANKED;
void carriage_logic() BANKED;
void update_timers_riding() BANKED;
void take_damage() BANKED;
void update_enemy_health() BANKED;
void stopAiming() BANKED;

#endif