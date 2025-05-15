#include "../include/bat.h"
#include "bn_math.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_bat.h"

Bat::Bat(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)),
      hitbox{x, y, 16, 16},
      is_dashing(false),
      is_preparing_dash(false),
      dash_timer(0),
      pause_timer(0),
      dash_cooldown(0),
      pre_dash_timer(0),
      dash_direction_x(0),
      dash_direction_y(0),
      dash_speed(2.0),
      fly_speed(0.5),
      animation(bn::nullopt),
      previous_position(sprite.position()) {}

void Bat::update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>& obstacles) {
    if (pause_timer > 0) {
        --pause_timer;

        if (!animation.has_value()) {
            animation = bn::create_sprite_animate_action_forever(
                sprite, 10, bn::sprite_items::bat.tiles_item(), 0, 1, 2, 3
            );
        }

        if (animation.has_value()) {
            animation->update();
        }

        return;
    }

    if (is_preparing_dash) {
        if (--pre_dash_timer <= 0) {
            is_preparing_dash = false;
            is_dashing = true;
            dash_timer = 40;
        }
        stop_animation();
        return;
    }

    bn::fixed dx = target_position.x() - sprite.x();
    bn::fixed dy = target_position.y() - sprite.y();
    bn::fixed distance = bn::sqrt(dx * dx + dy * dy);

    if (is_dashing) {
        if (dash_timer > 0) {
            --dash_timer;
            move_in_direction(dash_direction_x, dash_direction_y, dash_speed, obstacles);
        } else {
            is_dashing = false;
            pause_timer = 300;
        }

        if (!animation.has_value()) {
            animation = bn::create_sprite_animate_action_forever(
                sprite, 5, bn::sprite_items::bat.tiles_item(), 0, 1, 2, 3
            );
        }

        previous_position = sprite.position();

        if (animation.has_value()) {
            animation->update();
        }

        return;
    }

    if (distance < 50 && dash_cooldown <= 0) {
        is_preparing_dash = true;
        pre_dash_timer = 30;
        dash_direction_x = dx / distance;
        dash_direction_y = dy / distance;
        dash_cooldown = 60;
        stop_animation();
        return;
    }

    if (dash_cooldown > 0) {
        --dash_cooldown;
    }

    // Flip sprite only when flying normally
    if (!is_dashing && !is_preparing_dash) {
        if (dx > 0.5) {
            sprite.set_horizontal_flip(true);  // Face right
        } else if (dx < -0.5) {
            sprite.set_horizontal_flip(false); // Face left
        }
    }

    bn::fixed move_dx = 0;
    bn::fixed move_dy = 0;

    if (distance > 1) {
        move_dx = (dx / distance) * fly_speed;
        move_dy = (dy / distance) * fly_speed;
        move_in_direction(move_dx, move_dy, 1, obstacles);
    }

    bn::fixed movement_dx = sprite.x() - previous_position.x();
    bn::fixed movement_dy = sprite.y() - previous_position.y();
    bn::fixed movement_distance = bn::sqrt(movement_dx * movement_dx + movement_dy * movement_dy);

    if (movement_distance > 0.1) {
        if (!animation.has_value()) {
            animation = bn::create_sprite_animate_action_forever(
                sprite, 10, bn::sprite_items::bat.tiles_item(), 0, 1, 2, 3
            );
        }
    } else {
        stop_animation();
    }

    previous_position = sprite.position();

    if (animation.has_value()) {
        animation->update();
    }
}

void Bat::move_in_direction(bn::fixed dx, bn::fixed dy, bn::fixed speed, const bn::vector<Hitbox, 10>& obstacles) {
    bn::fixed new_x = sprite.x() + dx * speed;
    bn::fixed new_y = sprite.y() + dy * speed;
    Hitbox future_hitbox = {new_x, new_y, hitbox.width, hitbox.height};

    if (!future_hitbox.collides_any(obstacles)) {
        sprite.set_x(new_x);
        sprite.set_y(new_y);
        hitbox.x = new_x;
        hitbox.y = new_y;
    }
}

void Bat::stop_animation() {
    if (animation.has_value()) {
        animation.reset();
        sprite.set_tiles(bn::sprite_items::bat.tiles_item(), 0);
    }
}

const Hitbox& Bat::get_hitbox() const {
    return hitbox;
}

bn::sprite_ptr& Bat::get_sprite() {
    return sprite;
}

const bn::sprite_ptr& Bat::get_sprite() const {
    return sprite;
}
