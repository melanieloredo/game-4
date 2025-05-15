#ifndef BN_SPRITE_ITEMS_BAT_H
#define BN_SPRITE_ITEMS_BAT_H

#include "bn_sprite_item.h"

//{{BLOCK(bat_bn_gfx)

//======================================================================
//
//	bat_bn_gfx, 32x64@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BAT_BN_GFX_H
#define GRIT_BAT_BN_GFX_H

#define bat_bn_gfxTilesLen 1024
extern const bn::tile bat_bn_gfxTiles[32];

#define bat_bn_gfxPalLen 32
extern const bn::color bat_bn_gfxPal[16];

#endif // GRIT_BAT_BN_GFX_H

//}}BLOCK(bat_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item bat(sprite_shape_size(sprite_shape::WIDE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(bat_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 4), 
            sprite_palette_item(span<const color>(bat_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

