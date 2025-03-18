#include "../include/coin.h"
#include "bn_math.h"

Coin::Coin(int x, int y) 
    : sprite(bn::sprite_items::coin_animated.create_sprite(x, y)), 
      hitbox{x, y, 16, 16}, 
      animation(bn::create_sprite_animate_action_forever(
          sprite, 10, bn::sprite_items::coin_animated.tiles_item(),
          0, 1, 2, 3, 4, 5, 6, 7
      )) {}

void Coin::update_animation() {
    animation.update();
}

void Coin::respawn(bn::random& random_generator, const bn::vector<Hitbox, 10>& obstacles) {
    bool valid_position = false;

    while (!valid_position) {
        bn::fixed new_x = random_generator.get_int(-110, 110);
        bn::fixed new_y = random_generator.get_int(-80, 80);
        Hitbox new_coin_hitbox = {new_x, new_y, hitbox.width, hitbox.height};

        // Check if new position collides with any obstacles
        valid_position = true;
        for (const Hitbox& obstacle : obstacles) {
            if (new_coin_hitbox.collides(obstacle)) {
                valid_position = false;
                break;  // Retry spawning
            }
        }

        if (valid_position) {
            sprite.set_x(new_x);
            sprite.set_y(new_y);
            hitbox.x = new_x;
            hitbox.y = new_y;
        }
    }
}

Hitbox Coin::get_hitbox() const {
    return hitbox;
}

const bn::sprite_ptr& Coin::get_sprite() const { // Ensured const return reference
    return sprite;
}
