//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARDBOARD_H
#define MEMORY_GAME_CARDBOARD_H

#include <wx/wx.h>
#include <string>
#include <vector>
#include "Card.h"

class CardBoard {
private:
    std::vector<std::vector<Card*>> _cards;
    int row_num;
    int col_num;
    int cards_num;
    std::vector<std::vector<int>> turned_cards_position; // stores positions of flipped cards

public:
    CardBoard();
    ~CardBoard();

    void flipCard(int row, int col);
    bool isVanishable(int r1, int c1, int r2, int c2); // check if two cards are vanishable
    void vanishPairs(int r1, int c1, int r2, int c2); // vanish a pair of cards if possible
    int getAvailableCards(); // returns the number of available cards on the cardboard
    bool processEndGame(); // check if the number of cards remaining is 0
    //accessors
    std::vector<std::vector<Card*>> getCards();
};
#endif //MEMORY_GAME_CARDBOARD_H
