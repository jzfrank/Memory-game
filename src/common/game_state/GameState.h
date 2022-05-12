//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_GAMESTATE_H
#define MEMORY_GAME_GAMESTATE_H

#include <vector>
#include <string>
#include "cards/Card.h"
#include "cards/CardBoard.h"
#include "player/Player.h"

class GameState {
private:
    static const int _max_nof_players = 6;
    static const int _min_nof_players = 2;

    std::vector<Player *> _players;
    CardBoard * _cardBoard;
    bool _is_started;
    bool _is_finished;
    int _round_number;
    int _current_player_idx;
    int _starting_player_idx;

public:
    GameState();
    ~GameState();

    void flipCard(int row, int col);

    // accessors
    bool is_full() const;
    bool is_started() const;
    bool is_finished() const;
    bool is_player_in_game(Player* player) const;
    bool is_allowed_to_play_now(Player * player) const;
    std::vector<Player *> & get_players();
    int get_round_number() const;

    CardBoard* getCardBoard();
    Player * get_current_player() const;

};
#endif //MEMORY_GAME_GAMESTATE_H
