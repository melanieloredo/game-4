#include "../include/fire_worm.h"
#include "bn_sprite_items_fire_worm.h"
#include "bn_math.h"

FireWorm::FireWorm(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)),
      hitbox{x, y, 16, 16},
      fire_cooldown(0)
{
    sprite.set_tiles(bn::sprite_items::fire_worm.tiles_item(), 0);
    using_attack_frame = false;
    for (int i = 0; i < 10; ++i) {
        fireballs.push_back(Fireball());
    }
}

void FireWorm::update(const bn::fixed_point& target_position, const bn::vector<Hitbox, 10>&) {
    if (!sprite.visible()) {
        deactivate_all_fireballs();
        return;
    }

    bn::fixed dx = target_position.x() - sprite.x();
    bn::fixed dy = target_position.y() - sprite.y();
    bn::fixed distance = bn::sqrt(dx * dx + dy * dy);

    bool attacking = false;

    if (distance < 96 && fire_cooldown <= 0) {
        for (Fireball& f : fireballs) {
            if (!f.is_active()) {
                bn::fixed speed = 1.5;
                bn::fixed norm_dx = (dx / distance) * speed;
                bn::fixed norm_dy = (dy / distance) * speed;

                bn::fixed_point pos = sprite.position();
                f.launch(int(pos.x()), int(pos.y() - 4), norm_dx, norm_dy, *sprite.camera());

                if (!using_attack_frame) {
                    sprite.set_tiles(bn::sprite_items::fire_worm.tiles_item(), 1);
                    using_attack_frame = true;
                }

                fire_cooldown = 90;
                attacking = true;
                break;
            }
        }
    }

    if (!attacking && fire_cooldown < 80 && using_attack_frame) {
        sprite.set_tiles(bn::sprite_items::fire_worm.tiles_item(), 0);
        using_attack_frame = false;
    }

    for (Fireball& f : fireballs) {
        f.update();
    }

    if (fire_cooldown > 0) {
        --fire_cooldown;
    }
}

void FireWorm::deactivate_all_fireballs() {
    for (Fireball& f : fireballs) {
        f.deactivate();
    }
}

const Hitbox& FireWorm::get_hitbox() const {
    return hitbox;
}

bn::sprite_ptr& FireWorm::get_sprite() {
    return sprite;
}

const bn::sprite_ptr& FireWorm::get_sprite() const {
    return sprite;
}

const bn::vector<Fireball, 10>& FireWorm::get_fireballs() const {
    return fireballs;
}
