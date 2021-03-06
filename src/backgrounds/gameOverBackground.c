const int GameOverBackground_tile_map_size = 0x0168;
const int GameOverBackground_tile_map_width = 0x14;
const int GameOverBackground_tile_map_height = 0x12;

const int GameOverBackground_tile_data_size = 0x0390;
const int GameOverBackground_tile_count = 0x39;

const unsigned char GameOverBackground_map_data[] ={
    0x16, 0x00, 0xCD, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 
    0x0E, 0x85, 0xDB, 0xFF, 0xCD, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 
    0x1A, 0x1B, 0x1C, 0x85, 0xC7, 0xFF, 0xCD, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 
    0x26, 0x27, 0x28, 0x29, 0x2A, 0x85, 0xB3, 0xFF, 0xCD, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x7F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x86, 0x9F, 0xFE, 0x00
};

const unsigned char GameOverBackground_tile_data[] ={
    0x13, 0xFF, 0xCB, 0xF8, 0xFC, 0xF0, 0xF8, 0xF0, 0xF0, 0xE0, 0xF0, 0xE0, 0xF0, 0xF0, 0xE0, 0x83, 
    0xE0, 0xFF, 0xC1, 0x5F, 0x2F, 0x44, 0x07, 0x0F, 0x83, 0xD0, 0xFF, 0xCB, 0xDF, 0xE7, 0xC7, 0xE7, 
    0xE7, 0xC7, 0xE3, 0xC7, 0xE3, 0xC7, 0xC7, 0xC3, 0x83, 0xC0, 0xFF, 0xC1, 0xEE, 0xF1, 0x44, 0xF0, 
    0xE0, 0x83, 0xB0, 0xFF, 0xC1, 0xFD, 0xFE, 0x03, 0xFC, 0xC5, 0x78, 0xFC, 0x78, 0xFC, 0xFC, 0x78, 
    0x83, 0xA0, 0xFF, 0xC1, 0xD7, 0x38, 0x44, 0x30, 0x18, 0x84, 0x90, 0xFF, 0x0A, 0x03, 0x86, 0x80, 
    0xFF, 0xC2, 0xFE, 0xFC, 0xFE, 0x42, 0xFE, 0xFC, 0x83, 0x70, 0xFF, 0xC4, 0x8F, 0x07, 0x03, 0x03, 
    0x43, 0x06, 0x01, 0x84, 0x60, 0xFF, 0x02, 0x82, 0xC2, 0xC2, 0x82, 0x80, 0x04, 0x82, 0x83, 0x50, 
    0xFF, 0xC8, 0xEB, 0x1C, 0x08, 0x0C, 0x08, 0x0C, 0x4C, 0x0C, 0x28, 0x02, 0x0C, 0x84, 0x40, 0xFF, 
    0xC3, 0x01, 0x01, 0x01, 0x00, 0x83, 0xFC, 0xFF, 0x86, 0xD0, 0xFF, 0xC7, 0xBF, 0xC0, 0xC0, 0x80, 
    0xC0, 0x80, 0xC4, 0x80, 0x83, 0xFA, 0xFF, 0x83, 0x20, 0xFF, 0xC5, 0x7F, 0xFF, 0x3F, 0x7F, 0x1F, 
    0x3F, 0x42, 0x3F, 0x1F, 0xC2, 0xE0, 0xF0, 0xE1, 0x45, 0xF3, 0xE7, 0xC9, 0xF3, 0x07, 0x0F, 0x87, 
    0xCF, 0xC7, 0xCF, 0xE7, 0xCF, 0xC7, 0x86, 0xF7, 0xFE, 0xD2, 0xC7, 0xC3, 0x87, 0xC3, 0x93, 0xC3, 
    0xC1, 0x93, 0xC9, 0x93, 0x9B, 0x91, 0x93, 0x99, 0x3B, 0x99, 0xF0, 0xE0, 0xE0, 0x02, 0xF8, 0x42, 
    0xF9, 0xF8, 0xC0, 0xF8, 0x02, 0xF9, 0xC0, 0xFC, 0x04, 0x78, 0xC2, 0x32, 0x78, 0x32, 0x84, 0xFB, 
    0xFF, 0xC4, 0x30, 0x32, 0x38, 0x10, 0x10, 0x43, 0x7C, 0x7E, 0xD4, 0x7C, 0xFE, 0x7C, 0xFE, 0x7C, 
    0x03, 0x03, 0x83, 0x73, 0x73, 0xF3, 0x63, 0xF3, 0x73, 0xF3, 0x7F, 0xF3, 0xFF, 0xFF, 0xBF, 0x5F, 
    0x46, 0xFE, 0xFC, 0xC5, 0xFD, 0xFE, 0x01, 0x01, 0x79, 0x71, 0x44, 0x79, 0xF9, 0xC6, 0x7D, 0xF9, 
    0x82, 0x82, 0xAA, 0xC7, 0xCF, 0x02, 0xE7, 0xEB, 0xF7, 0xE7, 0xE7, 0xE7, 0xF3, 0xE7, 0xF2, 0xE7, 
    0x08, 0x0C, 0x0D, 0x9E, 0x3F, 0x9E, 0x3F, 0x9E, 0x9F, 0x3E, 0x9F, 0x3E, 0x3F, 0x3E, 0x3F, 0x3E, 
    0x01, 0x01, 0x40, 0x39, 0x78, 0x39, 0x79, 0x39, 0x79, 0x39, 0x3F, 0x79, 0x3F, 0x7F, 0x1F, 0x2F, 
    0xC0, 0x80, 0x81, 0xE6, 0x0B, 0xE7, 0x84, 0x2A, 0xFF, 0x43, 0x9F, 0x3F, 0xC2, 0x9F, 0x9F, 0x3F, 
    0x87, 0x24, 0xFF, 0xE7, 0xF7, 0xE3, 0xE7, 0xF3, 0xE3, 0xF3, 0xE2, 0xF1, 0xF7, 0x8F, 0x87, 0x8F, 
    0xC7, 0x8F, 0xE7, 0xCF, 0xE7, 0xCF, 0xE6, 0xCF, 0xC6, 0xCF, 0x46, 0x8C, 0xB9, 0x19, 0xA1, 0x19, 
    0x80, 0x01, 0x38, 0x01, 0x3D, 0x38, 0x79, 0x3C, 0xB8, 0x7C, 0x08, 0x50, 0x09, 0xF9, 0xCE, 0xFB, 
    0xF9, 0xF9, 0xF9, 0x30, 0x60, 0x32, 0x32, 0x86, 0x32, 0x86, 0x32, 0x36, 0x82, 0x22, 0x04, 0x86, 
    0xC1, 0xC6, 0x00, 0x85, 0x2A, 0xFF, 0xC0, 0xFE, 0x86, 0x1C, 0xFF, 0xC7, 0x14, 0x38, 0x7F, 0x1F, 
    0x3F, 0xFF, 0x77, 0xFF, 0x85, 0x1E, 0xFF, 0xC5, 0x73, 0xF3, 0x33, 0x03, 0xFE, 0xFC, 0x87, 0x46, 
    0xFE, 0x85, 0x40, 0xFE, 0x45, 0x79, 0xF9, 0xD3, 0xF1, 0x79, 0x21, 0x01, 0xF6, 0xE3, 0xE6, 0xF3, 
    0xF3, 0xF2, 0xF3, 0xF2, 0xF0, 0xF2, 0xF8, 0xF2, 0xFA, 0xF0, 0xF0, 0xF8, 0x42, 0x7F, 0x3E, 0xD0, 
    0x3F, 0x7E, 0x7F, 0x7E, 0x7F, 0x7E, 0xFF, 0x7E, 0xFC, 0x7C, 0x3F, 0x0F, 0x4F, 0x3F, 0x7B, 0x3F, 
    0x78, 0x86, 0x1C, 0xFF, 0xC1, 0x08, 0x01, 0x03, 0xE0, 0xC1, 0xE4, 0xE6, 0x43, 0xE6, 0xE7, 0xC7, 
    0xC3, 0x80, 0x3F, 0x3F, 0x7F, 0x7F, 0x3F, 0x7F, 0x42, 0x7F, 0x3F, 0xC3, 0x7F, 0x2F, 0x2F, 0x0F, 
    0x85, 0x6A, 0xFD, 0xC5, 0xE0, 0xF0, 0xF8, 0xF0, 0xF8, 0xF8, 0x83, 0xD3, 0xFD, 0x45, 0x06, 0x0C, 
    0xC4, 0x7F, 0xFF, 0xFF, 0xFF, 0x09, 0x44, 0x10, 0x08, 0xC0, 0x10, 0x83, 0x24, 0xFD, 0x45, 0x30, 
    0x60, 0x83, 0x14, 0xFD, 0xD0, 0xCC, 0x00, 0x84, 0x48, 0x84, 0x48, 0xCC, 0x48, 0xCC, 0x48, 0xDC, 
    0x48, 0xFB, 0xFF, 0xFF, 0xFF, 0x31, 0x44, 0x18, 0x30, 0x84, 0x64, 0xFD, 0x87, 0x65, 0xFD, 0xC3, 
    0x0B, 0x03, 0x0B, 0x13, 0x86, 0x67, 0xFD, 0xC0, 0xFC, 0x84, 0x1C, 0xFF, 0xC1, 0xFE, 0xFE, 0x87, 
    0x95, 0xFD, 0xCD, 0x01, 0x01, 0x01, 0x41, 0x01, 0x01, 0x03, 0x07, 0x03, 0x8F, 0xFF, 0xFF, 0xFF, 
    0xF0, 0x06, 0xF8, 0xC8, 0xFC, 0xF8, 0xFD, 0xF8, 0xFD, 0xFF, 0xFF, 0xFF, 0x7C, 0x83, 0x0A, 0xFD, 
    0xC5, 0xFC, 0xFC, 0xFC, 0xF8, 0xFC, 0xFC, 0x84, 0x34, 0xFD, 0xC0, 0x81, 0x42, 0x01, 0x00, 0xCC, 
    0x01, 0x04, 0x01, 0x00, 0x0D, 0xBF, 0xFF, 0xFF, 0xFF, 0xD3, 0x80, 0xC3, 0x80, 0x42, 0xC2, 0x81, 
    0xC1, 0xC3, 0x81, 0x83, 0x84, 0xFC, 0x09, 0x0F, 0xC5, 0x1F, 0x0F, 0x9F, 0xFF, 0xFF, 0xFF, 0x00
};
