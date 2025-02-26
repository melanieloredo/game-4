#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_ninja.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_coin_animated.h"
#include "bn_random.h"
#include "bn_sound_items.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_items_room1_bg.h"

struct Hitbox {
    bn::fixed x, y, width, height;

    bool collides(const Hitbox& other) const {
        return (x < other.x + other.width && x + width > other.x &&
                y < other.y + other.height && y + height > other.y);
    }
};

void sprites_animation_actions_scene() {
    bn::random random_generator;

    bn::regular_bg_ptr bg = bn::regular_bg_items::room1_bg.create_bg(0, 0);
    
    bn::sprite_ptr lamb_sprite = bn::sprite_items::lamb.create_sprite(0, 0);
    lamb_sprite.set_scale(1);
    
    bn::sprite_ptr ninja_sprite = bn::sprite_items::ninja.create_sprite(40, 40);
    ninja_sprite.set_scale(1);

    bn::sprite_ptr coin_sprite = bn::sprite_items::coin_animated.create_sprite(
        random_generator.get_int(-110, 110), random_generator.get_int(-80, 80)
    );
    
    bn::sprite_animate_action<8> coin_animation = bn::create_sprite_animate_action_forever(
        coin_sprite, 10, bn::sprite_items::coin_animated.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7
    );

    Hitbox ninja_hitbox = {ninja_sprite.x(), ninja_sprite.y(), 16, 16};
    Hitbox rock_hitbox = {bn::fixed(-32), bn::fixed(24), 16, 16};
    Hitbox coin_hitbox = {coin_sprite.x(), coin_sprite.y(), 16, 16};

    bn::optional<bn::sprite_animate_action<4>> lamb_action;
    bn::optional<bn::sprite_animate_action<4>> ninja_action;
    int lamb_last_direction = 3; // Default to facing forward (down)
    int ninja_last_direction = 3;
    int ninja_pause_counter = 0;
    int lamb_score = 0;
    int ninja_score = 0;

    while (!bn::keypad::start_pressed()) {
        coin_hitbox.x = coin_sprite.x();
        coin_hitbox.y = coin_sprite.y();
        
        bool lamb_moving = false;
        bool ninja_moving = false;

        // Lamb movement and animation
        bool move_left = bn::keypad::left_held();
        bool move_right = bn::keypad::right_held();
        bool move_up = bn::keypad::up_held();
        bool move_down = bn::keypad::down_held();

        if ((move_left && move_right) || (move_up && move_down)) {
            move_left = move_right = move_up = move_down = false;
        }

        int lamb_new_direction = lamb_last_direction;
        if (move_up) lamb_new_direction = 2;
        if (move_down) lamb_new_direction = 3;
        if (move_left) lamb_new_direction = 0;
        if (move_right) lamb_new_direction = 1;

        bn::fixed lamb_dx = (move_right - move_left);
        bn::fixed lamb_dy = (move_down - move_up);

        if (lamb_dx != 0 || lamb_dy != 0) {
            bn::fixed new_lamb_x = lamb_sprite.x() + lamb_dx;
            bn::fixed new_lamb_y = lamb_sprite.y() + lamb_dy;
            Hitbox new_lamb_hitbox = {new_lamb_x, new_lamb_y, 16, 16};
            
            if (!new_lamb_hitbox.collides(rock_hitbox)) {
                lamb_sprite.set_x(new_lamb_x);
                lamb_sprite.set_y(new_lamb_y);
                lamb_moving = true;
            }
        }

        // Ninja movement logic update
        if (ninja_pause_counter == 0) {
            bn::fixed ninja_dx = 0;
            bn::fixed ninja_dy = 0;
            bool collided = false;

            if (ninja_sprite.x() < coin_sprite.x()) {
                ninja_dx = 1;
                ninja_last_direction = 1;
            } else if (ninja_sprite.x() > coin_sprite.x()) {
                ninja_dx = -1;
                ninja_last_direction = 0;
            } else if (ninja_sprite.y() < coin_sprite.y()) {
                ninja_dy = 1;
                ninja_last_direction = 3;
            } else if (ninja_sprite.y() > coin_sprite.y()) {
                ninja_dy = -1;
                ninja_last_direction = 2;
            }

            bn::fixed new_ninja_x = ninja_sprite.x() + ninja_dx;
            bn::fixed new_ninja_y = ninja_sprite.y() + ninja_dy;
            Hitbox new_ninja_hitbox = {new_ninja_x, new_ninja_y, ninja_hitbox.width, ninja_hitbox.height};
            
            if (!new_ninja_hitbox.collides(rock_hitbox)) {
                ninja_sprite.set_x(new_ninja_x);
                ninja_sprite.set_y(new_ninja_y);
                ninja_hitbox = new_ninja_hitbox;
                ninja_moving = true;
            } else {
                collided = true;
            }

            if (collided) {
                if (ninja_dx != 0) {
                    ninja_dx = 0;
                    ninja_dy = (coin_sprite.y() > ninja_sprite.y()) ? 1 : -1;
                } else {
                    ninja_dy = 0;
                    ninja_dx = (coin_sprite.x() > ninja_sprite.x()) ? 1 : -1;
                }

                new_ninja_x = ninja_sprite.x() + ninja_dx;
                new_ninja_y = ninja_sprite.y() + ninja_dy;
                new_ninja_hitbox = {new_ninja_x, new_ninja_y, ninja_hitbox.width, ninja_hitbox.height};
                
                if (!new_ninja_hitbox.collides(rock_hitbox)) {
                    ninja_sprite.set_x(new_ninja_x);
                    ninja_sprite.set_y(new_ninja_y);
                    ninja_hitbox = new_ninja_hitbox;
                    ninja_moving = true;
                }
            }
        } else {
            ninja_pause_counter--;
        }

        // Lamb animation
        if (lamb_moving) {
            if (lamb_new_direction != lamb_last_direction || !lamb_action.has_value()) {
                int start_frame = (lamb_new_direction == 0) ? 8   // Left
                                : (lamb_new_direction == 1) ? 12 // Right
                                : (lamb_new_direction == 2) ? 4   // Up
                                : 0; // Down
                lamb_action = bn::create_sprite_animate_action_forever(
                    lamb_sprite, 6, bn::sprite_items::lamb.tiles_item(),
                    start_frame, start_frame + 1, start_frame + 2, start_frame + 3
                );
                lamb_last_direction = lamb_new_direction;
            }
            lamb_action->update();
        } else {
            lamb_action.reset();
            int idle_frame = (lamb_last_direction == 0) ? 8   // Left
                           : (lamb_last_direction == 1) ? 12 // Right
                           : (lamb_last_direction == 2) ? 4   // Up
                           : 0; // Down
            lamb_sprite.set_tiles(bn::sprite_items::lamb.tiles_item(), idle_frame);
        }

        // Ninja animation
        if (ninja_moving) {
            int start_frame = (ninja_last_direction == 0) ? 8   // Left
                            : (ninja_last_direction == 1) ? 12 // Right
                            : (ninja_last_direction == 2) ? 4   // Up
                            : 0; // Down
            
            if (!ninja_action.has_value() || ninja_action->graphics_indexes()[0] != start_frame) {
                ninja_action = bn::create_sprite_animate_action_forever(
                    ninja_sprite, 6, bn::sprite_items::ninja.tiles_item(),
                    start_frame, start_frame + 1, start_frame + 2, start_frame + 3
                );
            }
            ninja_action->update();
        } else {
            ninja_action.reset();
            int idle_frame = (ninja_last_direction == 0) ? 8   // Left
                           : (ninja_last_direction == 1) ? 12  // Right 
                           : (ninja_last_direction == 2) ? 4   // Up 
                           : 0;                                // Down 
            
            ninja_sprite.set_tiles(bn::sprite_items::ninja.tiles_item(), idle_frame);
        }

        // Coin collision and respawn logic 
        bool coin_collected = false;
        
        if (ninja_hitbox.collides(coin_hitbox)) {
            ninja_score++;
            coin_collected = true;
            ninja_pause_counter = 120; // Pause for about two seconds when collecting a coin.
        } else if (coin_hitbox.collides({lamb_sprite.x(), lamb_sprite.y(), 
                                         static_cast<bn::fixed>(16), 
                                         static_cast<bn::fixed>(16)})) {
            lamb_score++;
            coin_collected = true;
        }

        if (coin_collected) {
            bn::sound_items::coin.play();
            
            // Respawn the coin at a random position.
            coin_sprite.set_x(random_generator.get_int(-110, 110));
            coin_sprite.set_y(random_generator.get_int(-80, 80));
            coin_hitbox.x = coin_sprite.x();
            coin_hitbox.y = coin_sprite.y();
        }

        // Update animated coin.
        coin_animation.update();

        bn::core::update();
    }
}

int main() {
    bn::core::init();
    while (true) {
        sprites_animation_actions_scene();
        bn::core::update();
    }
}
