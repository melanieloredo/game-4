#include "bn_core.h"
#include "../include/heart_ui.h"
#include "bn_sprite_tiles_ptr.h" //tile header
#include "bn_sprite_ptr.h" //sprites

#include "bn_sprite_builder.h" //sprite builder
#include "bn_sprite_items_heart.h" //heart sprite

HeartUI::HeartUI(int max_hearts) : //constructor
    _max_hearts(max_hearts), _current_health(max_hearts), heart_spacing(16) //max hearts = number of hearts player can have
{

    for(int i = 0; i < _max_hearts; ++i) //loop for each heart to display
    {
        bn::sprite_builder builder(bn::sprite_items::heart); // <-- Create a builder

        int x = i * heart_spacing;
        int y = 10; // 10px from top

        builder.set_position(x, y);
        builder.set_bg_priority(0);
        builder.set_scale(0.5f); 

        _heart_sprites.push_back(builder.release_build()); // <-- Build and store the sprite

    }
}

void HeartUI::set_health(float current_health) //update visuals
{
    _current_health = current_health;

    for(int i = 0; i < _max_hearts; ++i) //go through each heart sprite
    {
        int frame = 2;  // default to empty <--

        if(current_health >= i + 1)
        {
            frame = 0; // full
        }
        else if(current_health >= i + 0.5f)
        {
            frame = 1; // half
        }

        _heart_sprites[i].set_tiles(
            bn::sprite_items::heart.tiles_item().create_tiles(frame) //update to current health
        );
    }
}

void HeartUI::set_position(int x, int y) //for the heart bar
{
    
    for(int i = 0; i < _max_hearts; ++i)
    {
        int heart_x = x + i * heart_spacing;
        _heart_sprites[i].set_position(heart_x, y);
    }
}