#include "../include/room1.h"
#include "../include/heart_ui.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_room1_bg.h"
#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"
#include "bn_sprite_items_lambdash.h"
#include "bn_sprite_items_cloak.h"
#include "bn_sprite_items_bat.h"

#include "bn_vector.h"
#include "bn_sound_items.h"
#include "bn_camera_actions.h"

#include "../include/hitbox.h"
#include "../include/player.h"
#include "../include/heart.h"
#include "../include/cloak.h"
#include "../include/bat.h"
#include "../include/camera.h"

namespace Room1 {

    void play_game_scene() {
        bn::random random_generator;
        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

        bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
        bg.set_mosaic_enabled(true);
        bg.set_camera(camera);

        Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk, bn::sprite_items::lambdash);
        lamb.set_camera(camera);

        HeartUI heartUI(3);
        heartUI.set_position(-109, -70);

        Cloak cloak(40, 40, bn::sprite_items::cloak);
        cloak.set_camera(camera);

        Bat bat(-50, 50, bn::sprite_items::bat);
        bat.set_camera(camera);

        Heart heart(0, 0); 
        heart.set_camera(camera);

        bn::vector<Hitbox, 10> obstacles;
        obstacles.push_back(Hitbox{-60, -70, 30, 30});
        obstacles.push_back(Hitbox{80,  0, 40, 30});
        obstacles.push_back(Hitbox{-256,  0, 10, 256});
        obstacles.push_back(Hitbox{ 256,  0, 10, 256});
        obstacles.push_back(Hitbox{ 0, -128, 512, 10});
        obstacles.push_back(Hitbox{ 0,  128, 512, 10});

        heart.respawn(random_generator, obstacles);

        bool cloak_alive = true;
        bool bat_alive = true;
        float player_health = 3.0f;
        int damage_cooldown_frames = 0;

        while (!bn::keypad::start_pressed()) {
           
            lamb.update(obstacles);
            heartUI.set_health(player_health);

            if (player_health <= 0.0f) {
                bn::core::update();
                bn::core::reset();
            }

            camera_system::update_camera(camera, lamb.get_sprite().position());

            const Hitbox& atk_hitbox = lamb.get_attack_hitbox();

            if (cloak_alive) {
                cloak.update(lamb.get_sprite().position(), obstacles);
                if (lamb.is_attacking_now() && atk_hitbox.collides(cloak.get_hitbox())) {
                    cloak.get_sprite().set_visible(false);
                    cloak_alive = false;
                }
            }

            if (bat_alive) {
                bat.update(lamb.get_sprite().position(), obstacles);
                if (lamb.is_attacking_now() && atk_hitbox.collides(bat.get_hitbox())) {
                    bat.get_sprite().set_visible(false);
                    bat_alive = false;
                }
            }

            // ✅ Dash Invulnerability
            if (damage_cooldown_frames > 0) {
                --damage_cooldown_frames;
            }

            if (damage_cooldown_frames <= 0 && !lamb.is_dashing_now()) {
                if (cloak_alive && lamb.get_hitbox().collides(cloak.get_hitbox())) {
                    player_health -= 0.5f;
                    damage_cooldown_frames = 30;
                }
                if (bat_alive && lamb.get_hitbox().collides(bat.get_hitbox())) {
                    player_health -= 0.5f;
                    damage_cooldown_frames = 30;
                }
            }

            if (lamb.get_hitbox().collides(heart.get_hitbox())) {
                //bn::sound_items::heart.play(); //heart pick up sound
                heart.respawn(random_generator, obstacles);
                player_health += 1.0f;  // heal 1 heart when picked up
                if (player_health > 3.0f) {
                    player_health = 3.0f;  // cap health at max 3
                }
            }

            if (bn::keypad::select_pressed()) {
                bn::core::update();
                bn::core::reset();
            }

            bn::core::update();
        }
    }
}
