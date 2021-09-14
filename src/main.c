#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "rand.h"
#include "utils.h"
#include "title.h"
#include "levels.h"
#include "sound.h"
#include "duel.h"
#include "shooting.h"
#include "riding.h"
#include "text.h"
#include "backgrounds/adrianjgLogo.h"
#include "backgrounds/gbcompo2021.h"

void main()  {        
	DISPLAY_OFF;
    initialize_save_data();
    disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;  
    UINT8 bank = _current_bank;  
    SWITCH_ROM_MBC1(2);
    gb_decompress(adrianjgLogo_map_data, buffer);
    set_bkg_submap(0, 0, adrianjgLogo_tile_map_width, adrianjgLogo_tile_map_height, buffer, adrianjgLogo_tile_map_width);
    gb_decompress_bkg_data(0 , adrianjgLogo_tile_data);
    enable_interrupts();
    DISPLAY_ON;
    SHOW_BKG;
    fade_in_white();
    performant_delay(120);
    fade_out_white();
    gb_decompress(gbCompo2021_map_data, buffer);
    set_bkg_submap(0, 0, gbCompo2021_tile_map_width, gbCompo2021_tile_map_height, buffer, gbCompo2021_tile_map_width);
    gb_decompress_bkg_data(0 , gbCompo2021_tile_data);
    SWITCH_ROM_MBC1(bank);
    fade_in_white();
    performant_delay(120);
    fade_out_white();
    randomSeed = DIV_REG;
    OBP1_REG = 170;    
    load_game_mode_title();    
    while (1) {
        if (isPaused == TRUE) {
            if (joypad() == J_START) { 
                isPaused = FALSE;                
                performant_wait_pad_up();
                SHOW_SPRITES;
                HIDE_WIN;
                enable_music();    
            }
        } else {
            if (playingMusic > 1) {playingMusic--;}        
            switch (gameMode) {
                case GAME_MODE_TITLE:
                    game_mode_title_loop();
                    break;
                case GAME_MODE_DUEL:
                    game_mode_duel_loop();
                    break;
                case GAME_MODE_SHOOTING:
                    game_mode_shooting_loop();
                    break;
                case GAME_MODE_RIDING:
                    game_mode_riding_loop();
                    break;      
                case GAME_MODE_PRELEVEL:
                    game_mode_prelevel_loop();
                    break;
                case GAME_MODE_GAME_OVER:
                    game_over_loop();
                    break;
                case GAME_MODE_LEVEL_COMPLETE:
                    game_mode_level_complete_loop();
                    break;
                case GAME_MODE_CREDITS:
                    game_mode_credits_loop();
                    break;
                case GAME_MODE_EASTER_EGG:
                    game_mode_easter_egg_loop();
            }
            if (joypad() & (J_A) && joypad() & J_B && joypad() & J_START && joypad() & J_SELECT) { reset(); }
                       
            add_time();      
            play_music();
            if (canPause == TRUE && joypad() == J_START) {
                isPaused = TRUE;
                mute_music();
                HIDE_SPRITES;
                move_win(7, 0);
                SHOW_WIN;
                play_beep_sound();
                performant_delay(3);
                play_beep_sound();
                performant_delay(3);
                play_beep_sound();
                performant_delay(3);
                play_beep_sound();
                performant_delay(3);
                performant_wait_pad_up();
            } 
        }        
        wait_vbl_done();
    }
}