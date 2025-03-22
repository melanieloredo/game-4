#include "../include/cloak.h"
#include "bn_math.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_cloak.h"

Cloak::Cloak(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)), hitbox{x, y, 16, 16}, last_direction(3), animation(bn::nullopt) {}

void Cloak::update(const bn::sprite_ptr& target, const bn::vector<Hitbox, 10>& obstacles) {
    bn::fixed dx = target.x() - sprite.x();
    bn::fixed dy = target.y() - sprite.y();
    bn::fixed distance = bn::sqrt(dx * dx + dy * dy);

    // Field of vision: start chasing if within 80px
    if (distance < 80) {
        chasing_player = true;
    } else {
        chasing_player = false;
    }

    // Stop moving when too close (within 24px)
    if (!chasing_player || distance < 24) {
        if (animation.has_value()) {
            animation.reset(); // Stop animation when idle
        }
        // Set idle frame
        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(bn::sprite_items::cloak.tiles_item(), idle_frame);
        return;
    }

    // Normalize movement direction
    bn::fixed move_speed = 0.8;
    dx = (dx / distance) * move_speed;
    dy = (dy / distance) * move_speed;

    // Predict new position
    Hitbox new_position = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    // Move if no collision
    if (!new_position.collides_any(obstacles)) {
        sprite.set_x(new_position.x);
        sprite.set_y(new_position.y);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        // Determine direction based on movement
        int new_direction = (bn::abs(dx) > bn::abs(dy)) ? ((dx > 0) ? 1 : 0) 
                                                        : ((dy > 0) ? 3 : 2);

        // Update animation if direction changed or if animation is missing
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
        animation->update();
    } else {
        // Stop animation if movement is blocked
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
