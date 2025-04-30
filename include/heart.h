#ifndef HEART_H
#define HEART_H

#include "bn_sprite_ptr.h"
#include "bn_random.h"
#include "bn_sprite_items_heart.h"  
#include "../include/hitbox.h"
#include "bn_camera_actions.h"

class Heart {
public:
    Heart(int x, int y);

    void update_animation();
    void respawn(bn::random& random_generator, const bn::vector<Hitbox, 10>& obstacles); 
    
    Hitbox get_hitbox() const;
    const bn::sprite_ptr& get_sprite() const;
    void set_camera(bn::camera_ptr& camera) {sprite.set_camera(camera);}

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
};

#endif
