//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_FLIP_CARD_REQUEST_H
#define MEMORY_GAME_FLIP_CARD_REQUEST_H

#include <string>
#include "client_request.h"
#include "../../../../rapidjson/include/rapidjson/document.h"

class flip_card_request : public client_request {
private:
    std::vector<int> _position;
    // _position indicates the user tries to turn (row=_position[0], col=_position[1]) card


    // for deserialization
    flip_card_request(base_class_properties, std::vector<int> position);

public:
    std::vector<int> get_position() const {return this->_position;};

    // constructor
    flip_card_request(std::string game_id, std::string player_id, std::vector<int> position);

    virtual void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType& allocator) const override;
    static flip_card_request* from_json(const rapidjson::Value& json);
};

#endif //MEMORY_GAME_FLIP_CARD_REQUEST_H
