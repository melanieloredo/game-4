#ifndef BAT_H
#define BAT_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_sprite_animate_actions.h"
#include "hitbox.h"
#include "bn_camera_actions.h"

class Bat {
public:
    Bat(int x, int y, const bn::sprite_item& item);

    void update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>& obstacles);
    const Hitbox& get_hitbox() const;
    bn::sprite_ptr& get_sprite();                    // Non-const access
    const bn::sprite_ptr& get_sprite() const;        // Const-safe access
    void set_camera(bn::camera_ptr& camera) {sprite.set_camera(camera);}

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

    bn::optional<bn::sprite_animate_action<4>> animation;
    bn::fixed_point previous_position;

    void move_in_direction(bn::fixed dx, bn::fixed dy, bn::fixed speed, const bn::vector<Hitbox, 10>& obstacles);
    void stop_animation();
};

#endif
