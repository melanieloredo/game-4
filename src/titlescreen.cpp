#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_fixed.h"
#include "bn_math.h"

#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_music.h"
#include "bn_music_items.h" // 🔊 Music support

#include "bn_regular_bg_items_title_bg.h"
#include "bn_regular_bg_items_logo.h"
#include "bn_sprite_items_play_button.h"
#include "bn_sprite_items_mascot.h"
#include "bn_sprite_items_flame1.h"
#include "bn_sprite_items_flame2.h"

#define REG_VCOUNT (*(volatile unsigned short*)(0x04000006))

unsigned titlescreen()
{
    int flash_counter = 0;
    bool flash_visible = true;
    int frame_timer = 0;

    // 🔊 Play title screen music
    bn::music_items::title_theme.play();

    bn::regular_bg_ptr title_bg = bn::regular_bg_items::title_bg.create_bg(0, 0);
    title_bg.set_priority(3);

    bn::regular_bg_ptr logo_bg = bn::regular_bg_items::logo.create_bg(0, -80);
    logo_bg.set_priority(1);

    bn::sprite_ptr mascot = bn::sprite_items::mascot.create_sprite(-50, -80);
    mascot.set_bg_priority(2);

    bn::sprite_animate_action<2> mascot_blink = bn::create_sprite_animate_action_forever(
        mascot, 50, bn::sprite_items::mascot.tiles_item(), 0, 1
    );

    bn::sprite_ptr play_button = bn::sprite_items::play_button.create_sprite(0, 15);
    play_button.set_visible(true);
    play_button.set_bg_priority(0);

    bn::sprite_ptr flame1 = bn::sprite_items::flame1.create_sprite(-58, 19);
    flame1.set_bg_priority(2);
    bn::sprite_ptr flame2 = bn::sprite_items::flame2.create_sprite(87, 4);
    flame2.set_bg_priority(2);

    bn::sprite_animate_action<5> flame1_anim = bn::create_sprite_animate_action_forever(
        flame1, 10, bn::sprite_items::flame1.tiles_item(), 0, 1, 2, 3, 4
    );
    bn::sprite_animate_action<5> flame2_anim = bn::create_sprite_animate_action_forever(
        flame2, 10, bn::sprite_items::flame2.tiles_item(), 0, 1, 2, 3, 4
    );

    // Slide logo and mascot down
    while (logo_bg.y() < 0)
    {
        logo_bg.set_y(logo_bg.y() + 1);
        mascot.set_y(logo_bg.y() - 40);
        mascot_blink.update();
        flame1_anim.update();
        flame2_anim.update();
        bn::core::update();
    }

    bool play_selected = false;

    while (!bn::keypad::start_pressed())
    {
        ++frame_timer;

        if (bn::keypad::down_pressed()) {
            play_selected = true;
            play_button.set_tiles(bn::sprite_items::play_button.tiles_item(), 1);
            play_button.set_visible(true);
        }
        else if (bn::keypad::up_pressed()) {
            play_selected = false;
            play_button.set_tiles(bn::sprite_items::play_button.tiles_item(), 0);
        }

        if (!play_selected)
        {
            if (++flash_counter >= 30)
            {
                flash_visible = !flash_visible;
                play_button.set_visible(flash_visible);
                flash_counter = 0;
            }
        }

        mascot_blink.update();
        flame1_anim.update();
        flame2_anim.update();

        bn::core::update();
    }

    // 🔇 Stop title screen music before scene transition
    bn::music::stop();

    // Generate seed for randomness
    unsigned seed = frame_timer ^ REG_VCOUNT;
    return seed;
}
