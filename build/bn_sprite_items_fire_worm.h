#ifndef BN_SPRITE_ITEMS_FIRE_WORM_H
#define BN_SPRITE_ITEMS_FIRE_WORM_H

#include "bn_sprite_item.h"

//{{BLOCK(fire_worm_bn_gfx)

//======================================================================
//
//	fire_worm_bn_gfx, 32x64@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FIRE_WORM_BN_GFX_H
#define GRIT_FIRE_WORM_BN_GFX_H

#define fire_worm_bn_gfxTilesLen 1024
extern const bn::tile fire_worm_bn_gfxTiles[32];

#define fire_worm_bn_gfxPalLen 32
extern const bn::color fire_worm_bn_gfxPal[16];

#endif // GRIT_FIRE_WORM_BN_GFX_H

//}}BLOCK(fire_worm_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item fire_worm(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(fire_worm_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(fire_worm_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

