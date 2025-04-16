#include "../include/player.h"
#include "bn_keypad.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"

Player::Player(int x, int y, const bn::sprite_item& idle_item, const bn::sprite_item& attack_item)
    : sprite(idle_item.create_sprite(x, y)),
      idle_sprite_item(idle_item),
      attack_sprite_item(attack_item),
      hitbox{x, y, 16, 16},
      attack_hitbox{x, y, 16, 16},
      last_direction(3),
      score(0),
      is_attacking(false),
      attack_timer(0),
      animation(bn::nullopt) {}

void Player::update(const bn::vector<Hitbox, 10>& obstacles) {
    if (is_attacking) {
        update_attack_hitbox();
        if (attack_timer > 0) {
            --attack_timer;
        } else {
            is_attacking = false;

            int idle_frame = (last_direction == 0) ? 8
                           : (last_direction == 1) ? 12
                           : (last_direction == 2) ? 4
                           : 0;

            sprite.set_tiles(idle_sprite_item.tiles_item(), idle_frame);
        }
        return;
    }

    if (bn::keypad::a_pressed() && !is_attacking) {
        attack();
        return;
    }

    bool move_left = bn::keypad::left_held();
    bool move_right = bn::keypad::right_held();
    bool move_up = bn::keypad::up_held();
    bool move_down = bn::keypad::down_held();

    if ((move_left && move_right) || (move_up && move_down)) {
        move_left = move_right = move_up = move_down = false;
    }

    int lamb_new_direction = last_direction;
    if (move_up) lamb_new_direction = 2;
    if (move_down) lamb_new_direction = 3;
    if (move_left) lamb_new_direction = 0;
    if (move_right) lamb_new_direction = 1;

    bn::fixed dx = (move_right - move_left);
    bn::fixed dy = (move_down - move_up);

    if (dx == 0 && dy == 0) {
        if (animation.has_value()) {
            animation.reset();
        }
        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(idle_sprite_item.tiles_item(), idle_frame);
        return;
    }

    Hitbox new_lamb_hitbox = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    if (!new_lamb_hitbox.collides_any(obstacles)) {
        sprite.set_x(sprite.x() + dx);
        sprite.set_y(sprite.y() + dy);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        if (lamb_new_direction != last_direction || !animation.has_value()) {
            int start_frame = (lamb_new_direction == 0) ? 8
                            : (lamb_new_direction == 1) ? 12
                            : (lamb_new_direction == 2) ? 4
                            : 0;

            animation = bn::create_sprite_animate_action_forever(
                sprite, 6, idle_sprite_item.tiles_item(),
                start_frame, start_frame + 1, start_frame + 2, start_frame + 3
            );

            last_direction = lamb_new_direction;
        }
        if (animation.has_value()) {
            animation->update();
        }
    } else {
        if (animation.has_value()) {
            animation.reset();
        }
        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(idle_sprite_item.tiles_item(), idle_frame);
    }
}

void Player::attack() {
    if (is_attacking) {
        return; // Prevent attack if already attacking
    }

    is_attacking = true;
    attack_timer = 20;
    update_attack_hitbox();

    // Determine the correct attack animation frame based on the last direction
    int start_frame = 0;
    if (last_direction == 0 || last_direction == 2) {  // Left
        start_frame = 0;         // Attack left animation frame starts at 0
    } else if (last_direction == 1 || last_direction == 3) {  // Right
        start_frame = 5;         // Attack right animation frame starts at 5
    }
    // Other directions (up, down) are not used for attacking

     // Reset any previous animation
     if (animation.has_value()) {
        animation.reset();
    }

    // Create an animation action for 4 frames (for attack)
    animation = bn::create_sprite_animate_action_once(
        sprite, 4, attack_sprite_item.tiles_item(),
        start_frame, start_frame + 1, start_frame + 2, start_frame + 3
    );
    

}

void Player::update_attack_hitbox() {
    bn::fixed ax = sprite.x();
    bn::fixed ay = sprite.y();

    if (last_direction == 0) { ax -= 16; }     // Left
    else if (last_direction == 1) { ax += 16; } // Right
    else if (last_direction == 2) { ay -= 16; } // Up
    else if (last_direction == 3) { ay += 16; } // Down

    attack_hitbox = {ax, ay, 16, 16};
}

Hitbox Player::get_hitbox() const {
    return hitbox;
}

Hitbox Player::get_attack_hitbox() const {
    return attack_hitbox;
}

void Player::increase_score() {
    score++;
}
