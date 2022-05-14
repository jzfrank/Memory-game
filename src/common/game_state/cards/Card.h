//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARD_H
#define MEMORY_GAME_CARD_H

#include <string>
#include "../../serialization/unique_serializable.h"
#include "../../serialization/serializable_value.h"
#include "../../../../rapidjson/include/rapidjson/document.h"

class Card : public unique_serializable {
private:
    serializable_value<int> * _value;
    serializable_value<bool> * _isFront;
    serializable_value<int> * _row;
    serializable_value<int> * _col;


    // deserialization constructor
    Card(std::string id, serializable_value<int>* val,
         serializable_value<bool> * isFront,
         serializable_value<int> * _row,
         serializable_value<int> * _col);

    // from_diff constructor
    Card(std::string id);

public:
    Card(int val, bool isFront, int row, int col);
    ~Card();

    void flip();

    // accessors
    [[nodiscard]] int getValue() const noexcept;
    [[nodiscard]] bool getIsFront()  const noexcept;
    [[nodiscard]] std::tuple<int, int> getPosition() const noexcept;

    // serializable interface
    void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType & allocator) const override;
    static Card* from_json(const rapidjson::Value & json);
};
#endif //MEMORY_GAME_CARD_H
