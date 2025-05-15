#ifndef BN_REGULAR_BG_ITEMS_ROOM2_BG_H
#define BN_REGULAR_BG_ITEMS_ROOM2_BG_H

#include "bn_regular_bg_item.h"

//{{BLOCK(room2_bg_bn_gfx)

//======================================================================
//
//	room2_bg_bn_gfx, 512x256@8, 
//	+ palette 48 entries, not compressed
//	+ 571 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 96 + 36544 + 4096 = 40736
//
//	Time-stamp: 2025-05-15, 05:44:42
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM2_BG_BN_GFX_H
#define GRIT_ROOM2_BG_BN_GFX_H

#define room2_bg_bn_gfxTilesLen 36544
extern const bn::tile room2_bg_bn_gfxTiles[1142];

#define room2_bg_bn_gfxMapLen 4096
extern const bn::regular_bg_map_cell room2_bg_bn_gfxMap[2048];

#define room2_bg_bn_gfxPalLen 96
extern const bn::color room2_bg_bn_gfxPal[48];

#endif // GRIT_ROOM2_BG_BN_GFX_H

//}}BLOCK(room2_bg_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item room2_bg(
            regular_bg_tiles_item(span<const tile>(room2_bg_bn_gfxTiles, 1142), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(room2_bg_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(room2_bg_bn_gfxMap[0], size(64, 32), compression_type::NONE, 1, false));
}

#endif

