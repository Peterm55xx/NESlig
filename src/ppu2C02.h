#ifndef PPU2C02_H_INCLUDED
#define PPU2C02_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdint.h>

static const uint32_t pixelWidth = 2;
static const uint32_t pixelHeight = 2;

static const uint32_t ppu_colors[64] =
{
0x757575, 0x271B8F, 0x0000AB, 0x47009F, 0x8F0077, 0xAB0013, 0xA70000, 0x7F0B00, 0x432F00, 0x004700, 0x005100, 0x003F17, 0x1B3F5F, 0x000000, 0x000000, 0x000000,
0xBCBCBC, 0x0073EF, 0x233BEF, 0x8300F3, 0xBF00BF, 0xE7005B, 0xDB2B00, 0xCB4F0F, 0x8B7300, 0x009700, 0x00AB00, 0x00933B, 0x00838B, 0x000000, 0x000000, 0x000000,
0xFFFFFF, 0x3FBFFF, 0x5F97FF, 0xA78BFD, 0xF77BFF, 0xFF77B7, 0xFF7763, 0xFF9B3B, 0xF3BF3F, 0x83D313, 0x4FDF4B, 0x58F898, 0x00EBDB, 0x000000, 0x000000, 0x000000,
0xFFFFFF, 0xABE7FF, 0xC7D7FF, 0xD7CBFF, 0xFFC7FF, 0xFFC7DB, 0xFFBFB3, 0xFFDBAB, 0xFFE7A3, 0xE3FFA3, 0xABF3BF, 0xB3FFCF, 0x9FFFF3, 0x000000, 0x000000, 0x000000
};

//struct for sprites on the scanline (for secondary OAM)
struct PPUsprite {
    uint8_t shifts_remaining;
    uint8_t sprite_index;
    uint8_t byte2;

    uint8_t shift_register_0;
    uint8_t shift_register_1;
    uint8_t attribute;
    uint8_t x;
};
typedef struct PPUsprite PPUsprite;

//struct to store the state of the PPU
struct PPU2C02state {
    uint8_t odd_frame;
    uint16_t scanline;
    uint16_t dot;

    uint8_t nmi_occurred;

    //PPU register values
    uint8_t nmi_output;
    uint8_t sprite_zero_hit;

    //more accurate ppu
    uint16_t nametable_base;

    uint16_t bitmap_shift_0_latch;
    uint16_t bitmap_shift_1_latch;

    uint16_t bitmap_shift_0;
    uint16_t bitmap_shift_1;


    uint16_t AT_shift_0_latch;
    uint16_t AT_shift_1_latch;
    uint16_t AT_shift_0;
    uint16_t AT_shift_1;

    uint8_t num_sprites;
    PPUsprite sprites[8];
};
typedef struct PPU2C02state PPU2C02state;
extern PPU2C02state PPU_state;

//initalize the PPU (ppu2C02.c)
int initPPU2C02(PPU2C02state *state);

//Ticking (ppu2C02.c)
uint8_t PPUcycle(PPU2C02state *state, SDL_Surface *screenSurface);
void handleVisibleScanline(PPU2C02state *state);
void horinc();
void verinc();

uint8_t rendering_enabled();

//Rendering stuff (ppu2C02rendering.c)
void setPixelColor(SDL_Surface* screenSurface, int x, int y, uint32_t color);
void renderPixel(SDL_Surface* screenSurface, PPU2C02state *state);
void updatePPUrenderingData(PPU2C02state *state);

//Loading stuff (ppu2C02rendering.c)
uint16_t getSpritePaletteBase(uint8_t attribute_value);
uint16_t getBackgroundPaletteBase(uint16_t attribute_value);

void fetchAttribute(PPU2C02state *state);
uint8_t getAttributeTableValue(uint16_t attribute_address, uint8_t x, uint8_t y);

void loadScanlineSprites(PPU2C02state *state);
int getActiveSpriteIndex(PPU2C02state *state);

#endif // PPU2C02_H_INCLUDED
