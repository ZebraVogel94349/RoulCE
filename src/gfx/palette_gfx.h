// Converted using ConvPNG
// This file contains all the graphics sources for easier inclusion in a project
#ifndef __palette_gfx__
#define __palette_gfx__
#include <stdint.h>

#define palette_gfx_transparent_color_index 0

#define ro_width 128
#define ro_height 128
#define ro_size 16386
extern uint8_t ro_data[16386];
#define ro ((gfx_sprite_t*)ro_data)
#define pfeil_width 32
#define pfeil_height 32
#define pfeil_size 1026
extern uint8_t pfeil_data[1026];
#define pfeil ((gfx_sprite_t*)pfeil_data)
#define sizeof_palette_gfx_pal 500
extern uint16_t palette_gfx_pal[250];

#endif
