const int adrianjgLogo_tile_map_size = 0x0168;
const int adrianjgLogo_tile_map_width = 0x14;
const int adrianjgLogo_tile_map_height = 0x12;

const int adrianjgLogo_tile_data_size = 0x04F0;
const int adrianjgLogo_tile_count = 0x4F;

const unsigned char adrianjgLogo_map_data[] ={
    0x3F, 0x00, 0xA3, 0xC0, 0xFF, 0xC0, 0x01, 0x11, 0x02, 0xCB, 0x03, 0x01, 0x04, 0x05, 0x06, 0x00, 
    0x07, 0x00, 0x08, 0x09, 0x0A, 0x0B, 0x83, 0x7D, 0xFF, 0xED, 0x0C, 0x0D, 0x0E, 0x0F, 0x03, 0x01, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x00, 0x1D, 0x1E, 
    0x1F, 0x20, 0x03, 0x01, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 
    0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x03, 0x01, 0x11, 0x33, 0xC0, 0x03, 0x60, 0x00, 0x00, 0xC5, 
    0x34, 0x35, 0x36, 0x00, 0x35, 0x36, 0x8B, 0xF0, 0xFE, 0xCB, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 
    0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x87, 0xD8, 0xFE, 0xCB, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 
    0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0xAB, 0xC4, 0xFE, 0x00
};

const unsigned char adrianjgLogo_tile_data[] ={
    0x0F, 0x00, 0x47, 0x07, 0x00, 0x42, 0xFF, 0x00, 0x89, 0xDA, 0xFF, 0x47, 0xE0, 0x00, 0x83, 0xC0, 
    0xFF, 0xC2, 0x01, 0x00, 0x00, 0x02, 0x01, 0xC2, 0x03, 0x01, 0x01, 0x02, 0x03, 0x83, 0xB0, 0xFF, 
    0xC1, 0xFF, 0xFE, 0x08, 0xFF, 0xC0, 0xEF, 0x89, 0xA0, 0xFF, 0xC1, 0x80, 0x00, 0x03, 0x80, 0xC1, 
    0x00, 0x00, 0x0D, 0x3F, 0x85, 0x80, 0xFF, 0xC0, 0x01, 0x83, 0xBC, 0xFF, 0x86, 0x75, 0xFF, 0xC2, 
    0x48, 0x30, 0xF8, 0x04, 0xFC, 0xC3, 0xF8, 0xFC, 0x48, 0x30, 0x86, 0x62, 0xFF, 0x83, 0xA6, 0xFF, 
    0xC2, 0x07, 0x0F, 0x07, 0x85, 0x54, 0xFF, 0xC6, 0xF8, 0x00, 0xE0, 0xF0, 0xC0, 0xE0, 0xC0, 0x83, 
    0xB5, 0xFF, 0x86, 0x43, 0xFF, 0x45, 0x3F, 0x1F, 0x86, 0x96, 0xFF, 0xC7, 0x00, 0x80, 0x01, 0x81, 
    0x03, 0x83, 0x07, 0x8F, 0x84, 0xCC, 0xFF, 0xC3, 0x1B, 0x07, 0x3F, 0x7F, 0x85, 0x6E, 0xFF, 0xC1, 
    0xF8, 0xF0, 0x83, 0x10, 0xFF, 0xC1, 0x30, 0xC0, 0x07, 0xF8, 0xC4, 0x08, 0x00, 0x07, 0x03, 0x03, 
    0x02, 0x07, 0xC2, 0x0F, 0x07, 0x07, 0x02, 0x0F, 0xCA, 0x1F, 0x0F, 0x0F, 0x1F, 0xEF, 0xEF, 0xCF, 
    0xEF, 0xEF, 0xC7, 0xCF, 0x03, 0xC7, 0xC6, 0x87, 0xC7, 0x83, 0xFF, 0xFF, 0xC0, 0x80, 0x03, 0xC0, 
    0xCD, 0xE0, 0xC0, 0xC0, 0xE0, 0xE1, 0xE0, 0xF0, 0xE1, 0xE0, 0xF1, 0x17, 0x0E, 0x3F, 0x3F, 0x02, 
    0x7F, 0xC3, 0xFF, 0xFF, 0xFF, 0xFE, 0x83, 0x5D, 0xFF, 0xC4, 0xF8, 0x3F, 0x3F, 0xFF, 0xBF, 0x85, 
    0x12, 0xFF, 0xC1, 0x3F, 0x7F, 0x83, 0x26, 0xFF, 0x0F, 0x1F, 0xC5, 0x90, 0x8C, 0x9C, 0xBC, 0xFC, 
    0xBC, 0x83, 0x2F, 0xFF, 0xC1, 0xC0, 0xC0, 0x83, 0x00, 0xFF, 0x0F, 0xFC, 0xC1, 0x19, 0x07, 0x42, 
    0x7F, 0x3F, 0xD7, 0x60, 0x00, 0x06, 0x01, 0x3F, 0x1F, 0x3F, 0x7F, 0x20, 0xC0, 0xF8, 0xF0, 0xFC, 
    0xF8, 0xFC, 0xFC, 0x7E, 0x7C, 0x7E, 0xFC, 0xFE, 0xFC, 0xFE, 0xFC, 0x0F, 0x3F, 0xC1, 0x2A, 0x1C, 
    0x84, 0x83, 0xFF, 0xC2, 0xFF, 0x9F, 0x1F, 0x42, 0x1F, 0x0F, 0x84, 0xA6, 0xFE, 0xC1, 0x80, 0x80, 
    0x43, 0x80, 0xC0, 0xC0, 0x80, 0x46, 0x3F, 0x1F, 0xCD, 0x1F, 0x3F, 0x8F, 0x0F, 0x8F, 0x0F, 0x9F, 
    0x0F, 0x9F, 0x0F, 0x8F, 0x1F, 0x8F, 0x1F, 0x83, 0xF8, 0xFF, 0xCF, 0xF0, 0xE0, 0xE0, 0xC0, 0xCF, 
    0xC7, 0xCF, 0xC7, 0x8F, 0xC7, 0x8F, 0xC7, 0xCF, 0xC7, 0xE0, 0xC0, 0x83, 0x00, 0xFE, 0x44, 0xFE, 
    0xFC, 0xC2, 0xFE, 0x7C, 0x1F, 0x83, 0xB4, 0xFE, 0xCA, 0x3F, 0x3F, 0x3F, 0x7F, 0x3F, 0x7E, 0x7F, 
    0x7E, 0x7E, 0x00, 0x00, 0x87, 0x36, 0xFE, 0x04, 0x01, 0xCC, 0x00, 0x00, 0x00, 0xF0, 0xF1, 0xF9, 
    0xF0, 0xF1, 0xF8, 0xF8, 0xF8, 0xFC, 0xF8, 0x83, 0x5A, 0xFE, 0xC1, 0x00, 0x00, 0x83, 0xF6, 0xFF, 
    0xC9, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x15, 0x0E, 0x86, 0x22, 0xFE, 0x84, 0x92, 
    0xFE, 0xC1, 0x7F, 0xBF, 0x83, 0x22, 0xFE, 0x8D, 0xF0, 0xFE, 0x85, 0x54, 0xFF, 0x09, 0x80, 0xC1, 
    0x00, 0x00, 0x8D, 0xF0, 0xFE, 0xC3, 0x00, 0x00, 0xF8, 0x7C, 0x83, 0xA4, 0xFF, 0x83, 0xB0, 0xFF, 
    0xCB, 0x3F, 0x7F, 0x2A, 0x1C, 0x00, 0x00, 0x7E, 0x7C, 0x7E, 0x7C, 0xFE, 0x7C, 0x83, 0xF6, 0xFE, 
    0xC3, 0xBE, 0x7C, 0x3E, 0x7C, 0x91, 0xC2, 0xFD, 0x46, 0x1F, 0x0F, 0xC1, 0x00, 0x00, 0x46, 0xC0, 
    0x80, 0x83, 0x22, 0xFD, 0xC1, 0x08, 0x00, 0x07, 0x0F, 0xC1, 0x0D, 0x03, 0x84, 0x82, 0xFD, 0xC2, 
    0x7F, 0xFE, 0xFF, 0x02, 0xFE, 0xC8, 0xFC, 0xFC, 0xF8, 0xA0, 0xC0, 0x00, 0x00, 0x8F, 0x0F, 0x83, 
    0x03, 0xFE, 0xC2, 0x07, 0x03, 0x03, 0x86, 0x7F, 0xFD, 0xC3, 0xE0, 0xE0, 0xF8, 0xF0, 0x85, 0x42, 
    0xFD, 0xC6, 0x7F, 0xFF, 0x33, 0x0F, 0x00, 0x00, 0xFE, 0x86, 0x82, 0xFF, 0xC4, 0xFE, 0xFC, 0xF8, 
    0xFC, 0x60, 0x89, 0x8D, 0xFD, 0x83, 0x1A, 0xFD, 0x8E, 0xE6, 0xFC, 0xC5, 0x00, 0x00, 0x1E, 0x0C, 
    0x1E, 0x0C, 0x8B, 0xB0, 0xFC, 0xC1, 0x01, 0x00, 0x84, 0xCD, 0xFE, 0x89, 0xFE, 0xFC, 0xC0, 0xC0, 
    0x85, 0x90, 0xFE, 0xCB, 0x02, 0x01, 0x07, 0x03, 0x04, 0x00, 0x03, 0x00, 0x03, 0x07, 0x07, 0x06, 
    0x83, 0x80, 0xFC, 0xCB, 0xA0, 0xC0, 0xF3, 0xF1, 0x73, 0x33, 0x7B, 0xF3, 0xFB, 0xF3, 0x7B, 0x33, 
    0x83, 0xBC, 0xFF, 0xCB, 0x7E, 0xCC, 0xFE, 0xFC, 0xCE, 0x9C, 0x9E, 0x8C, 0x9E, 0x8C, 0x8E, 0x9C, 
    0x83, 0xE8, 0xFC, 0xC1, 0xF5, 0xED, 0x03, 0xFD, 0xC0, 0xF1, 0x04, 0xE1, 0xCF, 0x80, 0xC0, 0x00, 
    0x00, 0xC5, 0xC3, 0xCF, 0xC7, 0xC8, 0xC0, 0xC6, 0xC1, 0xC7, 0xCF, 0xCE, 0xCC, 0x83, 0x40, 0xFC, 
    0xC1, 0x47, 0x87, 0x02, 0xE7, 0xC6, 0x67, 0xF7, 0xE7, 0xF7, 0xE7, 0xF7, 0x67, 0x83, 0xB8, 0xFC, 
    0xC5, 0xE9, 0x31, 0xF9, 0xF9, 0x9D, 0x39, 0x42, 0x3D, 0x19, 0x83, 0xD0, 0xFF, 0xC4, 0xC0, 0xC3, 
    0xCF, 0xC7, 0xCF, 0x06, 0xCE, 0x84, 0xBE, 0xFC, 0xCA, 0x30, 0xF8, 0xF0, 0x38, 0x70, 0x78, 0x30, 
    0x78, 0x30, 0x3B, 0x71, 0x83, 0x00, 0xFC, 0xC5, 0x06, 0x03, 0x0F, 0x0F, 0x0C, 0x1C, 0x83, 0x46, 
    0xFD, 0xC1, 0x1C, 0x9C, 0x83, 0xF0, 0xFB, 0xCA, 0x85, 0x03, 0xCF, 0xC7, 0xEE, 0xCE, 0xCF, 0xE7, 
    0xC5, 0xE3, 0x09, 0x84, 0xE1, 0xFB, 0xC4, 0x40, 0x80, 0xC0, 0xC0, 0x40, 0x83, 0x41, 0xFF, 0xC5, 
    0xC0, 0xE0, 0xC0, 0x07, 0x07, 0x04, 0x84, 0x1C, 0xFC, 0x87, 0xC8, 0xFB, 0xC2, 0xFB, 0xF1, 0xF9, 
    0x87, 0x5A, 0xFC, 0x84, 0xB5, 0xFB, 0xC2, 0xFE, 0xFC, 0x3E, 0x84, 0x6C, 0xFF, 0x87, 0xA8, 0xFB, 
    0x83, 0x4B, 0xFF, 0x8B, 0x9C, 0xFB, 0xC3, 0xCF, 0xCF, 0xC9, 0xC6, 0x8B, 0x8C, 0xFB, 0x83, 0x4C, 
    0xFF, 0x8B, 0x7C, 0xFB, 0x83, 0x4A, 0xFF, 0x83, 0x94, 0xFD, 0xC2, 0x07, 0x03, 0x02, 0x84, 0xB4, 
    0xFB, 0xC3, 0xCF, 0xC7, 0xC5, 0xC3, 0x83, 0x7E, 0xFC, 0xC2, 0xC7, 0x87, 0x83, 0x84, 0x00, 0xFC, 
    0xCA, 0xFB, 0xF3, 0xFB, 0x31, 0x38, 0x70, 0xF0, 0x70, 0xE0, 0xE0, 0x40, 0x84, 0xFF, 0xFB, 0xC3, 
    0xDF, 0x8F, 0x03, 0x87, 0x8D, 0xA0, 0xFF, 0xC0, 0x4A, 0x8C, 0xF0, 0xFF, 0xC0, 0xC0, 0x85, 0xFB, 
    0xFD, 0x88, 0x19, 0xFB, 0x00
};