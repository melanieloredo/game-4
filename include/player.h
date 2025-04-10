#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_optional.h"
#include "bn_vector.h"
#include "hitbox.h"
#include "bn_camera_ptr.h"

class Player {
public:
    Player(int x, int y, const bn::sprite_item& idle_item, const bn::sprite_item& attack_item);
    void update(const bn::vector<Hitbox, 10>& obstacles);
    Hitbox get_hitbox() const;
    Hitbox get_attack_hitbox() const;
    void increase_score();
    const bn::sprite_ptr& get_sprite() const { return sprite; }
    void set_camera(bn::camera_ptr& camera) { sprite.set_camera(camera); }
    bool is_attacking_now() const { return is_attacking; }

private:
    bn::sprite_ptr sprite;
    const bn::sprite_item& idle_sprite_item;
    const bn::sprite_item& attack_sprite_item;

    Hitbox hitbox;
    Hitbox attack_hitbox;

    int last_direction;
    int score;

    bool is_attacking;
    int attack_timer;

    bn::optional<bn::sprite_animate_action<4>> animation;

    void attack();
    void update_attack_hitbox();
};

#endif
