//
// Created by Jin on 5/11/22.
//

#include "GameState.h"

GameState::GameState() {
    this->_players = std::vector<Player *>();
    this->_cardBoard = new CardBoard();
    this->_is_started = false;
    this->_is_finished = false;
    this->_round_number = 0;
    this->_current_player_idx = 0;
    this->_starting_player_idx = 0;
}

GameState::~GameState() {
    delete this->_cardBoard;
}

void GameState::flipCard(int row, int col) {
    this->_cardBoard->flipCard(row, col);
}

bool GameState::is_full() const {
    return _players.size() == _max_nof_players;
}

bool GameState::is_started() const {
    return _is_started;
}

bool GameState::is_finished() const {
    return _is_finished;
}

bool GameState::is_player_in_game(Player *player) const {\
    return (std::find(_players.begin(), _players.end(), player)
            < _players.end());
}

bool GameState::is_allowed_to_play_now(Player *player) const {
    return player == get_current_player();
}

std::vector<Player *> &GameState::get_players() {
    return _players;
}

int GameState::get_round_number() const {
    return _round_number;
}

CardBoard *GameState::getCardBoard() {
    return this->_cardBoard;
}

Player *GameState::get_current_player() const {
    if (_players.size() == 0) {
        return nullptr;
    }
    return _players[_current_player_idx];
}