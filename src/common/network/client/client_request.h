//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_CLIENT_REQUEST_H
#define MEMORY_GAME_CLIENT_REQUEST_H

#include <string>
#include <unordered_map>
#include "../../../../rapidjson/include/rapidjson/document.h"
#include "../../serialization/serializable.h"
#include "../../exceptions/MemoryException.h"
#include "../../serialization/uuid_generator.h"
#include "../../serialization/json_utils.h"

#endif //MEMORY_GAME_CLIENT_REQUEST_H

// Identifier for the different request types.
// The RequestType is sent with every client_request to identify the type of client_request
// during deserialization on the server side.
enum RequestType {
    join_game,
    start_game,
    flip_card
};

class client_request : public serializable {
protected:

    struct base_class_properties {
        RequestType _type;
        std::string _req_id;
        std::string _player_id;
        std::string _game_id;
    };

    RequestType _type;
    std::string _req_id;
    std::string _player_id;
    std::string _game_id;

    explicit client_request(base_class_properties); // base constructor
    static base_class_properties create_base_class_properties(RequestType type, std::string req_id,
                                                              std::string & player_id, std::string & game_id);
    static base_class_properties extract_base_class_properties(const rapidjson::Value& json);

private:
    // for deserialization
    static const std::unordered_map<std::string, RequestType> _string_to_request_type;
    // for serialization
    static const std::unordered_map<RequestType, std::string> _request_type_to_string;

public:
    virtual ~client_request() {}

    [[nodiscard]] RequestType get_type() const {return this->_type; };
    [[nodiscard]] std::string get_req_id() const {return this->_req_id; };
    [[nodiscard]] std::string get_player_id() const {return this->_player_id; };
    [[nodiscard]] std::string get_game_id() const {return this-> _game_id; };

    // Tries to create the specific client_request from the provided json
    // Throw exception if parsing fails -> use only in "try{}catch{}" block
    static client_request* from_json(const rapidjson::Value & json);

    // Serializes the client request into a json object that can be sent over the network
    void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType& allocator) const override;

    [[nodiscard]] virtual std::string to_string() const;

};