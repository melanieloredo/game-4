#ifndef BN_SPRITE_ITEMS_HELP_BUTTON_H
#define BN_SPRITE_ITEMS_HELP_BUTTON_H

#include "bn_sprite_item.h"

//{{BLOCK(help_button_bn_gfx)

//======================================================================
//
//	help_button_bn_gfx, 64x64@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 32 + 2048 = 2080
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HELP_BUTTON_BN_GFX_H
#define GRIT_HELP_BUTTON_BN_GFX_H

#define help_button_bn_gfxTilesLen 2048
extern const bn::tile help_button_bn_gfxTiles[64];

#define help_button_bn_gfxPalLen 32
extern const bn::color help_button_bn_gfxPal[16];

#endif // GRIT_HELP_BUTTON_BN_GFX_H

//}}BLOCK(help_button_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item help_button(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(help_button_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(help_button_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

