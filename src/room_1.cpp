#include "../include/room1.h"
#include "../include/heart_ui.h" //heart ui

#include "bn_core.h"
#include "bn_keypad.h"

#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_room1_bg.h"
#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"
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



namespace Room1 {
	void play_game_scene() {
		bn::random random_generator;
		bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

		// Load background
		bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
		bg.set_mosaic_enabled(true);
		bg.set_camera(camera);

		// Create player
		Player lamb(0, 0, bn::sprite_items::lamb, bn::sprite_items::lambattk);
		lamb.set_camera(camera);
		

		//Create Heart UI
		HeartUI heartUI(3);
        heartUI.set_position(0,0);
        

		// Create enemies
		Cloak cloak(40, 40, bn::sprite_items::cloak);
		cloak.set_camera(camera);

		Bat bat(-50, 50, bn::sprite_items::bat);
		bat.set_camera(camera);

		// Create coin
		Coin coin(0, 0);
		coin.set_camera(camera);

		// Obstacles and map borders
		bn::vector<Hitbox, 10> obstacles;
		obstacles.push_back(Hitbox{-60, -70, 30, 30});
		obstacles.push_back(Hitbox{80,  0, 40, 30});
		obstacles.push_back(Hitbox{-256,  0, 10, 256});
		obstacles.push_back(Hitbox{ 256,  0, 10, 256});
		obstacles.push_back(Hitbox{ 0, -128, 512, 10});
		obstacles.push_back(Hitbox{ 0,  128, 512, 10});

		// Respawn coin away from obstacles
		coin.respawn(random_generator, obstacles);

		bool cloak_alive = true;
		bool bat_alive = true;


		float player_health = 3.0f; //start health

		while (!bn::keypad::start_pressed()) {
			// Update coin animation and player
			coin.update_animation();
			lamb.update(obstacles);

			//update health
			heartUI.set_health(player_health);

			// Camera follow
			camera_system::update_camera(camera, lamb.get_sprite().position());

			const Hitbox& atk_hitbox = lamb.get_attack_hitbox();

			// Cloak logic
			if (cloak_alive) {
				cloak.update(lamb.get_sprite().position(), obstacles);

				if (lamb.is_attacking_now() && atk_hitbox.collides(cloak.get_hitbox())) {
					cloak.get_sprite().set_visible(false);
					cloak_alive = false;
				}
			}

			// Bat logic
			if (bat_alive) {
				bat.update(lamb.get_sprite().position(), obstacles);

				if (lamb.is_attacking_now() && atk_hitbox.collides(bat.get_hitbox())) {
					bat.get_sprite().set_visible(false);
					bat_alive = false;
				}
			}

			// Coin pickup
			if (lamb.get_hitbox().collides(coin.get_hitbox())) {
				bn::sound_items::coin.play();
				coin.respawn(random_generator, obstacles);
				lamb.increase_score();
			}

			// ✅ Crash-proof reset using bn::core::reset()
			if (bn::keypad::select_pressed()) {
				bn::core::update();  // Optional: brief update before reset
				bn::core::reset();   // 🔁 Clean reset to main()
			}

			bn::core::update();
		}
	}
}
