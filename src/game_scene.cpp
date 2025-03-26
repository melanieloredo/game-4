#include "../include/game_scene.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_room1_bg.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h" // ✅ updated to match your BMP filename
#include "bn_sprite_items_cloak.h"
#include "bn_sprite_items_coin_animated.h"
#include "bn_sprite_items_bat.h"
#include "bn_vector.h"
#include "../include/hitbox.h"
#include "../include/player.h"
#include "../include/coin.h"
#include "../include/cloak.h"
#include "../include/bat.h"
#include "../include/camera.h"
#include "bn_sound_items.h"
#include "bn_camera_actions.h"

void sprites_animation_actions_scene() {
    bn::random random_generator;
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // Load background
    bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
    bg.set_mosaic_enabled(true);
    bg.set_camera(camera); // adding bg to camera so it moves with it DO NOT TOUCH

    // Create player with idle and attack sprite sheets
    Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk); // ✅ updated here
    lamb.set_camera(camera);

    // Create enemies (no camera assigned)
    Cloak cloak(40, 40, bn::sprite_items::cloak);
    cloak.set_camera(camera); // adding cloak to camera so it moves with it DO NOT TOUCH

    Bat bat(-50, 50, bn::sprite_items::bat);
    bat.set_camera(camera); // adding bat to camera so it moves with it DO NOT TOUCH

    // Create coin
    Coin coin(0, 0); // Temporary position, will respawn
    coin.set_camera(camera); // adding coin to camera so it moves with it DO NOT TOUCH

    // Define map obstacles and borders
    bn::vector<Hitbox, 10> obstacles;
    obstacles.push_back(Hitbox{-60, -70, 30, 30});   // Pikes on the top left
    obstacles.push_back(Hitbox{80,  0, 40, 30});     // Pikes on the right
    obstacles.push_back(Hitbox{-256,  0, 10, 256});  // Left border
    obstacles.push_back(Hitbox{ 256,  0, 10, 256});  // Right border
    obstacles.push_back(Hitbox{ 0, -128, 512, 10});  // Top border
    obstacles.push_back(Hitbox{ 0,  128, 512, 10});  // Bottom border

    // Ensure coin spawns away from obstacles and borders
    coin.respawn(random_generator, obstacles);

    // Enemy active state
    bool cloak_alive = true;
    bool bat_alive = true;

    while (!bn::keypad::start_pressed()) {
        // Update coin animation and player
        coin.update_animation();
        lamb.update(obstacles);

        // Update camera using camera system
        camera_system::update_camera(camera, lamb.get_sprite().position());

        // Get player's attack hitbox
        const Hitbox& atk_hitbox = lamb.get_attack_hitbox();

        // Cloak logic
        if (cloak_alive) {
            cloak.update(lamb.get_sprite().position(), obstacles);

            if (lamb.is_attacking_now() && atk_hitbox.collides(cloak.get_hitbox())) {
                cloak.get_sprite().set_visible(false);
                cloak_alive = false;
                // Optional: play a sound
            }
        }

        // Bat logic
        if (bat_alive) {
            bat.update(lamb.get_sprite().position(), obstacles);

            if (lamb.is_attacking_now() && atk_hitbox.collides(bat.get_hitbox())) {
                bat.get_sprite().set_visible(false);
                bat_alive = false;
                // Optional: play a sound
            }
        }

        // Player collects coin
        if (lamb.get_hitbox().collides(coin.get_hitbox())) {
            bn::sound_items::coin.play();
            coin.respawn(random_generator, obstacles);
            lamb.increase_score();
        }

        bn::core::update();
    }
}
