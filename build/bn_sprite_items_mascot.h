#ifndef BN_SPRITE_ITEMS_MASCOT_H
#define BN_SPRITE_ITEMS_MASCOT_H

#include "bn_sprite_item.h"

//{{BLOCK(mascot_bn_gfx)

//======================================================================
//
//	mascot_bn_gfx, 64x128@4, 
//	+ palette 16 entries, not compressed
//	+ 128 tiles not compressed
//	Total size: 32 + 4096 = 4128
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MASCOT_BN_GFX_H
#define GRIT_MASCOT_BN_GFX_H

#define mascot_bn_gfxTilesLen 4096
extern const bn::tile mascot_bn_gfxTiles[128];

#define mascot_bn_gfxPalLen 32
extern const bn::color mascot_bn_gfxPal[16];

#endif // GRIT_MASCOT_BN_GFX_H

//}}BLOCK(mascot_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item mascot(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(mascot_bn_gfxTiles, 128), bpp_mode::BPP_4, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(mascot_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

