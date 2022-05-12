//
// Created by Jin on 5/11/22.
//

#include "CardBoard.h"
#include <algorithm>
#include <random>
#include <vector>

CardBoard::CardBoard() {
    this->row_num = 3;
    this->col_num = 4;
    this->cards_num = this->row_num * this->col_num;
    std::vector<std::string> cards_values = std::vector<std::string>(this->cards_num);
    for (int i=0; i < this->cards_num; i++) {
        if (i % 2 == 0) {
            cards_values[i] = "K";
        }
        else {
            cards_values[i] = "Q";
        }
    }
    // TODO: implement shuffle

    for (int i=0; i < this->row_num; i++) {
        this->_cards.push_back(std::vector<Card *>(col_num));
        for (int j = 0; j < this->col_num; j++) {
            this->_cards[i][j] = new Card(cards_values[col_num * i + j]);
        }
    }
}

CardBoard::~CardBoard() {
    for (int i=0; i < this->_cards.size(); i++) {
        for (int j=0; j < this->_cards[i].size(); j++) {
            delete this->_cards[i][j];
        }
        this->_cards[i].clear();
    }
    this->_cards.clear();
}

std::vector<std::vector<Card *>> CardBoard::getCards() {
    return this->_cards;
}

bool CardBoard::isVanishable(int r1, int c1, int r2, int c2) {
    // check if the given positions are valid
    if ((r1 < 0 || r1 >= this->_cards.size() || r2 < 0 || r2 >= this->_cards.size())
    ||  (c1 < 0 || c1 >= this->_cards[0].size() || c2 < 0 || c2 >= this->_cards[0].size()) )
    {
        return false;
    }
    // check if two cards are of same value
    if (r1 == r2 && c1 == c2) {
        // the same card
        return false;
    }
    else if (this->_cards[r1][c1] == nullptr || this->_cards[r2][c2] == nullptr) {
        // cards already vanished
        return false;
    }
    else if (this->_cards[r1][c1]->getValue() == this->_cards[r2][c2]->getValue()) {
        return true;
    }
    else {
        return false;
    }
}

void CardBoard::vanishPairs(int r1, int c1, int r2, int c2) {
    if (! this->isVanishable(r1, c1, r2, c2)) {
        return;
    }
    else {
        Card * old_card = this->_cards[r1][c1];
        this->_cards[r1][c1] = nullptr;
        delete old_card;
        old_card = this->_cards[r2][c2];
        this->_cards[r2][c2] = nullptr;
        delete old_card;

//        std::cout << "_cards[r2][c2] is nullptr: " << (_cards[r2][c2] == nullptr) << std::endl;
        this->cards_num -= 2;
        this->turned_cards_position.clear();
    }
}

void CardBoard::flipCard(int row, int col) {
    if (this->_cards[row][col] != nullptr
    && !this->_cards[row][col]->getIsFront()
    && this->turned_cards_position.size() < 2)
    {
        this->_cards[row][col]->flip();
        this->turned_cards_position.push_back(std::vector<int>{row, col});
//        if (this->turned_cards_position.size() == 2) {
//            this->vanishPairs(
//                    this->turned_cards_position[0][0], this->turned_cards_position[0][1],
//                    this->turned_cards_position[1][0], this->turned_cards_position[1][1]
//            );
//        }
    }

}

int CardBoard::getAvailableCards() {
    return this->cards_num;
}

bool CardBoard::processEndGame() {
    return this->cards_num == 0;
}

int CardBoard::getNofTurnedCards() {
    return this->turned_cards_position.size();
}

std::vector<std::vector<int>> CardBoard::get_turned_cards_position() {
    return this->turned_cards_position;
}