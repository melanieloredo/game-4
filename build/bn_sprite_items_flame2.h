#ifndef BN_SPRITE_ITEMS_FLAME2_H
#define BN_SPRITE_ITEMS_FLAME2_H

#include "bn_sprite_item.h"

//{{BLOCK(flame2_bn_gfx)

//======================================================================
//
//	flame2_bn_gfx, 16x160@8, 
//	+ palette 32 entries, not compressed
//	+ 40 tiles not compressed
//	Total size: 64 + 2560 = 2624
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FLAME2_BN_GFX_H
#define GRIT_FLAME2_BN_GFX_H

#define flame2_bn_gfxTilesLen 2560
extern const bn::tile flame2_bn_gfxTiles[80];

#define flame2_bn_gfxPalLen 64
extern const bn::color flame2_bn_gfxPal[32];

#endif // GRIT_FLAME2_BN_GFX_H

//}}BLOCK(flame2_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item flame2(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(flame2_bn_gfxTiles, 80), bpp_mode::BPP_8, compression_type::NONE, 5), 
            sprite_palette_item(span<const color>(flame2_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

