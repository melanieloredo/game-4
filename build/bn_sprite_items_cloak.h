#ifndef BN_SPRITE_ITEMS_CLOAK_H
#define BN_SPRITE_ITEMS_CLOAK_H

#include "bn_sprite_item.h"

//{{BLOCK(cloak_bn_gfx)

//======================================================================
//
//	cloak_bn_gfx, 32x512@4, 
//	+ palette 16 entries, not compressed
//	+ 256 tiles not compressed
//	Total size: 32 + 8192 = 8224
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CLOAK_BN_GFX_H
#define GRIT_CLOAK_BN_GFX_H

#define cloak_bn_gfxTilesLen 8192
extern const bn::tile cloak_bn_gfxTiles[256];

#define cloak_bn_gfxPalLen 32
extern const bn::color cloak_bn_gfxPal[16];

#endif // GRIT_CLOAK_BN_GFX_H

//}}BLOCK(cloak_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item cloak(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(cloak_bn_gfxTiles, 256), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(cloak_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

