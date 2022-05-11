//
// Created by Jin on 5/11/22.
//

#include "card_board.h"

card_board::card_board() {
    this->row_num = 3;
    this->col_num = 4;
    for (int i=0; i < this->row_num; i++) {
        this->_cards.push_back(std::vector<card *>(col_num));
        for (int j = 0; j < this->col_num; j++) {
            this->_cards[i][j] = new card(1);
        }
    }
}

card_board::~card_board() {
    for (int i=0; i < this->_cards.size(); i++) {
        for (int j=0; j < this->_cards[i].size(); j++) {
            delete this->_cards[i][j];
        }
        this->_cards[i].clear();
    }
    this->_cards.clear();
}

std::vector<std::vector<card *>> card_board::get_cards() {
    return this->_cards;
}

