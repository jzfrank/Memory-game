//
// Created by Jin on 5/11/22.
//

#include "GameState.h"
#include "../exceptions/MemoryException.h"
#include "../serialization/vector_utils.h"

GameState::GameState() : unique_serializable() {
    this->_players = std::vector<Player *>();
    this->_cardBoard = new CardBoard();
    this->_is_started = new serializable_value<bool> (false);
    this->_is_finished = new serializable_value<bool> (false);
    this->_round_number = new serializable_value<int> (0);
    this->_current_player_idx = new serializable_value<int> (0);
    this->_starting_player_idx = new serializable_value<int> (0);
}

GameState::GameState(std::string id, CardBoard *cardBoard, std::vector<Player *> players,
                     serializable_value<bool> *is_started, serializable_value<bool> *is_finished,
                     serializable_value<int> *round_number, serializable_value<int> *current_player_idx,
                     serializable_value<int> *starting_player_idx)
         : unique_serializable(id),
           _cardBoard(cardBoard),
           _players(players),
           _is_started(is_started),
           _is_finished(is_finished),
           _round_number(round_number),
           _current_player_idx(current_player_idx),
           _starting_player_idx(starting_player_idx)
 { }

 GameState::GameState(std::string id) : unique_serializable(id) {
     this->_players = std::vector<Player *>();
     this->_cardBoard = new CardBoard();
     this->_is_started = new serializable_value<bool> (false);
     this->_is_finished = new serializable_value<bool> (false);
     this->_round_number = new serializable_value<int> (0);
     this->_current_player_idx = new serializable_value<int> (0);
     this->_starting_player_idx = new serializable_value<int> (0);
}

GameState::~GameState() {
    if (_is_started != nullptr) {
        delete this->_cardBoard;
        delete this->_is_started;
        delete this->_is_finished;
        delete this->_round_number;
        delete this->_current_player_idx;
        delete this->_starting_player_idx;

        this->_cardBoard = nullptr;
        this->_is_started = nullptr;
        this->_is_finished = nullptr;
        this->_round_number = nullptr;
        this->_current_player_idx = nullptr;
        this->_starting_player_idx = nullptr;
    }

}

bool GameState::flipCard(int row, int col) {
    return this->_cardBoard->flipCard(row, col);
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
    return _round_number->get_value();
}

CardBoard *GameState::getCardBoard() {
    return this->_cardBoard;
}

Player *GameState::get_current_player() const {
    if (_players.size() == 0) {
        return nullptr;
    }
    return _players[_current_player_idx->get_value()];
}

#ifdef MEMORY_SERVER
// TODO: define related functions
#endif

// Serializable Interface
void GameState::write_into_json(rapidjson::Value &json,
                                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) const {
    unique_serializable::write_into_json(json, allocator);

    rapidjson::Value card_board_val(rapidjson::kObjectType);
    _cardBoard->write_into_json(card_board_val, allocator);
    json.AddMember("cardBoard", card_board_val, allocator);

    rapidjson::Value is_finished_val(rapidjson::kObjectType);
    _is_finished->write_into_json(is_finished_val, allocator);
    json.AddMember("is_finished", is_finished_val, allocator);

    rapidjson::Value is_started_val(rapidjson::kObjectType);
    _is_started->write_into_json(is_started_val, allocator);
    json.AddMember("is_started", is_started_val, allocator);

    rapidjson::Value current_player_idx_val(rapidjson::kObjectType);
    _current_player_idx->write_into_json(current_player_idx_val, allocator);
    json.AddMember("current_player_idx", current_player_idx_val, allocator);

    rapidjson::Value starting_player_idx_val(rapidjson::kObjectType);
    _starting_player_idx->write_into_json(starting_player_idx_val, allocator);
    json.AddMember("starting_player_idx", starting_player_idx_val, allocator);

    rapidjson::Value round_number_val(rapidjson::kObjectType);
    _round_number->write_into_json(round_number_val, allocator);
    json.AddMember("round_number", round_number_val, allocator);

    json.AddMember("players", vector_utils::serialize_vector(_players, allocator), allocator);
}

GameState *GameState::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id")
        && json.HasMember("cardBoard")
        && json.HasMember("is_finished")
        && json.HasMember("is_started")
        && json.HasMember("current_player_idx")
        && json.HasMember("round_number")
        && json.HasMember("starting_player_idx")
        && json.HasMember("players")
            )
    {
        std::vector<Player*> deserialized_players;
        for (auto &serialized_player : json["players"].GetArray()) {
            deserialized_players.push_back(Player::from_json(serialized_player.GetObject()));
        }
        return new GameState(json["id"].GetString(),
                              CardBoard::from_json(json["cardBoard"].GetObject()),
                              deserialized_players,
                              serializable_value<bool>::from_json(json["is_started"].GetObject()),
                              serializable_value<bool>::from_json(json["is_finished"].GetObject()),
                              serializable_value<int>::from_json(json["round_number"].GetObject()),
                              serializable_value<int>::from_json(json["current_player_idx"].GetObject()),
                              serializable_value<int>::from_json(json["starting_player_idx"].GetObject()));
    } else {
        throw MemoryException("Failed to deserialize game_state. Required entries were missing.");
    }
}