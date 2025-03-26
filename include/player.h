#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_optional.h"
#include "bn_vector.h"
#include "hitbox.h"
#include "bn_camera_actions.h"

class Player {
public:
    Player(int x, int y, const bn::sprite_item& item);
    void update(const bn::vector<Hitbox, 10>& obstacles);
    Hitbox get_hitbox() const;
    void increase_score();
    const bn::sprite_ptr& get_sprite() const { return sprite; }
    void set_camera(bn::camera_ptr& camera) {sprite.set_camera(camera);}

private:
    bn::sprite_ptr sprite;
    Hitbox hitbox;
    int last_direction;
    int score;
    bn::optional<bn::sprite_animate_action<4>> animation;
};

#endif // PLAYER_H
