#include "../include/game_scene.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_room1_bg.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_cloak.h"
#include "bn_sprite_items_coin_animated.h"
#include "bn_sprite_items_bat.h"
#include "bn_vector.h"
#include "../include/hitbox.h"
#include "../include/player.h"
#include "../include/coin.h"
#include "../include/cloak.h"
#include "../include/bat.h"
#include "bn_sound_items.h"
#include "bn_camera_actions.h"

void sprites_animation_actions_scene() {
    bn::random random_generator;
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // Load background
    bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
    bg.set_mosaic_enabled(true);
    bg.set_camera(camera);

    // Create player, enemies, and coin
    Player lamb(0, 0, bn::sprite_items::lamb);
    lamb.set_camera(camera);

    Cloak cloak(40, 40, bn::sprite_items::cloak);
<<<<<<< HEAD
    cloak.set_camera(camera);

=======
    Bat bat(-50, 50, bn::sprite_items::bat);
>>>>>>> main
    Coin coin(0, 0); // Temporary position, will respawn
    coin.set_camera(camera);

    // Define map obstacles and borders
    bn::vector<Hitbox, 10> obstacles;
    obstacles.push_back(Hitbox{-60, -70, 30, 30}); // Pikes on the top left
    obstacles.push_back(Hitbox{80,  0, 40, 30});   // Pikes on the right
    obstacles.push_back(Hitbox{-256,  0, 10, 256});  // Left border
    obstacles.push_back(Hitbox{ 256,  0, 10, 256});  // Right border
    obstacles.push_back(Hitbox{ 0, -128, 512, 10});  // Top border
    obstacles.push_back(Hitbox{ 0,  128, 512, 10});  // Bottom border

    // Ensure coin spawns away from obstacles and borders
    coin.respawn(random_generator, obstacles);

    while (!bn::keypad::start_pressed()) {
        coin.update_animation();
        lamb.update(obstacles);
        camera.set_x(lamb.get_sprite().x());
        camera.set_y(lamb.get_sprite().y());
        cloak.update(lamb.get_sprite(), obstacles);
        bat.update(lamb.get_sprite(), obstacles);

        // Player collects coins
        if (lamb.get_hitbox().collides(coin.get_hitbox())) {
            bn::sound_items::coin.play();
            coin.respawn(random_generator, obstacles);
            lamb.increase_score();
        }

        bn::core::update();
    }
}
