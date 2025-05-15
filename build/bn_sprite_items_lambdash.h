#ifndef BN_SPRITE_ITEMS_LAMBDASH_H
#define BN_SPRITE_ITEMS_LAMBDASH_H

#include "bn_sprite_item.h"

//{{BLOCK(lambdash_bn_gfx)

//======================================================================
//
//	lambdash_bn_gfx, 64x1024@4, 
//	+ palette 16 entries, not compressed
//	+ 1024 tiles not compressed
//	Total size: 32 + 32768 = 32800
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LAMBDASH_BN_GFX_H
#define GRIT_LAMBDASH_BN_GFX_H

#define lambdash_bn_gfxTilesLen 32768
extern const bn::tile lambdash_bn_gfxTiles[1024];

#define lambdash_bn_gfxPalLen 32
extern const bn::color lambdash_bn_gfxPal[16];

#endif // GRIT_LAMBDASH_BN_GFX_H

//}}BLOCK(lambdash_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item lambdash(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(lambdash_bn_gfxTiles, 1024), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(lambdash_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

