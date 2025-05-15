#ifndef BN_SPRITE_ITEMS_HEART_H
#define BN_SPRITE_ITEMS_HEART_H

#include "bn_sprite_item.h"

//{{BLOCK(heart_bn_gfx)

//======================================================================
//
//	heart_bn_gfx, 32x96@8, 
//	+ palette 48 entries, not compressed
//	+ 48 tiles not compressed
//	Total size: 96 + 3072 = 3168
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HEART_BN_GFX_H
#define GRIT_HEART_BN_GFX_H

#define heart_bn_gfxTilesLen 3072
extern const bn::tile heart_bn_gfxTiles[96];

#define heart_bn_gfxPalLen 96
extern const bn::color heart_bn_gfxPal[48];

#endif // GRIT_HEART_BN_GFX_H

//}}BLOCK(heart_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item heart(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(heart_bn_gfxTiles, 96), bpp_mode::BPP_8, compression_type::NONE, 3), 
            sprite_palette_item(span<const color>(heart_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

