//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_MEMORYEXCEPTION_H
#define MEMORY_GAME_MEMORYEXCEPTION_H

#include <string>

class MemoryException : public std::exception {
private:
    std::string _msg;
public:
    explicit MemoryException(const std::string& message) : _msg(message) { };

    const char* what() const noexcept override {
        return _msg.c_str();
    }
};

#endif //MEMORY_GAME_MEMORYEXCEPTION_H
