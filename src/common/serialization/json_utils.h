//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_JSON_UTILS_H
#define MEMORY_GAME_JSON_UTILS_H


#include <string>

#include "../../rapidjson/include/rapidjson/writer.h"
#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/stringbuffer.h"


class json_utils {
public:
    static std::string to_string(const rapidjson::Value* json) {
        rapidjson::StringBuffer buffer;
        buffer.Clear();
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json->Accept(writer);
        return buffer.GetString();
    }

    // In case you need to create a rapidjson::Document on the heap (pointer) based on a value extracted from a json.
    static rapidjson::Document* clone_value(const rapidjson::Value& val) {
        rapidjson::Document* state_json = new rapidjson::Document(rapidjson::kObjectType);
        state_json->CopyFrom(val, state_json->GetAllocator());
        return state_json;
    }

};

#endif //MEMORY_GAME_JSON_UTILS_H
