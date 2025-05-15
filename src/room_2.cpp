#include "../include/room2.h"
#include "../include/heart_ui.h"
#include "../include/score_manager.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_room2_bg.h"
#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"
#include "bn_sprite_items_lambdash.h"
#include "bn_sprite_items_bat.h"
#include "bn_sprite_items_cloak.h"
#include "bn_sprite_items_fire_worm.h"
#include "bn_sprite_items_fire_ball.h"

#include "bn_camera_actions.h"
#include "bn_vector.h"
#include "bn_random.h"
#include "bn_seed_random.h"
#include "bn_sound_items.h" // 🔊 Sound support

#include "../include/player.h"
#include "../include/hitbox.h"
#include "../include/bat.h"
#include "../include/cloak.h"
#include "../include/fire_worm.h"
#include "../include/camera.h"
#include "../include/heart.h"

namespace Room2 {

int play_game_scene(unsigned seed, ScoreManager& score_manager) {
    bn::seed_random rng(seed);
    bn::random rng_instance;

    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    bn::regular_bg_ptr bg = bn::regular_bg_items::room2_bg.create_bg(0, 0);
    bg.set_camera(camera);

    Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk, bn::sprite_items::lambdash);
    lamb.set_camera(camera);

    HeartUI heartUI(3);
    heartUI.set_position(-109, -70);

    Heart heart(0, 0);
    heart.set_camera(camera);
    
    bn::vector<Hitbox, 10> obstacles;
    obstacles.push_back(Hitbox{-160, -128, 10, 256});
    obstacles.push_back(Hitbox{164, -128, 10, 256});
    obstacles.push_back(Hitbox{-164, -128, 512, 10});
    obstacles.push_back(Hitbox{-164, 120, 512, 10});

    Hitbox exit_trigger(148, -90, 10, 35);

    bn::vector<Bat, 10> bats;
    bn::vector<Cloak, 10> cloaks;
    bn::vector<FireWorm, 10> fire_worms;
    bn::vector<Hitbox, 30> spawn_zones = obstacles;

    auto try_spawn = [&](auto& list, auto sprite_item, int count) {
        for (int i = 0; i < count; ++i) {
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
                    auto entity = typename std::remove_reference<decltype(list)>::type::value_type(int(x), int(y), sprite_item);
                    entity.get_sprite().set_camera(camera);
                    list.push_back(entity);
                    spawn_zones.push_back(test_hitbox);
                    break;
                }
            }
        }
    };

    try_spawn(bats, bn::sprite_items::bat, rng.get_int(3, 7));
    try_spawn(cloaks, bn::sprite_items::cloak, rng.get_int(2, 5));
    try_spawn(fire_worms, bn::sprite_items::fire_worm, rng.get_int(1, 3));
    
    heart.respawn(rng_instance, obstacles);

    float player_health = 3.0f;
    int damage_cooldown_frames = 0;

    while (true) {
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
                    bn::sound_items::death.play(); // 🔊 Cloak defeated
                    score_manager.add_points(50);
                }
                if (damage_cooldown_frames <= 0 && !lamb.is_dashing_now() && lamb.get_hitbox().collides(cloak.get_hitbox())) {
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
                    bn::sound_items::death.play(); // 🔊 Bat defeated
                    score_manager.add_points(30);
                }
                if (damage_cooldown_frames <= 0 && !lamb.is_dashing_now() && lamb.get_hitbox().collides(bat.get_hitbox())) {
                    player_health -= 0.5f;
                    damage_cooldown_frames = 30;
                }
            }
        }

        for (FireWorm& worm : fire_worms) {
            worm.update(lamb.get_sprite().position(), obstacles);
            if (worm.get_sprite().visible()) {
                for (const Fireball& fireball : worm.get_fireballs()) {
                    if (fireball.is_active() && damage_cooldown_frames <= 0 && !lamb.is_dashing_now() && fireball.get_hitbox().collides(lamb.get_hitbox())) {
                        player_health -= 0.5f;
                        damage_cooldown_frames = 30;
                    }
                }
                if (lamb.is_attacking_now() && atk_hitbox.collides(worm.get_hitbox())) {
                    worm.get_sprite().set_visible(false);
                    bn::sound_items::death.play(); // 🔊 Fire Worm defeated
                    score_manager.add_points(40);
                }
            }
        }

        if (lamb.get_hitbox().collides(heart.get_hitbox())) {
            bn::sound_items::healthup.play(); // ❤️ Heart pickup
            heart.respawn(rng_instance, obstacles);
            player_health += 1.0f;
            if (player_health > 3.0f) {
                player_health = 3.0f;
            }
        }

        score_manager.draw_score(0, -70);

        bool all_defeated = true;
        for (const Bat& bat : bats) if (bat.get_sprite().visible()) all_defeated = false;
        for (const Cloak& cloak : cloaks) if (cloak.get_sprite().visible()) all_defeated = false;
        for (const FireWorm& worm : fire_worms) if (worm.get_sprite().visible()) all_defeated = false;

        if (all_defeated && lamb.get_hitbox().collides(exit_trigger)) {
            return 1;
        }

        if (bn::keypad::select_pressed()) {
            return 0;
        }

        if (damage_cooldown_frames > 0) {
            --damage_cooldown_frames;
        }

        bn::core::update();
    }
}

}
