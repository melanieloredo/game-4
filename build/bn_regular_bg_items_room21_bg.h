#ifndef BN_REGULAR_BG_ITEMS_ROOM21_BG_H
#define BN_REGULAR_BG_ITEMS_ROOM21_BG_H

#include "bn_regular_bg_item.h"

//{{BLOCK(room21_bg_bn_gfx)

//======================================================================
//
//	room21_bg_bn_gfx, 512x256@8, 
//	+ palette 48 entries, not compressed
//	+ 549 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 96 + 35136 + 4096 = 39328
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM21_BG_BN_GFX_H
#define GRIT_ROOM21_BG_BN_GFX_H

#define room21_bg_bn_gfxTilesLen 35136
extern const bn::tile room21_bg_bn_gfxTiles[1098];

#define room21_bg_bn_gfxMapLen 4096
extern const bn::regular_bg_map_cell room21_bg_bn_gfxMap[2048];

#define room21_bg_bn_gfxPalLen 96
extern const bn::color room21_bg_bn_gfxPal[48];

#endif // GRIT_ROOM21_BG_BN_GFX_H

//}}BLOCK(room21_bg_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item room21_bg(
            regular_bg_tiles_item(span<const tile>(room21_bg_bn_gfxTiles, 1098), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(room21_bg_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(room21_bg_bn_gfxMap[0], size(64, 32), compression_type::NONE, 1, false));
}

#endif

