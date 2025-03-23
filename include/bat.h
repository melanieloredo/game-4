#ifndef BAT_H
#define BAT_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "hitbox.h"

class Bat {
public:
    Bat(int x, int y, const bn::sprite_item& item);

    void update(const bn::sprite_ptr& target, const bn::vector<Hitbox, 10>& obstacles);
    const Hitbox& get_hitbox() const;

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;

    bool is_dashing;
    bool is_preparing_dash;
    int dash_timer;
    int pause_timer;
    int dash_cooldown;
    int pre_dash_timer;

    bn::fixed dash_direction_x;
    bn::fixed dash_direction_y;
    bn::fixed dash_speed;
    bn::fixed fly_speed;

    void move_in_direction(bn::fixed dx, bn::fixed dy, bn::fixed speed, const bn::vector<Hitbox, 10>& obstacles);
};

#endif