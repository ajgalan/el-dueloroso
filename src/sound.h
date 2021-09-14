#ifndef __sound_h
#define __sound_h

extern UINT8 playingMusic;
extern UINT8 channel1Timer;
extern UINT8 channel2Timer;
extern UINT8 channel3Timer;
extern UINT8 channel4Timer;

void play_music();
void stop_music();
void set_title_song();
void set_shooting_song();
void set_riding_song();
void set_win_song();
void set_lose_song();
void play_shoot_sound();
void play_explosion_sound();
void play_empty_sound();
void play_reload_sound();
void play_almost_exploding_sound();
void play_take_damage_sound();
void play_carriage_damaged_sound();
void play_beep_sound();
void mute_music();
void enable_music();

#endif