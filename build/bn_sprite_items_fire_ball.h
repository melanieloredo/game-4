#ifndef BN_SPRITE_ITEMS_FIRE_BALL_H
#define BN_SPRITE_ITEMS_FIRE_BALL_H

#include "bn_sprite_item.h"

//{{BLOCK(fire_ball_bn_gfx)

//======================================================================
//
//	fire_ball_bn_gfx, 8x8@4, 
//	+ palette 16 entries, not compressed
//	+ 1 tiles not compressed
//	Total size: 32 + 32 = 64
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FIRE_BALL_BN_GFX_H
#define GRIT_FIRE_BALL_BN_GFX_H

#define fire_ball_bn_gfxTilesLen 32
extern const bn::tile fire_ball_bn_gfxTiles[1];

#define fire_ball_bn_gfxPalLen 32
extern const bn::color fire_ball_bn_gfxPal[16];

#endif // GRIT_FIRE_BALL_BN_GFX_H

//}}BLOCK(fire_ball_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item fire_ball(sprite_shape_size(sprite_shape::SQUARE, sprite_size::SMALL), 
            sprite_tiles_item(span<const tile>(fire_ball_bn_gfxTiles, 1), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(fire_ball_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

