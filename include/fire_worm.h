#ifndef FIRE_WORM_H
#define FIRE_WORM_H

#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_fixed_point.h"
#include "bn_optional.h"
#include "bn_sprite_item.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_items_fire_ball.h"
#include "hitbox.h"

struct Fireball {
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    bn::fixed dx;
    bn::fixed dy;
    bool active;

    Fireball()
        : sprite(bn::sprite_items::fire_ball.create_sprite(0, 0)), dx(0), dy(0), active(false)
    {
        sprite.set_visible(false);
    }

    void launch(int x, int y, bn::fixed dx_in, bn::fixed dy_in, const bn::camera_ptr& camera) {
        sprite.set_x(x);
        sprite.set_y(y);
        sprite.set_camera(camera);
        sprite.set_visible(true);
        dx = dx_in;
        dy = dy_in;
        hitbox = Hitbox{x, y, 8, 8};
        active = true;
    }

    void update() {
        if (!active) return;

        sprite.set_x(sprite.x() + dx);
        sprite.set_y(sprite.y() + dy);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        if (sprite.x() < -160 || sprite.x() > 160 || sprite.y() < -120 || sprite.y() > 120) {
            deactivate();
        }
    }

    void deactivate() {
        active = false;
        sprite.set_visible(false);
    }

    bool is_active() const {
        return active;
    }

    const Hitbox& get_hitbox() const {
        return hitbox;
    }
};

class FireWorm {
public:
    FireWorm(int x, int y, const bn::sprite_item& item);

    void update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>& obstacles);
    const Hitbox& get_hitbox() const;

    bn::sprite_ptr& get_sprite();
    const bn::sprite_ptr& get_sprite() const;

    const bn::vector<Fireball, 10>& get_fireballs() const;
    void deactivate_all_fireballs(); // ✅ Declare here

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    bn::vector<Fireball, 10> fireballs;
    int fire_cooldown;
    bool using_attack_frame = false; // ✅ Track current tile state
};

#endif
