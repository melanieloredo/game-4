#ifndef COIN_H
#define COIN_H

#include "bn_sprite_ptr.h"
#include "bn_random.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_coin_animated.h"
#include "../include/hitbox.h"

class Coin {
public:
    Coin(int x, int y);

    void update_animation();
    void respawn(bn::random& random_generator, const bn::vector<Hitbox, 10>& obstacles); // Updated signature

    Hitbox get_hitbox() const;
    const bn::sprite_ptr& get_sprite() const; // Ensure const reference return type

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    bn::sprite_animate_action<8> animation;
};

#endif
