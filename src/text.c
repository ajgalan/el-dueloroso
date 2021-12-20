#include <gbdk/platform.h>
#include <gbdk/gbdecompress.h>
#include "utils.h"
#include "levels.h"
#include "sound.h"
#include "tiles/textTiles.h"
#include "tiles/numbers.h"

const unsigned char main_menu_option_arcade_mode[] = "ARCADE MODE\0";
const unsigned char main_menu_option_practice_mode[] = "PRACTICE MODE\0";
const unsigned char main_menu_option_survival_mode[] = "SURVIVAL MODE\0";
const unsigned char main_menu_option_blank[] = "\0";
const unsigned char main_menu_option_high_scores[] = "HIGH SCORES\0";
const unsigned char main_menu_option_credits[] = "CREDITS\0";
const unsigned char * main_menu_options_text[] = {
    main_menu_option_arcade_mode, 
    main_menu_option_practice_mode,
    main_menu_option_survival_mode,
    main_menu_option_blank,
    main_menu_option_high_scores,
    main_menu_option_credits
};

const unsigned char arcade_menu_option_easy[] = "EASY\0";
const unsigned char arcade_menu_option_normal[] = "NORMAL\0";
const unsigned char arcade_menu_option_hard[] = "HARD\0";
const unsigned char arcade_menu_option_extreme[] = "EXTREME\0";
const unsigned char * arcade_menu_options_text[] = { 
    arcade_menu_option_easy,
    arcade_menu_option_normal,
    arcade_menu_option_hard,
    arcade_menu_option_extreme
};

const unsigned char press_any_button_text[] = " PRESS ANY BUTTON \0";
const unsigned char score_text[] = "  SCORE \0";
const unsigned char bonus_text[] = "  BONUS\0";
const unsigned char level_complete_text[] = "  LEVEL COMPLETE\0";
const unsigned char level_text[] = "  LEVEL\0";
const unsigned char time_text[] = "  TIME\0";
const unsigned char difficulty_text[] = "  DIFFICULTY\0";
const unsigned char high_scores_text[] = "HIGH  SCORES\0";

const unsigned char level_1_1_text[] = "1-1\0";
const unsigned char level_1_2_text[] = "1-2\0";
const unsigned char level_1_3_text[] = "1-3\0";
const unsigned char level_2_1_text[] = "2-1\0";
const unsigned char level_2_2_text[] = "2-2\0";
const unsigned char level_2_3_text[] = "2-3\0";
const unsigned char level_3_1_text[] = "3-1\0";
const unsigned char level_3_2_text[] = "3-2\0";
const unsigned char level_3_3_text[] = "3-3\0";
const unsigned char level_4_1_text[] = "4-1\0";
const unsigned char level_4_2_text[] = "4-2\0";
const unsigned char level_4_3_text[] = "4-3\0";
const unsigned char level_5_1_text[] = "5-1\0";
const unsigned char level_5_2_text[] = "5-2\0";
const unsigned char level_5_3_text[] = "5-3\0";
const unsigned char * level_names[] = { 
    level_1_1_text,
    level_1_2_text,
    level_1_3_text,
    level_2_1_text,
    level_2_2_text,
    level_2_3_text,
    level_3_1_text,
    level_3_2_text,
    level_3_3_text,
    level_4_1_text,
    level_4_2_text,
    level_4_3_text,
    level_5_1_text,
    level_5_2_text,
    level_5_3_text,
};

const unsigned char round_text[] = "ROUND \0";
const unsigned char rounds_text[] = "ROUNDS\0";
const unsigned char enemy_text[] = "ENEMY - \0";
const unsigned char you_text[] = "YOU - \0";
const unsigned char you_win_text[] = "YOU WIN!\0";
const unsigned char you_lose_text[] = "YOU  LOSE!\0";

const unsigned char lives_text[] = "LIVES\0";
const unsigned char start_text[] = "START\0";
const unsigned char how_to_play_text[] = "HOW TO PLAY\0";
const unsigned char shooting_mode_text[] = " DEFEAT  THE GANG\0";
const unsigned char riding_mode_text[] = "  STOP THE WAGON\0";
const unsigned char duel_1_text[] = "VS LENNY SIMPLETON\0";
const unsigned char duel_2_text[] = "  VS HARRY JONES\0";
const unsigned char duel_3_text[] = " VS REED MATTHEWS\0";
const unsigned char duel_4_text[] = " VS MARTHA GUNNER\0";
const unsigned char duel_5_text[] = "  VS BARRY JONES\0";
const unsigned char * duel_texts[] = {
    duel_1_text,
    duel_2_text,
    duel_3_text,
    duel_4_text,
    duel_5_text
};
const unsigned char how_to_play_duel_text[] = "WIN THREE ROUNDS IN\nTHE DUEL AGAINST\nYOUR OPPONENT\n\n\SHOOT WHEN INDICATED\nON SCREEN\n\nYOU WILL LOSE THE\nROUND IF YOU SHOOT\nEARLY OR IF YOUR\nOPPONENT SHOOTS\nBEFORE YOU DO\n\nPRESS A TO SHOOT\0";
const unsigned char how_to_play_shooting_text[] = "DEFEAT ALL THE FOES\nBEFORE THE TIME IS\nOVER OR BEFORE\nYOU LOSE ALL YOUR\nHEALTH\n\nRELOAD YOUR GUN WHEN\nOUT OF AMMUNITION\n\nSHOOT THE EXPLOSIVES\nBEFORE THEY GO OFF\n\nUSE THE D-PAD TO AIM\n\nPRESS A TO SHOOT\n\nPRESS B TO RELOAD\n\nPRESS START TO PAUSE\0";
const unsigned char how_to_play_riding_text[] = "STOP THE WAGON BY\nSHOOTING IT BEFORE\nTHE TIME IS OVER OR\nBEFORE YOU LOSE ALL\nYOUR HEALTH\n\nAVOID GETTING HIT\nBY BARRELS\n\nUSE THE D-PAD TO\nMOVE LEFT AND RIGHT\n\nPRESS A TO AIM WHILE\nNOT MOVING AND THEN\nPRESS A AGAIN\nTO SHOOT\n\nPRESS START TO PAUSE\0";

const unsigned char credits_text_1[] = "EL DUELOROSO\0";
const unsigned char credits_text_2[] = "A GAME BY ADRIAN JG \0";
const unsigned char credits_text_3[] = "THANKS\0";
const unsigned char credits_text_4[] = "GBDK AND GBDK DEVS\0";
const unsigned char credits_text_5[] = "HUGETRACKER DEVS\0";
const unsigned char credits_text_6[] = "HUGEBUILD DEVS\0";
const unsigned char credits_text_7[] = "SPECIAL THANKS TO\0";
const unsigned char credits_text_8[] = "ALEX\0";
const unsigned char credits_text_9[] = "AND THANK YOU\0";
const unsigned char credits_text_10[] = "FOR PLAYING!\0";
const unsigned char * credits_texts[] = {
    credits_text_1,
    credits_text_2,
    credits_text_3,
    credits_text_4,
    credits_text_5,
    credits_text_6,
    credits_text_7,
    credits_text_8,
    credits_text_9,
    credits_text_10,
};
const unsigned char credits_text[] = "    EL DUELOROSO\nA GAME BY  ADRIAN JG\n\nTHANKS TO\nGBDK-2020 DEVS\nHUGETRACKER DEVS\nHUGEBUILD DEVS\nGAMINGMONSTERS\n\nSPECIAL THANKS TO\nALEX @\n\nAND THANK YOU\nFOR PLAYING!\n\0";
const unsigned char new_record_text[] = "NEW  RECORD!\n";