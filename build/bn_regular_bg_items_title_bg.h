#ifndef BN_REGULAR_BG_ITEMS_TITLE_BG_H
#define BN_REGULAR_BG_ITEMS_TITLE_BG_H

#include "bn_regular_bg_item.h"

//{{BLOCK(title_bg_bn_gfx)

//======================================================================
//
//	title_bg_bn_gfx, 256x256@8, 
//	+ palette 32 entries, not compressed
//	+ 248 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 64 + 15872 + 2048 = 17984
//
//	Time-stamp: 2025-05-15, 05:44:42
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TITLE_BG_BN_GFX_H
#define GRIT_TITLE_BG_BN_GFX_H

#define title_bg_bn_gfxTilesLen 15872
extern const bn::tile title_bg_bn_gfxTiles[496];

#define title_bg_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell title_bg_bn_gfxMap[1024];

#define title_bg_bn_gfxPalLen 64
extern const bn::color title_bg_bn_gfxPal[32];

#endif // GRIT_TITLE_BG_BN_GFX_H

//}}BLOCK(title_bg_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item title_bg(
            regular_bg_tiles_item(span<const tile>(title_bg_bn_gfxTiles, 496), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(title_bg_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(title_bg_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

