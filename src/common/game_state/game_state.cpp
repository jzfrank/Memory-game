//
// Created by Jin on 5/11/22.
//

#include "game_state.h"

game_state::game_state() {
    this->_card_board = new card_board();
}

game_state::~game_state() {
    delete this->_card_board;
}

card_board *game_state::get_card_board() {
    return this->_card_board;
}