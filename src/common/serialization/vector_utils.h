//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_VECTOR_UTILS_H
#define MEMORY_GAME_VECTOR_UTILS_H


#include <vector>
#include "serializable.h"
#include "unique_serializable.h"
#include "../../rapidjson/include/rapidjson/document.h"


namespace vector_utils {

    template<class T, class B> struct derived_from {
        static void constraints(T* p) { B* pb = p; }
        derived_from() { void(*p)(T*) = constraints; }
    };

    template<class T>
    /* WARNING: can only be called with vectors containing elements of type T that derives from "serializable" */
    static rapidjson::Value serialize_vector(const std::vector<T*>& serializables, rapidjson::Document::AllocatorType& allocator) {
        derived_from<T,serializable>(); // ensure T derives from serializable
        rapidjson::Value arr_val(rapidjson::kArrayType);
        for (int i = 0; i < serializables.size(); i++) {
            rapidjson::Value elem(rapidjson::kObjectType);
            serializables[i]->write_into_json(elem, allocator);
            arr_val.PushBack(elem, allocator);
        }
        return arr_val;
    }

}

#endif //MEMORY_GAME_VECTOR_UTILS_H
