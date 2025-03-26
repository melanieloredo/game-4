#ifndef CAMERA_H
#define CAMERA_H

#include "bn_camera_ptr.h"
#include "bn_fixed_point.h"

namespace camera_system {

    void update_camera(bn::camera_ptr& camera, const bn::fixed_point& target_position, 
                       bn::fixed min_x = -320 + 240, bn::fixed max_x = 320 - 240, //world dims - screen dims
                       bn::fixed min_y = -240 + 160,  bn::fixed max_y = 240 - 160,
                       bn::fixed follow_speed = 0.1);

}

#endif 