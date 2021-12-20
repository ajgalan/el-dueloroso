#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>
#include "utils.h"
#include "title.h"
#include "levels.h"
#include "duel.h"
#include "saveData.h"

const UINT8 fadeBlackPalette[4] = {0xE4,0xF9,0xFE,0xFF};
const UINT8 fadeWhitePalette[4] = {0xE4,0x94,0x54,0x00};
const UINT8 konamiCode[] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_B, J_A, J_START};

UINT8 timer = 0;
UINT8 decimalTimer;
UINT8 secondTimer;
UINT8 gameMode;
UINT8 timerFlickerSprites;
UINT8 konamiCodeBuffer[11];
UINT8 backgroundOffset1x;
UINT8 backgroundOffset2x;
UINT8 backgroundOffset3x;
UINT8 backgroundOffset4x;
UINT16 randomSeed;
UINT8 buffer[1024];
UINT8 timeLeft;
UINT8 health;
UINT8 canPause = FALSE;
UINT8 isPaused = FALSE;
UINT16 currentScore = 0;

void performant_delay(UINT8 numloops) {
    UINT8 i = 0;
    for (i = 0; i != numloops; i++){
        wait_vbl_done();
    }     
}

void fade_out_white() {
    UINT8 i = 0;
    for (i = 0; i != 4; i++)
    {
        OBP0_REG = fadeWhitePalette[i];
        BGP_REG = fadeWhitePalette[i];     
        performant_delay(5);
    }
}

void fade_in_white() {
    UINT8 i = 0;
    for (i = 4; i > 0; i--)
    {
        OBP0_REG = fadeWhitePalette[i-1];
        BGP_REG = fadeWhitePalette[i-1]; 
        performant_delay(5);
    }
}

void performant_wait_pad_up() {
    while (joypad())
    {
        wait_vbl_done();
    }
}

BOOLEAN is_konami_code() {
    UINT8 i = 0;
    for (i = 0; i != 11; i++) {
        if (konamiCode[i] != konamiCodeBuffer[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

void add_input_to_konami_code_buffer(UINT8 input) {
    UINT8 i = 0;
    if (input) { 
        for (i = 0; i != 10; i++) {
            konamiCodeBuffer[i] = konamiCodeBuffer[i + 1];
        }
        konamiCodeBuffer[10] = input;
    }    
}

UINT8 generate_random_number_range(UINT8 min, UINT8 max) {
    randomSeed = clock();
    initrand(randomSeed);
    UINT8 rValue = rand();
    UINT8 value = min + (rValue % (max - min));
    return value;
}

UINT8 generate_random_number() {
    return 127 + rand();
}

void hide_all_sprites() {
    UINT8 i = 0;
    for (i = 0; i != 40; i++) {
        move_sprite(i, 0, 0);
        set_sprite_prop(i, 0);
    }
}

void add_time() {
    decimalTimer++;
    secondTimer++;
    if (decimalTimer == 6) {
        decimalTimer = 0;
        timer++;
    }
    if (secondTimer == 60) {
        secondTimer = 0;
    }               
}

void print_integer(UINT8 n, UINT8 x, UINT8 y) {
    UINT8 value = n;
    UINT8 digit;
    UINT8 i = 0;
    for (i = 0; i != 3; i++) {
        digit = value % 10;
        value = value / 10;
        if (i != 0 && digit == 0 && value == 0) {
            set_bkg_tile_xy(x - i + 3, y, 245);
        } else {
            set_bkg_tile_xy(x - i + 3, y, 245 + digit);
        }        
    } 
}

void print_decimal(UINT8 n, UINT8 x, UINT8 y) {
    UINT8 value = n;
    UINT8 digit;
    UINT8 i = 0;
    for (i = 0; i < 3; i++) {
        digit = value % 10;
        value = value / 10;
        if (i > 1 && digit == 0 && value == 0) {
            set_bkg_tile_xy(x + 3 + i , y, 0);
        } else {
            if (i == 0) {
                set_bkg_tile_xy(x - i + 4, y, 245 + digit);  
                set_bkg_tile_xy(x - i + 3, y, 255);
                if (value == 0) {
                    set_bkg_tile_xy(x - i + 2 , y, 245);
                }
            } else {
                set_bkg_tile_xy(x - i + 3, y, 245 + digit);
            }
        }        
    } 
}

BOOLEAN update_score() {
    ENABLE_RAM_MBC1;
    BOOLEAN isUpdated = FALSE;
    if (isPracticeMode == FALSE && isSurvivalMode == FALSE) {
        switch (difficulty)
        {       
            case EASY:
                if (currentScore > easyScore) { 
                    easyScore = currentScore; 
                    isUpdated = TRUE;
                }                
                break;
            case NORMAL:
                if (currentScore > normalScore) {
                    normalScore = currentScore;
                    isUpdated = TRUE;
                }
                break;
            case HARD:
                if (currentScore > hardScore) { 
                    hardScore = currentScore;
                    isUpdated = TRUE;
                }
                break;   
            case EXTREME:   
                if (currentScore > extremeScore) { 
                    extremeScore = currentScore; 
                    isUpdated = TRUE;
                }
                break;  
            default:
                break;        
        }
        
    } else if (isPracticeMode == FALSE) {
         if (roundsWon > survivalScore) { 
            survivalScore = roundsWon; 
            isUpdated = TRUE;
        }        
    }
    DISABLE_RAM_MBC1;
    return isUpdated;
}

void initialize_save_data() {
    ENABLE_RAM_MBC1;
    if (isSaveDataInitialized != TRUE) {
        survivalScore = 0;
        easyScore = 0;
        normalScore = 0;
        hardScore = 0;
        extremeScore = 0;
        isSaveDataInitialized = TRUE;
    }
    DISABLE_RAM_MBC1;    
}

void print_text_bkg(UINT8 x, UINT8 y, unsigned char text[]) {
    UINT8 i = 0;
    while (text[i] != '\0') {
        if (text[i] > 64 && text[i] < 91) {
            set_bkg_tile_xy(i+x, y, text[i] + 149);                     
        }
        i++;
    }
}

void print_text_win(UINT8 x, UINT8 y, unsigned char text[]) {
    UINT8 i = 0;
    while (text[i] != '\0') {
        if (text[i] > 64 && text[i] < 91) {
            set_win_tile_xy(i+x, y, text[i] + 149);                     
        } else if (text[i] == ':') {
            set_win_tile_xy(i+x, y, 0xF2);
        } else if (text[i] == '!') {
            set_win_tile_xy(i+x, y, 0xF3);
        }
        i++;
    }
}