//
// Created by Jin on 5/11/22.
//

#include "Card.h"

#include "../../exceptions/MemoryException.h"

Card::Card(std::string id) : unique_serializable(id) { }

Card::Card(std::string id, serializable_value<int> *val, serializable_value<bool> *isFront)
        : unique_serializable(id), _value(val), _isFront(isFront)
{ }

Card::Card(int val, bool isFront) :
    unique_serializable(),
    _value(new serializable_value<int> (val)),
    _isFront(new serializable_value<bool> (isFront))
{ }

Card::~Card() { }


int Card::getValue() const noexcept {
    return _value->get_value();
}

bool Card::getIsFront() const noexcept {
    return _isFront->get_value();
}

void Card::flip() {
    _isFront->set_value(! _isFront->get_value());
}

Card *Card::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id") && json.HasMember("value") && json.HasMember("isFront")) {
        return new Card(json["id"].GetString(),
                        serializable_value<int>::from_json(json["value"].GetObject()),
                        serializable_value<bool>::from_json(json["isFront"].GetObject()));
    } else {
        throw MemoryException("Could not parse json of card. Was missing 'id' or 'val' or 'isFront'. ");
    }
}


void Card::write_into_json(rapidjson::Value &json, rapidjson::Document::AllocatorType& allocator) const  {
    unique_serializable::write_into_json(json, allocator);

    rapidjson::Value value_val(rapidjson::kObjectType);
    _value->write_into_json(value_val, allocator);
    json.AddMember("value", value_val, allocator);

    rapidjson::Value isFront_val(rapidjson::kObjectType);
    _isFront->write_into_json(isFront_val, allocator);
    json.AddMember("isFront", isFront_val, allocator);
}