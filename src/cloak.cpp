#include "../include/cloak.h"
#include "bn_math.h"
#include "bn_sprite_items_cloak.h"

Cloak::Cloak(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)),
      hitbox{x, y, 16, 16},
      last_direction(3),
      chasing_player(false),
      animation(bn::nullopt) {}

void Cloak::update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>& obstacles) {
    bn::fixed dx = target_position.x() - sprite.x();
    bn::fixed dy = target_position.y() - sprite.y();
    bn::fixed distance = bn::sqrt(dx * dx + dy * dy);

    chasing_player = distance < 80;

    if (!chasing_player || distance < 24) {
        if (animation.has_value()) {
            animation.reset();
        }

        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(bn::sprite_items::cloak.tiles_item(), idle_frame);
        return;
    }

    bn::fixed move_speed = 0.8;
    dx = (dx / distance) * move_speed;
    dy = (dy / distance) * move_speed;

    Hitbox new_position = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    if (!new_position.collides_any(obstacles)) {
        sprite.set_x(new_position.x);
        sprite.set_y(new_position.y);
        hitbox.x = new_position.x;
        hitbox.y = new_position.y;

        int new_direction = (bn::abs(dx) > bn::abs(dy)) ? ((dx > 0) ? 1 : 0)
                                                        : ((dy > 0) ? 3 : 2);

        if (new_direction != last_direction || !animation.has_value()) {
            int start_frame = (new_direction == 0) ? 8
                            : (new_direction == 1) ? 12
                            : (new_direction == 2) ? 4
                            : 0;

            animation = bn::create_sprite_animate_action_forever(
                sprite, 8, bn::sprite_items::cloak.tiles_item(),
                start_frame, start_frame + 1, start_frame + 2, start_frame + 3
            );

            last_direction = new_direction;
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
        sprite.set_tiles(bn::sprite_items::cloak.tiles_item(), idle_frame);
    }
}

const Hitbox& Cloak::get_hitbox() const {
    return hitbox;
}

bn::sprite_ptr& Cloak::get_sprite() {
    return sprite;
}

const bn::sprite_ptr& Cloak::get_sprite() const {
    return sprite;
}
