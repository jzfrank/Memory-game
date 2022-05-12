//
// Created by Jin on 5/12/22.
//

#ifndef MEMORY_GAME_PLAYER_H
#define MEMORY_GAME_PLAYER_H

#include <vector>
#include <string>

class Player {
private:
    std::string _player_name;
    int _score;

    Player(std::string id,
           std::string name);

public:
    //constructors
    explicit Player(std::string name); // for client
    ~Player();
};

#endif //MEMORY_GAME_PLAYER_H
