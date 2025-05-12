#include "../include/room2.h"
#include "../include/heart_ui.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_room2_bg.h"
#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"
#include "bn_sprite_items_lambdash.h"

#include "bn_camera_actions.h"
#include "bn_vector.h"
#include "bn_random.h"
#include "bn_seed_random.h"

#include "../include/player.h"
#include "../include/hitbox.h"
#include "../include/camera.h"

namespace Room2 {

void play_game_scene(unsigned seed) {
    bn::seed_random rng(seed);
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    bn::regular_bg_ptr bg = bn::regular_bg_items::room2_bg.create_bg(0, 0);
    bg.set_camera(camera);

    Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk, bn::sprite_items::lambdash);
    lamb.set_camera(camera);

    HeartUI heartUI(3);
    heartUI.set_position(-109, -70);

    bn::vector<Hitbox, 10> obstacles;
    obstacles.push_back(Hitbox{-160, -128, 10, 256});
    obstacles.push_back(Hitbox{164, -128, 10, 256});
    obstacles.push_back(Hitbox{-164, -128, 512, 10});
    obstacles.push_back(Hitbox{-164, 120, 512, 10});

    while (!bn::keypad::start_pressed()) {
        lamb.update(obstacles);
        camera_system::update_camera(camera, lamb.get_sprite().position());

        if (bn::keypad::select_pressed()) {
            return; // Exit Room2 to title screen or later room
        }

        bn::core::update();
    }
}

}