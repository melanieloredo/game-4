#include "../include/score_manager.h"
//#include "butano_save.h"
#include "bn_string.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "../include/common_fixed_8x8_sprite_font.h"

namespace {
    bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, 32> score_sprites;
}

void ScoreManager::reset() {
    _score = 0;
}

void ScoreManager::add_points(int points) {
    _score += points;
}

void ScoreManager::draw_score(int x, int y) {
    score_sprites.clear();
    bn::string<32> score_text = bn::to_string<32>(_score);
    text_generator.generate(x, y, score_text, score_sprites);
}

int ScoreManager::current_score() const {
    return _score;
}
