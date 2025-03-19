#ifndef CLOAK_H
#define CLOAK_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_cloak.h"
#include "bn_optional.h"
#include "bn_vector.h"
#include "hitbox.h"

class Cloak {
public:
    Cloak(int x, int y, const bn::sprite_item& item);
    void update(const bn::sprite_ptr& target, const bn::vector<Hitbox, 10>& obstacles);
    Hitbox get_hitbox() const;
    void increase_score();

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    int last_direction;
    int score;
    bn::optional<bn::sprite_animate_action<4>> animation;
};

#endif // CLOAK_H
