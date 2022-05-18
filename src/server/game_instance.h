//
// Created by Jin on 5/14/22.
//

#ifndef MEMORY_GAME_GAME_INSTANCE_H
#define MEMORY_GAME_GAME_INSTANCE_H

#include <vector>
#include <string>
#include <mutex>

#include "../common/game_state/player/Player.h"
#include "../common/game_state/GameState.h"

class game_instance {
private:
    GameState* _game_state;
    bool is_player_allowed_to_play(Player * player);
    inline static std::mutex modification_lock;
public:
    game_instance();
    ~game_instance() {
        if (_game_state != nullptr) {
            delete _game_state;
        }
        _game_state = nullptr;
    }
    std::string get_id();

    GameState* get_game_state();

    bool is_full();
    bool is_started();
    bool is_finished();

    // game update functions
    bool start_game(Player * player, std::string & err);
    bool try_add_player(Player * new_player, std::string & err);
    bool try_remove_player(Player * player, std::string & err);
    bool flip_card(Player * player, int row, int col, std::string & err);
    bool shuffle(Player * player, std::string & err);

};


#endif //MEMORY_GAME_GAME_INSTANCE_H
