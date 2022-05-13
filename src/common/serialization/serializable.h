//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_SERIALIZABLE_H
#define MEMORY_GAME_SERIALIZABLE_H


#include "../../rapidjson/include/rapidjson/document.h"

class serializable {
public:

    virtual rapidjson::Document* to_json() const {
        rapidjson::Document* json = new rapidjson::Document();
        json->SetObject();
        this->write_into_json(*json, json->GetAllocator());
        return json;
    }

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const = 0;
};

#endif //MEMORY_GAME_SERIALIZABLE_H
