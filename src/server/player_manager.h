//
// Created by Jin on 5/14/22.
//

#ifndef MEMORY_GAME_PLAYER_MANAGER_H
#define MEMORY_GAME_PLAYER_MANAGER_H

#include <string>
#include <shared_mutex>
#include <unordered_map>

#include "../common/game_state/player/Player.h"

class player_manager {

private:

    inline static std::shared_mutex _rw_lock;
    static std::unordered_map<std::string, Player*> _players_lut;

public:
    static bool try_get_player(const std::string& player_id, Player*& player_ptr);
    static bool add_or_get_player(std::string name, const std::string& player_id, Player*& player_ptr);
    static bool remove_player(const std::string& player_id, Player*& player);  // not implemented
};


#endif //MEMORY_GAME_PLAYER_MANAGER_H
