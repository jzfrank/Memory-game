//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_START_GAME_REQUEST_H
#define MEMORY_GAME_START_GAME_REQUEST_H


#include <string>
#include "client_request.h"
#include "../../../../rapidjson/include/rapidjson/document.h"

class start_game_request : public client_request{

private:

    /*
     * Private constructor for deserialization
     */
    explicit start_game_request(base_class_properties);

public:
    start_game_request(std::string game_id, std::string player_id);
    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static start_game_request* from_json(const rapidjson::Value& json);
};

#endif //MEMORY_GAME_START_GAME_REQUEST_H
