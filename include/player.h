#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_optional.h"
#include "bn_vector.h"
#include "bn_camera_ptr.h"
#include "hitbox.h"

class Player {
public:
    Player(int x, int y,
           const bn::sprite_item& idle_item,
           const bn::sprite_item& attack_item,
           const bn::sprite_item& dash_item);

    void update(const bn::vector<Hitbox, 10>& obstacles);
    void set_camera(bn::camera_ptr& camera);

    Hitbox get_hitbox() const;
    Hitbox get_attack_hitbox() const;
    const bn::sprite_ptr& get_sprite() const;

    void increase_score();

    bool is_attacking_now() const;
    bool is_dashing_now() const;

private:
    bn::sprite_ptr sprite;
    const bn::sprite_item& idle_sprite_item;
    const bn::sprite_item& attack_sprite_item;
    const bn::sprite_item& dash_sprite_item;

    Hitbox hitbox;
    Hitbox attack_hitbox;

    int last_direction; // 0 left, 1 right, 2 up, 3 down
    int score;

    bool is_attacking;
    int attack_timer;

    bool is_dashing;
    int dash_timer;

    bn::optional<bn::sprite_animate_action<4>> animation;

    void attack();
    void dash();
    void update_attack_hitbox();
};

#endif
