#ifndef BN_SPRITE_ITEMS_COIN_ANIMATED_H
#define BN_SPRITE_ITEMS_COIN_ANIMATED_H

#include "bn_sprite_item.h"

//{{BLOCK(coin_animated_bn_gfx)

//======================================================================
//
//	coin_animated_bn_gfx, 16x128@8, 
//	+ palette 32 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 64 + 2048 = 2112
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COIN_ANIMATED_BN_GFX_H
#define GRIT_COIN_ANIMATED_BN_GFX_H

#define coin_animated_bn_gfxTilesLen 2048
extern const bn::tile coin_animated_bn_gfxTiles[64];

#define coin_animated_bn_gfxPalLen 64
extern const bn::color coin_animated_bn_gfxPal[32];

#endif // GRIT_COIN_ANIMATED_BN_GFX_H

//}}BLOCK(coin_animated_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item coin_animated(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(coin_animated_bn_gfxTiles, 64), bpp_mode::BPP_8, compression_type::NONE, 8), 
            sprite_palette_item(span<const color>(coin_animated_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

