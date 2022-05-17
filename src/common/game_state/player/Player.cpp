//
// Created by Jin on 5/12/22.
//

#include "Player.h"
#include "../../exceptions/MemoryException.h"

Player::Player(std::string name, int score) : unique_serializable() {
    this->_player_name = new serializable_value<std::string> (name);
    this->_score = new serializable_value<int> (score);
}

Player::Player(std::string id, serializable_value<std::string> *name,
               serializable_value<int> *score) :
               unique_serializable(id),
               _player_name(name),
               _score(score)
{ }

Player::~Player() {
    if (_player_name != nullptr) {
        delete _player_name;
        delete _score;

        _player_name = nullptr;
        _score = nullptr;
    }
}

#ifdef MEMORY_SERVER
Player::Player(std::string id, std::string name, int score) :
    unique_serializable(id)
{
    this->_player_name = new serializable_value<std::string>(name);
    this->_score = new serializable_value<int>(score);
}

std::string Player::get_game_id() {
    return _game_id;
}

void Player::set_game_id(std::string game_id) {
    _game_id = game_id;
}
#endif

int Player::get_score() const noexcept {
    return _score->get_value();
}

std::string Player::get_player_name() const noexcept {
    return _player_name->get_value();
}


void Player::set_score(int score) {
    _score->set_value(score);
}
#ifdef MEMORY_SERVER
// state update functions
    // TODO: implement this similar to LAMA's player

void Player::wrap_up_round(std::string &err) {}
void Player::setup_round(std::string &err) {}
#endif

void Player::write_into_json(rapidjson::Value &json, rapidjson::Document::AllocatorType &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    rapidjson::Value id_val(_id.c_str(), allocator);
    json.AddMember("id", id_val, allocator);

    rapidjson::Value name_val(rapidjson::kObjectType);
    _player_name->write_into_json(name_val, allocator);
    json.AddMember("player_name", name_val, allocator);

    rapidjson::Value score_val(rapidjson::kObjectType);
    _score->write_into_json(score_val, allocator);
    json.AddMember("score", score_val, allocator);
}

Player *Player::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id")
        && json.HasMember("player_name")
        && json.HasMember("score"))
    {
        return new Player(json["id"].GetString(),
                          serializable_value<std::string>::from_json(json["player_name"].GetObject()),
                          serializable_value<int>::from_json(json["score"].GetObject()));
    } else {
        throw MemoryException("Failed to deserialize player from json. Required json entries were missing.");
    }
}