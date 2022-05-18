//
// Created by Jin on 5/18/22.
//

#include "shuffle_request.h"

#ifdef MEMORY_SERVER
#include "../../../server/game_instance_manager.h"
#include "../../../server/game_instance.h"
#endif

shuffle_request::shuffle_request(std::string game_id, std::string player_id) :
        client_request(client_request::create_base_class_properties(RequestType::shuffle, uuid_generator::generate_uuid_v4(), player_id, game_id))
{}

shuffle_request::shuffle_request(client_request::base_class_properties props) :
        client_request(props)
{}

shuffle_request *shuffle_request::from_json(const rapidjson::Value &json) {
    return new shuffle_request(client_request::extract_base_class_properties(json));
}

void shuffle_request::write_into_json(rapidjson::Value &json,
                                      rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator) const {
    client_request::write_into_json(json, allocator);
}