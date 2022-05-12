//
// Created by Jin on 5/11/22.
//

#include "GameState.h"

GameState::GameState() {
    this->_cardBoard = new CardBoard();
}

GameState::~GameState() {
    delete this->_cardBoard;
}

void GameState::flipCard(int row, int col) {
    this->_cardBoard->flipCard(row, col);
}

CardBoard *GameState::getCardBoard() {
    return this->_cardBoard;
}