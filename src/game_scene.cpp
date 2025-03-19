#include "../include/game_scene.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_room1_bg.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_cloak.h"
#include "bn_sprite_items_coin_animated.h"
#include "bn_vector.h"
#include "../include/hitbox.h"
#include "../include/player.h"
#include "../include/coin.h"
#include "../include/cloak.h"
#include "bn_sound_items.h"

void sprites_animation_actions_scene() {
    bn::random random_generator;

    // Load background
    bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
    bg.set_mosaic_enabled(true);

    // Create player, enemy, and coin objects
    Player lamb(0, 0, bn::sprite_items::lamb);
    Cloak cloak(40, 40, bn::sprite_items::cloak);
    Coin coin(0, 0); // Temporary position, will respawn

    // Define map obstacles and borders
    bn::vector<Hitbox, 10> obstacles;

    // Obstacles inside the map
    obstacles.push_back(Hitbox{-60, -70, 30, 30}); // Pikes on the top left
    obstacles.push_back(Hitbox{80,  0, 40, 30});   // Pikes on the right

    // **Map Border (512x256)**
    obstacles.push_back(Hitbox{-256,  0, 10, 256});  // Left border
    obstacles.push_back(Hitbox{ 256,  0, 10, 256});  // Right border
    obstacles.push_back(Hitbox{ 0, -128, 512, 10});  // Top border
    obstacles.push_back(Hitbox{ 0,  128, 512, 10});  // Bottom border

    // Ensure coin spawns away from obstacles and borders
    coin.respawn(random_generator, obstacles);

    while (!bn::keypad::start_pressed()) {
        // Update animations
        coin.update_animation();
        lamb.update(obstacles);
        cloak.update(coin.get_sprite(), obstacles);

        // **Collision logic with sound effect**
        if (cloak.get_hitbox().collides(coin.get_hitbox())) {
            bn::sound_items::coin.play(); // Play coin collection sound
            coin.respawn(random_generator, obstacles);
            cloak.increase_score();
        }
        if (lamb.get_hitbox().collides(coin.get_hitbox())) {
            bn::sound_items::coin.play(); // Play coin collection sound
            coin.respawn(random_generator, obstacles);
            lamb.increase_score();
        }

        bn::core::update();
    }
}
