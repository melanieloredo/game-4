#ifndef BN_REGULAR_BG_ITEMS_LOGO_H
#define BN_REGULAR_BG_ITEMS_LOGO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(logo_bn_gfx)

//======================================================================
//
//	logo_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 150 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 4800 + 2048 = 6880
//
//	Time-stamp: 2025-05-15, 05:44:41
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LOGO_BN_GFX_H
#define GRIT_LOGO_BN_GFX_H

#define logo_bn_gfxTilesLen 4800
extern const bn::tile logo_bn_gfxTiles[150];

#define logo_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell logo_bn_gfxMap[1024];

#define logo_bn_gfxPalLen 32
extern const bn::color logo_bn_gfxPal[16];

#endif // GRIT_LOGO_BN_GFX_H

//}}BLOCK(logo_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item logo(
            regular_bg_tiles_item(span<const tile>(logo_bn_gfxTiles, 150), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(logo_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(logo_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

