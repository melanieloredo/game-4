#ifndef HEART_UI_H
#define HEART_UI_H

#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h" 
#include "bn_sprite_builder.h" //we use builder now

class HeartUI
{
public:
    HeartUI(int max_hearts);

    void set_health(float current_health);  // can be half values like 2.5
    void set_position(int x, int y);

   private:
    int _max_hearts;
    float _current_health;
    int heart_spacing;

    bn::vector<bn::sprite_ptr, 10> _heart_sprites;
};

#endif
