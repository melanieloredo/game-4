#ifndef CLOAK_H
#define CLOAK_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_fixed_point.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_sprite_animate_actions.h"
#include "hitbox.h"
#include "bn_camera_actions.h"

class Cloak {
public:
    Cloak(int x, int y, const bn::sprite_item& item);

    void update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>& obstacles);
    const Hitbox& get_hitbox() const;

    bn::sprite_ptr& get_sprite();                    
    const bn::sprite_ptr& get_sprite() const;        

    void set_camera(bn::camera_ptr& camera) {sprite.set_camera(camera);}

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    int last_direction;
    bool chasing_player;
    bn::optional<bn::sprite_animate_action<4>> animation;
};

#endif
