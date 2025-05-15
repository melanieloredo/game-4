#ifndef BN_SPRITE_ITEMS_PLAY_BUTTON_H
#define BN_SPRITE_ITEMS_PLAY_BUTTON_H

#include "bn_sprite_item.h"

//{{BLOCK(play_button_bn_gfx)

//======================================================================
//
//	play_button_bn_gfx, 64x64@8, 
//	+ palette 32 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 64 + 4096 = 4160
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PLAY_BUTTON_BN_GFX_H
#define GRIT_PLAY_BUTTON_BN_GFX_H

#define play_button_bn_gfxTilesLen 4096
extern const bn::tile play_button_bn_gfxTiles[128];

#define play_button_bn_gfxPalLen 64
extern const bn::color play_button_bn_gfxPal[32];

#endif // GRIT_PLAY_BUTTON_BN_GFX_H

//}}BLOCK(play_button_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item play_button(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(play_button_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(play_button_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

