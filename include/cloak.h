#ifndef CLOAK_H
#define CLOAK_H

#include "bn_sprite_ptr.h"
#include "bn_optional.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_cloak.h"
#include "../include/hitbox.h"
#include "bn_camera_actions.h"

class Cloak {
public:
    Cloak(int x, int y, const bn::sprite_item& item);
    void update(const bn::sprite_ptr& target, const bn::vector<Hitbox, 10>& obstacles);
    const Hitbox& get_hitbox() const;
    void set_camera(bn::camera_ptr& camera) {sprite.set_camera(camera);}

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    bool chasing_player;
    int last_direction;
    
    // **Fix: Declare animation as an optional animation action**
    bn::optional<bn::sprite_animate_action<4>> animation;
};

#endif
