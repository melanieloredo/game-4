#ifndef HITBOX_H
#define HITBOX_H

#include "bn_fixed.h"
#include "bn_vector.h"

struct Hitbox {
    bn::fixed x, y, width, height;

    bool collides(const Hitbox& other) const {
        return (x < other.x + other.width && x + width > other.x &&
                y < other.y + other.height && y + height > other.y);
    }

    bool collides_any(const bn::vector<Hitbox, 10>& obstacles) const {
        for (const Hitbox& obstacle : obstacles) {
            if (collides(obstacle)) {
                return true;
            }
        }
        return false;
    }
};

#endif // HITBOX_H
