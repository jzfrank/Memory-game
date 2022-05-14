//
// Created by Jin on 5/14/22.
//

#include "full_state_response.h"

#include "../../exceptions/MemoryException.h"
#include "../../serialization/json_utils.h"

#ifdef MEMORY_CLIENT
#include "../../../client/GameController.h"
#endif

full_state_response::full_state_response(base_class_properties props, rapidjson::Value *state_json)
   : server_response(props),
    _state_json(state_json)
{}

full_state_response::full_state_response(std::string game_id, const GameState &game_state) :
        server_response(server_response::create_base_class_properties(ResponseType::full_state_msg, game_id))
{
    this->_state_json = game_state.to_json();
}

void full_state_response::write_into_json(rapidjson::Value &json,
                                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    server_response::write_into_json(json, allocator);
    json.AddMember("state_json", *_state_json, allocator);
}

full_state_response *full_state_response::from_json(const rapidjson::Value &json) {
    if (json.HasMember("state_json")) {
        return new full_state_response(server_response::extract_base_class_properties(json),
                                       json_utils::clone_value(json["state_json"].GetObject()));
    } else {
        throw MemoryException("Could not parse full_state_response from json. state is missing");
    }
}

full_state_response::~full_state_response() {
    if (_state_json != nullptr) {
        delete _state_json;
        _state_json = nullptr;
    }
}

rapidjson::Value *full_state_response::get_state_json() const {
    return _state_json;
}

#ifdef MEMORY_CLIENT
void full_state_reponse::Process() const {
    try {
        GameState* state = GameState::from_json(*_state_json);
        GameController::updateGameState(state);
    } catch {std::exception & e} {
        std::cerr << "Failed to extract GameState from full_state_response" << std::endl
                  << e.what() << std::endl;
    }
}

#endif