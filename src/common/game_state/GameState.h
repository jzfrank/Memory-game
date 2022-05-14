//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_GAMESTATE_H
#define MEMORY_GAME_GAMESTATE_H

#include <vector>
#include <string>
#include "../../rapidjson/include/rapidjson/document.h"
#include "../serialization/serializable.h"
#include "../serialization/serializable_value.h"
#include "../serialization/unique_serializable.h"
#include "cards/Card.h"
#include "cards/CardBoard.h"
#include "player/Player.h"

class GameState : public unique_serializable {
private:

    static const int _max_nof_players = 6;
    static const int _min_nof_players = 2;

    std::vector<Player *> _players;
    CardBoard * _cardBoard;
    serializable_value<bool>* _is_started;
    serializable_value<bool>* _is_finished;
    serializable_value<int>* _round_number;
    serializable_value<int>* _current_player_idx;
    serializable_value<int>* _starting_player_idx;

    // from_diff constructor
    GameState(std::string id);


    // deserialization constructor
    GameState(
            std::string id,
            CardBoard * cardBoard,
            std::vector<Player *> players,
            serializable_value<bool>* is_started,
            serializable_value<bool>* is_finished,
            serializable_value<int>* round_number,
            serializable_value<int>* current_player_idx,
            serializable_value<int>* starting_player_idx
            );


public:
    GameState();
    ~GameState();

    bool flipCard(int row, int col);

    // accessors
    [[nodiscard]] bool is_full() const;
    [[nodiscard]] bool is_started() const;
    [[nodiscard]] bool is_finished() const;
    bool is_player_in_game(Player* player) const;
    bool is_allowed_to_play_now(Player * player) const;
    std::vector<Player *> & get_players();
    [[nodiscard]] int get_round_number() const;

    CardBoard* getCardBoard();
    Player * get_current_player() const;

#ifdef MEMORY_SERVER
// server-side state update functions
    void setup_round(std::string& err);   // server side initialization
    bool remove_player(Player* player, std::string& err);
    bool add_player(Player* player, std::string& err);
    bool start_game(std::string& err);
    bool flipCard(int row, int col, std::string err);

    // end of round functions
    void update_current_player(std::string& err);
    void wrap_up_round(std::string& err);
#endif
// serializable interface
    static GameState * from_json(const rapidjson::Value& json);
    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const;

};
#endif //MEMORY_GAME_GAMESTATE_H
