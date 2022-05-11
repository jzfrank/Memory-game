//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARD_BOARD_H
#define MEMORY_GAME_CARD_BOARD_H

#include <string>
#include <vector>
#include "card.h"

class card_board {
private:
    std::vector<std::vector<card*>> _cards;
    int row_num;
    int col_num;

public:
    card_board();
    ~card_board();

    //accessors
    std::vector<std::vector<card*>> get_cards();
};
#endif //MEMORY_GAME_CARD_BOARD_H
