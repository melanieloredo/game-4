#include "../include/heart.h"
#include "bn_math.h"

Heart::Heart(int x, int y)
    : sprite(bn::sprite_items::heart.create_sprite(x, y)),
      hitbox{x, y, 16, 16} {
    
    sprite.set_scale(0.5);
    sprite.set_tiles(bn::sprite_items::heart.tiles_item(), 0);  // static frame 0 (full heart)
}


void Heart::respawn(bn::random& random_generator, const bn::vector<Hitbox, 10>& obstacles) {
    bool valid_position = false;

    while (!valid_position) {
        bn::fixed new_x = random_generator.get_int(-110, 110);
        bn::fixed new_y = random_generator.get_int(-80, 80);
        Hitbox new_heart_hitbox = {new_x, new_y, hitbox.width, hitbox.height};

        valid_position = true;
        for (const Hitbox& obstacle : obstacles) {
            if (new_heart_hitbox.collides(obstacle)) {
                valid_position = false;
                break; 
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

Hitbox Heart::get_hitbox() const {
    return hitbox;
}

const bn::sprite_ptr& Heart::get_sprite() const { // Ensured const return reference
    return sprite;
}
