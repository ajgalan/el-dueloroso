#include <gbdk/platform.h>
#include "sound/hUGEDriver.h"

extern const hUGESong_t titleSong;
extern const hUGESong_t shootingSong;
extern const hUGESong_t ridingSong;
extern const hUGESong_t loseSong;
extern const hUGESong_t winSong;

UINT8 playingMusic = FALSE;
UINT8 channel1Timer;
UINT8 channel2Timer;
UINT8 channel3Timer;
UINT8 channel4Timer;

void play_music() {    
    if (playingMusic == TRUE) {
        UINT8 bank = _current_bank;
        SWITCH_ROM_MBC1(3);
        if (channel1Timer != 0) {
            channel1Timer--;
        } else {
            hUGE_mute_channel(HT_CH1, HT_CH_PLAY);
        }
        if (channel2Timer != 0) {
            channel2Timer--;
        } else {
            hUGE_mute_channel(HT_CH2, HT_CH_PLAY);
        }
        if (channel3Timer != 0) {
            channel3Timer--;
        } else {
            hUGE_mute_channel(HT_CH3, HT_CH_PLAY);
        }
        if (channel4Timer != 0) {
            channel4Timer--;
        } else {
            hUGE_mute_channel(HT_CH4, HT_CH_PLAY);
        }       
        hUGE_dosound();  
        SWITCH_ROM_MBC1(bank);
    }
}    

void stop_music() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH2, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH3, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH4, HT_CH_MUTE);    
    SWITCH_ROM_MBC1(bank);
    playingMusic = FALSE;
}

void set_title_song() {    
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_init(&titleSong);  
    SWITCH_ROM_MBC1(bank);
    playingMusic = TRUE;
}

void set_shooting_song() {    
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_init(&shootingSong);  
    SWITCH_ROM_MBC1(bank);
    playingMusic = TRUE;
}

void set_riding_song() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_init(&ridingSong);  
    SWITCH_ROM_MBC1(bank);
    playingMusic = TRUE;
}

void set_win_song() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_init(&winSong);  
    SWITCH_ROM_MBC1(bank);
    playingMusic = TRUE;
}

void set_lose_song() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_init(&loseSong);  
    SWITCH_ROM_MBC1(bank);
    playingMusic = TRUE;
}

void play_shoot_sound() {   
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR10_REG = 0x5E;
    NR11_REG = 0xC2;
    NR12_REG = 0xB3;
    NR13_REG = 0x66;
    NR14_REG = 0x86;
    channel1Timer = 10;    
}

void play_last_bullet_shoot_sound() {   
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR10_REG = 0x5E;
    NR11_REG = 0xC2;
    NR12_REG = 0xB3;
    NR13_REG = 0x66;
    NR14_REG = 0x85;
    channel1Timer = 10;    
}

void play_almost_exploding_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH4, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR41_REG = 0x26;
    NR42_REG = 0x79;
    NR43_REG = 0x10;
    NR44_REG = 0xC0;   
    channel4Timer = 10;  
}

void play_explosion_sound() {    
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH4, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR41_REG = 0x00;
    NR42_REG = 0x79;
    NR43_REG = 0x47;
    NR44_REG = 0xC0;   
    channel4Timer = 45;  
}

void play_empty_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank); 
    NR10_REG = 0x5A;
    NR11_REG = 0x81;
    NR12_REG = 0x91;
    NR13_REG = 0xBD;
    NR14_REG = 0xC6;
    channel1Timer = 10;  
}

void play_reload_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank); 
    NR10_REG = 0x24;
    NR11_REG = 0x00;
    NR12_REG = 0xA0;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
    channel1Timer = 10;  
}

void play_take_damage_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank); 
    NR10_REG = 0x6C;
    NR11_REG = 0x82;
    NR12_REG = 0x90;
    NR13_REG = 0x55;
    NR14_REG = 0xC6;
    channel1Timer = 20;
}

void play_carriage_damaged_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH4, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR41_REG = 0x00;
    NR42_REG = 0xA0;
    NR43_REG = 0x55;
    NR44_REG = 0xC0;   
    channel4Timer = 30;  
}

void play_beep_sound() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);  
    SWITCH_ROM_MBC1(bank);  
    NR10_REG = 0x23;
    NR11_REG = 0x81;
    NR12_REG = 0x83;
    NR13_REG = 0xDF;
    NR14_REG = 0x86;
    channel1Timer = 5; 
}

void mute_music() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH2, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH3, HT_CH_MUTE);
    hUGE_mute_channel(HT_CH4, HT_CH_MUTE);      
    SWITCH_ROM_MBC1(bank);   
}

void enable_music() {
    UINT8 bank = _current_bank;
    SWITCH_ROM_MBC1(3);
    hUGE_mute_channel(HT_CH1, HT_CH_PLAY);
    hUGE_mute_channel(HT_CH2, HT_CH_PLAY);
    hUGE_mute_channel(HT_CH3, HT_CH_PLAY);
    hUGE_mute_channel(HT_CH4, HT_CH_PLAY);      
    SWITCH_ROM_MBC1(bank);   
}