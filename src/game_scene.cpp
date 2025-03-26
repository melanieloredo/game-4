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
#include "../include/camera.h"
#include "bn_sound_items.h"
#include "bn_camera_actions.h"

void sprites_animation_actions_scene() {
    bn::random random_generator;
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // Load background
    bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
    bg.set_mosaic_enabled(true);
    bg.set_camera(camera);

    // Create player
    Player lamb(0, 0, bn::sprite_items::lamb);
    lamb.set_camera(camera);

    // Create enemies (no camera assigned)
    Cloak cloak(40, 40, bn::sprite_items::cloak);
    Bat bat(-50, 50, bn::sprite_items::bat);

    // Ensure enemies are not tied to camera
    cloak.get_sprite().remove_camera();
    bat.get_sprite().remove_camera();

    // Create coin
    Coin coin(0, 0); // Temporary position, will respawn
    coin.set_camera(camera);

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

    while (!bn::keypad::start_pressed()) {
        // Update coin animation and player
        coin.update_animation();
        lamb.update(obstacles);

        // Update camera using camera system
        camera_system::update_camera(camera, lamb.get_sprite().position());

        // Update enemies with world position, not affected by camera
        const bn::fixed_point player_world_pos = lamb.get_sprite().position();
        cloak.update(player_world_pos, obstacles);
        bat.update(player_world_pos, obstacles);

        // Player collects coin
        if (lamb.get_hitbox().collides(coin.get_hitbox())) {
            bn::sound_items::coin.play();
            coin.respawn(random_generator, obstacles);
            lamb.increase_score();
        }

        bn::core::update();
    }
}