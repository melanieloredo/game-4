#ifndef BN_REGULAR_BG_ITEMS_ROOM1_BG_H
#define BN_REGULAR_BG_ITEMS_ROOM1_BG_H

#include "bn_regular_bg_item.h"

//{{BLOCK(room1_bg_bn_gfx)

//======================================================================
//
//	room1_bg_bn_gfx, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 661 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 21152 + 4096 = 25280
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM1_BG_BN_GFX_H
#define GRIT_ROOM1_BG_BN_GFX_H

#define room1_bg_bn_gfxTilesLen 21152
extern const bn::tile room1_bg_bn_gfxTiles[661];

#define room1_bg_bn_gfxMapLen 4096
extern const bn::regular_bg_map_cell room1_bg_bn_gfxMap[2048];

#define room1_bg_bn_gfxPalLen 32
extern const bn::color room1_bg_bn_gfxPal[16];

#endif // GRIT_ROOM1_BG_BN_GFX_H

//}}BLOCK(room1_bg_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item room1_bg(
            regular_bg_tiles_item(span<const tile>(room1_bg_bn_gfxTiles, 661), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(room1_bg_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(room1_bg_bn_gfxMap[0], size(64, 32), compression_type::NONE, 1, false));
}

#endif

