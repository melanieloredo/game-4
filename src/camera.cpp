#include "../include/camera.h"

namespace camera_system {

    void update_camera(bn::camera_ptr& camera, const bn::fixed_point& target_position,
                       bn::fixed min_x, bn::fixed max_x,
                       bn::fixed min_y, bn::fixed max_y,
                       bn::fixed follow_speed) {

        bn::fixed cam_x = camera.x();
        bn::fixed cam_y = camera.y();

        // Clamp target position
        bn::fixed target_x = bn::min(max_x, bn::max(min_x, target_position.x()));
        bn::fixed target_y = bn::min(max_y, bn::max(min_y, target_position.y()));

        // Lerp camera position towards target
        bn::fixed new_cam_x = cam_x + (target_x - cam_x) * follow_speed;
        bn::fixed new_cam_y = cam_y + (target_y - cam_y) * follow_speed;

        camera.set_position(new_cam_x, new_cam_y);
    }

}