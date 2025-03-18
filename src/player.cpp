#include "../include/player.h"
#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_lamb.h" // Required for animations

Player::Player(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)), hitbox{x, y, 16, 16}, last_direction(3), score(0), animation(bn::nullopt) {}

void Player::update(const bn::vector<Hitbox, 10>& obstacles) {
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

    // If no movement input, stop animation and reset sprite to idle frame
    if (dx == 0 && dy == 0) {
        if (animation.has_value()) {
            animation.reset();
        }
        int idle_frame = (last_direction == 0) ? 8   // Left
                       : (last_direction == 1) ? 12  // Right
                       : (last_direction == 2) ? 4   // Up
                       : 0;                          // Down
        sprite.set_tiles(bn::sprite_items::lamb.tiles_item(), idle_frame);
        return;
    }

    Hitbox new_lamb_hitbox = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    if (!new_lamb_hitbox.collides_any(obstacles)) {
        sprite.set_x(sprite.x() + dx);
        sprite.set_y(sprite.y() + dy);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        if (lamb_new_direction != last_direction || !animation.has_value()) {
            int start_frame = (lamb_new_direction == 0) ? 8   // Left
                            : (lamb_new_direction == 1) ? 12  // Right
                            : (lamb_new_direction == 2) ? 4   // Up
                            : 0; // Down

            animation = bn::create_sprite_animate_action_forever(
                sprite, 6, bn::sprite_items::lamb.tiles_item(),
                start_frame, start_frame + 1, start_frame + 2, start_frame + 3
            );

            last_direction = lamb_new_direction;
        }
        animation->update();
    } else {
        if (animation.has_value()) {
            animation.reset();
        }
        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(bn::sprite_items::lamb.tiles_item(), idle_frame);
    }
}

Hitbox Player::get_hitbox() const {
    return hitbox;
}

void Player::increase_score() {
    score++;
}
