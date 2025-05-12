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
#include "bn_seed_random.h"
#include "bn_random.h"
#include "bn_sound_items.h"
#include "bn_camera_actions.h"

#include "../include/hitbox.h"
#include "../include/player.h"
#include "../include/heart.h"
#include "../include/cloak.h"
#include "../include/bat.h"
#include "../include/camera.h"

namespace Room1 {

    void play_game_scene(unsigned seed) {
        bn::seed_random rng(seed); 
        bn::random rng_instance;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
        bg.set_mosaic_enabled(true);
        bg.set_camera(camera);

        Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk, bn::sprite_items::lambdash);
        lamb.set_camera(camera);

        HeartUI heartUI(3);
        heartUI.set_position(-109, -70);

        Heart heart(0, 0); 
        heart.set_camera(camera);

        bn::vector<Hitbox, 10> obstacles;
        obstacles.push_back(Hitbox{-60, -70, 30, 30});
        obstacles.push_back(Hitbox{80,  0, 40, 30});
        obstacles.push_back(Hitbox{-160,  -128, 10, 256});
        obstacles.push_back(Hitbox{ 164,  -128, 10, 256});
        obstacles.push_back(Hitbox{ -164, -128, 512, 10});
        obstacles.push_back(Hitbox{ -164,  120, 512, 10});
        // REMOVE: obstacles.push_back(Hitbox{ 148, -90, 10, 35 });

        Hitbox exit_trigger(148, -90, 10, 35);

        int bat_count = rng.get_int(2, 6);
        int cloak_count = rng.get_int(1, 4);

        bn::vector<Bat, 10> bats;
        bn::vector<Cloak, 10> cloaks;
        bn::vector<Hitbox, 30> spawn_zones = obstacles;

        for (int i = 0; i < bat_count; ++i) {
            for (int attempts = 0; attempts < 100; ++attempts) {
                bn::fixed x = rng.get_fixed(-140, 140);
                bn::fixed y = rng.get_fixed(-100, 100);
                Hitbox test_hitbox(x, y, 16, 16);
                bool collides = false;

                for (const Hitbox& h : spawn_zones) {
                    if (test_hitbox.collides(h)) {
                        collides = true;
                        break;
                    }
                }

                if (!collides) {
                    Bat bat(int(x), int(y), bn::sprite_items::bat);
                    bat.set_camera(camera);
                    bats.push_back(bat);
                    spawn_zones.push_back(test_hitbox);
                    break;
                }
            }
        }

        for (int i = 0; i < cloak_count; ++i) {
            for (int attempts = 0; attempts < 100; ++attempts) {
                bn::fixed x = rng.get_fixed(-140, 140);
                bn::fixed y = rng.get_fixed(-100, 100);
                Hitbox test_hitbox(x, y, 16, 16);
                bool collides = false;

                for (const Hitbox& h : spawn_zones) {
                    if (test_hitbox.collides(h)) {
                        collides = true;
                        break;
                    }
                }

                if (!collides) {
                    Cloak cloak(int(x), int(y), bn::sprite_items::cloak);
                    cloak.set_camera(camera);
                    cloaks.push_back(cloak);
                    spawn_zones.push_back(test_hitbox);
                    break;
                }
            }
        }

        heart.respawn(rng_instance, obstacles);

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

            for (Cloak& cloak : cloaks) {
                if (cloak.get_sprite().visible()) {
                    cloak.update(lamb.get_sprite().position(), obstacles);
                    if (lamb.is_attacking_now() && atk_hitbox.collides(cloak.get_hitbox())) {
                        cloak.get_sprite().set_visible(false);
                    }
                    if (damage_cooldown_frames <= 0 && !lamb.is_dashing_now() &&
                        lamb.get_hitbox().collides(cloak.get_hitbox())) {
                        player_health -= 0.5f;
                        damage_cooldown_frames = 30;
                    }
                }
            }

            for (Bat& bat : bats) {
                if (bat.get_sprite().visible()) {
                    bat.update(lamb.get_sprite().position(), obstacles);
                    if (lamb.is_attacking_now() && atk_hitbox.collides(bat.get_hitbox())) {
                        bat.get_sprite().set_visible(false);
                    }
                    if (damage_cooldown_frames <= 0 && !lamb.is_dashing_now() &&
                        lamb.get_hitbox().collides(bat.get_hitbox())) {
                        player_health -= 0.5f;
                        damage_cooldown_frames = 30;
                    }
                }
            }

            if (lamb.get_hitbox().collides(heart.get_hitbox())) {
                heart.respawn(rng_instance, obstacles);
                player_health += 1.0f;
                if (player_health > 3.0f) {
                    player_health = 3.0f;
                }
            }

            bool all_defeated = true;
            for (int i = 0, limit = bats.size(); i < limit; ++i) {
                if (bats[i].get_sprite().visible()) {
                    all_defeated = false;
                    break;
                }
            }
            for (int i = 0, limit = cloaks.size(); i < limit; ++i) {
                if (cloaks[i].get_sprite().visible()) {
                    all_defeated = false;
                    break;
                }
            }

            if (all_defeated && lamb.get_hitbox().collides(exit_trigger)) {
                return;
            }

            if (bn::keypad::select_pressed()) {
                return;
            }

            if (damage_cooldown_frames > 0) {
                --damage_cooldown_frames;
            }

            bn::core::update();
        }
    }
}
