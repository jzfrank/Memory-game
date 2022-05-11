//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_GAME_STATE_H
#define MEMORY_GAME_GAME_STATE_H

#include <vector>
#include <string>
#include "../cards/card.h"
#include "../cards/card_board.h"

class game_state {
private:
    card_board * _card_board;
public:
    game_state();
    ~game_state();

    // accessors
    card_board* get_card_board();
};
#endif //MEMORY_GAME_GAME_STATE_H
