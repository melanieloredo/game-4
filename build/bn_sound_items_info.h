#ifndef BN_SOUND_ITEMS_INFO_H
#define BN_SOUND_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_sound_item.h"
#include "bn_string_view.h"

namespace bn::sound_items_info
{
    constexpr inline pair<sound_item, string_view> array[] = {
        make_pair(sound_item(0), string_view("coin")),
        make_pair(sound_item(1), string_view("death")),
        make_pair(sound_item(2), string_view("healthup")),
        make_pair(sound_item(3), string_view("slash")),
    };

    constexpr inline span<const pair<sound_item, string_view>> span(array);
}

#endif

