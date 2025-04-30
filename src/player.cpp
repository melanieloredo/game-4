#include "../include/player.h"
#include "bn_keypad.h"
#include "bn_sprite_items_lamb.h"
#include "bn_sprite_items_lambattk.h"

namespace {
    constexpr int FRAME_DURATION = 6;
    constexpr int ATTACK_DURATION = 20;

    int direction_to_idle_frame(int dir) {
        switch(dir) {
            case 0: return 8;  // Left
            case 1: return 12; // Right
            case 2: return 4;  // Up
            case 3: return 0;  // Down
            default: return 0;
        }
    }

    int direction_to_attack_frame(int dir) {
        switch(dir) {
            case 0: return 0;  // Left attack → frames 0–3
            case 1: return 4;  // Right attack → frames 4–7
            case 2: return 0;  // Up → reuse Left
            case 3: return 4;  // Down → reuse Right
            default: return 0;
        }
    }
}

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

        if (animation.has_value() && !animation->done()) {
            animation->update();
        }

        if (--attack_timer <= 0) {
            is_attacking = false;
            animation.reset();
            sprite.set_item(idle_sprite_item, direction_to_idle_frame(last_direction));
        }

        return;
    }

    if (bn::keypad::a_pressed()) {
        attack();
        return;
    }

    bool left = bn::keypad::left_held();
    bool right = bn::keypad::right_held();
    bool up = bn::keypad::up_held();
    bool down = bn::keypad::down_held();

    if ((left && right) || (up && down)) {
        left = right = up = down = false;
    }

    bn::fixed dx = (right - left);
    bn::fixed dy = (down - up);

    if (dx == 0 && dy == 0) {
        if (animation.has_value()) {
            animation.reset();
        }
        sprite.set_item(idle_sprite_item, direction_to_idle_frame(last_direction));
        return;
    }

    int new_dir = last_direction;
    if (up) new_dir = 2;
    if (down) new_dir = 3;
    if (left) new_dir = 0;
    if (right) new_dir = 1;

    Hitbox proposed = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    if (!proposed.collides_any(obstacles)) {
        sprite.set_x(sprite.x() + dx);
        sprite.set_y(sprite.y() + dy);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        if (new_dir != last_direction || !animation.has_value()) {
            int start_frame = direction_to_idle_frame(new_dir);
            sprite.set_item(idle_sprite_item); // Ensure correct shape
            animation = bn::create_sprite_animate_action_forever(
                sprite, FRAME_DURATION, idle_sprite_item.tiles_item(),
                start_frame, start_frame + 1, start_frame + 2, start_frame + 3
            );
            last_direction = new_dir;
        }

        if (animation.has_value() && !animation->done()) {
            animation->update();
        }
    } else {
        if (animation.has_value()) {
            animation.reset();
        }
        sprite.set_item(idle_sprite_item, direction_to_idle_frame(last_direction));
    }
}

void Player::attack() {
    if (is_attacking) return;

    is_attacking = true;
    attack_timer = ATTACK_DURATION;
    update_attack_hitbox();

    int start_frame = direction_to_attack_frame(last_direction);

    if (animation.has_value()) {
        animation.reset();
    }

    sprite.set_item(attack_sprite_item); // Ensure correct shape/tile set
    animation = bn::create_sprite_animate_action_once(
        sprite, 4, attack_sprite_item.tiles_item(),
        start_frame, start_frame + 1, start_frame + 2, start_frame + 3
    );
}

void Player::update_attack_hitbox() {
    bn::fixed ax = sprite.x();
    bn::fixed ay = sprite.y();

    if (last_direction == 0) { ax -= 16; }
    else if (last_direction == 1) { ax += 16; }
    else if (last_direction == 2) { ay -= 16; }
    else if (last_direction == 3) { ay += 16; }

    attack_hitbox = {ax, ay, 16, 16};
}

Hitbox Player::get_hitbox() const {
    return hitbox;
}

Hitbox Player::get_attack_hitbox() const {
    return attack_hitbox;
}

void Player::increase_score() {
    ++score;
}

const bn::sprite_ptr& Player::get_sprite() const {
    return sprite;
}

bool Player::is_attacking_now() const {
    return is_attacking;
}

void Player::set_camera(bn::camera_ptr& camera) {
    sprite.set_camera(camera);
}
