//
// Created by Jin on 5/12/22.
//

#ifndef MEMORY_GAME_PLAYER_H
#define MEMORY_GAME_PLAYER_H

#include <vector>
#include <string>
#include "../../serialization/uuid_generator.h"
#include "../../../../rapidjson/include/rapidjson/document.h"
#include "../../serialization/unique_serializable.h"
#include "../../serialization/serializable_value.h"

#define MEMORY_SERVER 1

class Player : public unique_serializable {
private:
    serializable_value<std::string> * _player_name;
    serializable_value<int> * _score;

#ifdef MEMORY_SERVER
    std::string _game_id;
#endif

    // deserialization constructor
    Player(std::string id,
           serializable_value<std::string> * name,
           serializable_value<int> * score
           );

public:
    //constructors
    explicit Player(std::string name, int score); // for client
    ~Player();

#ifdef MEMORY_SERVER
    Player(std::string id, std::string name, int score); // for server

    std::string get_game_id();
    void set_game_id(std::string game_id);
#endif

    // accessor
    int get_score() const noexcept;
    std::string get_player_name() const noexcept;

#ifdef MEMORY_SERVER
    // state update functions
    void wrap_up_round(std::string & err);
    void setup_round(std::string & err);
#endif

    // serialization
    static Player* from_json(const rapidjson::Value & json);
    virtual void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType& allocator) const override;
};

#endif //MEMORY_GAME_PLAYER_H
