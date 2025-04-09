#include "../include/game_scene.h"
#include "../include/titlescreen.h"  // include your title screen
#include "bn_core.h"

int main() {
    bn::core::init();
    titlescreen();  // Show title screen first

    sprites_animation_actions_scene();
    
    return 0;
}
