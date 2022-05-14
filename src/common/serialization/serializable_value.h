//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_SERIALIZABLE_VALUE_H
#define MEMORY_GAME_SERIALIZABLE_VALUE_H


#include <vector>
#include <iostream>
#include <functional>
#include <string>

#include "unique_serializable.h"
#include "value_type_helpers.h"
#include "../../../rapidjson/include/rapidjson/document.h"

template <class T>
class serializable_value : public serializable {

private:
    T _value;


public:

    serializable_value(T val) : serializable(), _value(val) { }

    T get_value() const { return this->_value; }

    void set_value(T val) {
        if (this->_value != val) {
            this->_value = val;
        }
    }

// serializable interface
    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override {
        json.AddMember("value", value_type_helpers::get_json_value<decltype(_value)>(_value, allocator), allocator);
    }

    static serializable_value<T>* from_json(const rapidjson::Value& json) {
        if (json.HasMember("value")) {
            T val = json["value"].Get<T>();
            return new serializable_value<T>(val);
        }
        return nullptr;
    }
};


#endif //MEMORY_GAME_SERIALIZABLE_VALUE_H
