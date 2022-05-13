//
// Created by Jin on 5/13/22.
//

#include "unique_serializable.h"

#include "uuid_generator.h"
#include "../exceptions/MemoryException.h"


unique_serializable::unique_serializable()
        : _id(uuid_generator::generate_uuid_v4())
{ }

unique_serializable::unique_serializable(std::string id)
        : _id(id)
{ }

std::string unique_serializable::get_id() const {
    return this->_id;
}

void unique_serializable::write_into_json(rapidjson::Value &json,
                                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    rapidjson::Value id_val(_id.c_str(), allocator);
    json.AddMember("id", id_val, allocator);

}


#include "unique_serializable.h"
