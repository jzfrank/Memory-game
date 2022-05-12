//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_GAMESTATE_H
#define MEMORY_GAME_GAMESTATE_H

#include <vector>
#include <string>
#include "cards/Card.h"
#include "cards/CardBoard.h"

class GameState {
private:
    CardBoard * _cardBoard;
public:
    GameState();
    ~GameState();

    void flipCard(int row, int col);

    // accessors
    CardBoard* getCardBoard();
};
#endif //MEMORY_GAME_GAMESTATE_H
