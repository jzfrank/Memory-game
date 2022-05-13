//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_UNIQUE_SERIALIZABLE_H
#define MEMORY_GAME_UNIQUE_SERIALIZABLE_H


#include "serializable.h"

class unique_serializable : public serializable {
protected:

    std::string _id;       // unique identifier

    unique_serializable();
    unique_serializable(std::string id);

public:
// accessors
    std::string get_id() const;

// serializable interface
    virtual void write_into_json(rapidjson::Value& json,
                                 rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const override;

};


#endif //MEMORY_GAME_UNIQUE_SERIALIZABLE_H
