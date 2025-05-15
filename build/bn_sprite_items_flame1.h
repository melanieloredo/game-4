#ifndef BN_SPRITE_ITEMS_FLAME1_H
#define BN_SPRITE_ITEMS_FLAME1_H

#include "bn_sprite_item.h"

//{{BLOCK(flame1_bn_gfx)

//======================================================================
//
//	flame1_bn_gfx, 16x160@8, 
//	+ palette 32 entries, not compressed
//	+ 40 tiles not compressed
//	Total size: 64 + 2560 = 2624
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FLAME1_BN_GFX_H
#define GRIT_FLAME1_BN_GFX_H

#define flame1_bn_gfxTilesLen 2560
extern const bn::tile flame1_bn_gfxTiles[80];

#define flame1_bn_gfxPalLen 64
extern const bn::color flame1_bn_gfxPal[32];

#endif // GRIT_FLAME1_BN_GFX_H

//}}BLOCK(flame1_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item flame1(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(flame1_bn_gfxTiles, 80), bpp_mode::BPP_8, compression_type::NONE, 5), 
            sprite_palette_item(span<const color>(flame1_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

