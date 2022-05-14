//
// Created by Jin on 5/14/22.
//

#include "player_manager.h"

// Initialize static map
std::unordered_map<std::string, Player*> player_manager::_players_lut = {};

bool player_manager::try_get_player(const std::string& player_id, Player *&player_ptr) {
    player_ptr = nullptr;
    _rw_lock.lock_shared();
    auto it = player_manager::_players_lut.find(player_id);
    if (it != _players_lut.end()) {
        player_ptr = it->second;
    }
    _rw_lock.unlock_shared();
    return player_ptr;
}

bool player_manager::add_or_get_player(std::string name, const std::string& player_id, Player *&player_ptr) {
    if (try_get_player(player_id, player_ptr)) {
        return true;
    }
    player_ptr = new Player(player_id, name, 0);
//    player_ptr = new Player(std::string("player_id"), std::string("name"), 0);
    _rw_lock.lock();    // exclusive
    player_manager::_players_lut.insert({player_id, player_ptr});
    _rw_lock.unlock();
    return true;
}

bool player_manager::remove_player(const std::string& player_id, Player *&player) {
    if (try_get_player(player_id, player)) {
        _rw_lock.lock();    // exclusive
        int nof_removals = player_manager::_players_lut.erase(player_id);
        _rw_lock.unlock();
        return true;
    }
    return false;
}

