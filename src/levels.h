#ifndef __levels_h
#define __levels_h

typedef struct level
{
  UINT8 gameMode;
  UINT8 index;
} level;

typedef struct shootingLevel
{
  UINT8 timeLeft;
  UINT8 enemies;
  UINT8 spawnEnemyCooldown;
  UINT8 spawnRate;
} shootingLevel;

typedef struct duelLevel
{
  UINT8 minReadyTime;
  UINT8 maxReadyTime;
  UINT8 minEnemyFireTime;
  UINT8 maxEnemyFireTime;
  UINT8 character;
} duelLevel;

typedef struct ridingLevel
{
  UINT8 timeLeft;
  UINT8 enemyHealth;
} ridingLevel;

extern UINT8 currentLevel;
extern UINT8 lives;
extern UINT8 difficulty;
extern UINT8 textScreenTimer;
extern UINT8 creditsTextIndex;
extern UINT8 creditsTextCursor;
extern UINT8 creditsTimer;
extern UINT8 creditsLine;
extern BOOLEAN isPracticeMode;
extern BOOLEAN isSurvivalMode;
extern BOOLEAN loadPrelevelScreen;
extern BOOLEAN showingHowToPlay;
extern BOOLEAN showingPressAnyKey;
extern BOOLEAN newRecord;

extern const level levels[];
extern const duelLevel duelLevels[];
extern const shootingLevel shootingLevels[];
extern const ridingLevel ridingLevels[];

void load_level();
void load_next_level();
void lose_game();
void reset_values();
void game_over_loop();
void load_game_over();
void game_mode_level_complete_loop();
void load_level_complete();
void print_current_score(UINT8 yPosition);
void print_number_win(UINT8 startingXPosition, UINT8 yPosition, UINT16 number);
void print_number_bkg(UINT8 startingXPosition, UINT8 yPosition, UINT16 number);
void load_prelevel_screen();
void game_mode_prelevel_loop();
void load_high_scores_screen();
void game_mode_credits_loop();
void load_credits();
void load_easter_egg();
void game_mode_easter_egg_loop();
void lose_live();

#endif