//
// Created by Jin on 5/13/22.
//

#include <sstream>
#include "flip_card_request.h"

// public constructor
flip_card_request::flip_card_request(std::string game_id, std::string player_id, std::vector<int> position)
            : client_request(client_request::create_base_class_properties(RequestType::flip_card,uuid_generator::generate_uuid_v4(),player_id,game_id)),
            _position(position)
{ }

// private constructor for deserialization
flip_card_request::flip_card_request(client_request::base_class_properties props, std::vector<int> position) :
    client_request(props),
    _position(position)
{}

flip_card_request* flip_card_request::from_json(const rapidjson::Value &json) {
    base_class_properties props = client_request::extract_base_class_properties(json);
    if (json.HasMember("position")) {
        // assume position_string is like "row col"
        // e.g. "1 2" or "2 0"
        std::string position_string = json["position"].GetString();
        std::stringstream iss( position_string );
        int num;
        std::vector<int> position;
        while (iss >> num) {
            position.push_back(num);
        }

        return new flip_card_request(props, position);
    }
    else {
        throw MemoryException("Could not find 'row' and 'col' in flip_card_request");
    }
}

void flip_card_request::write_into_json(rapidjson::Value &json,
                                        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    client_request::write_into_json(json, allocator);
    std::stringstream oss;
    copy(_position.begin(), _position.end(), std::ostream_iterator<int>(oss, " "));
    std::string position_string = oss.str();
    rapidjson::Value position_val(position_string.c_str(), allocator);
    json.AddMember("position", position_val, allocator);
}


