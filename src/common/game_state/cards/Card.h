//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARD_H
#define MEMORY_GAME_CARD_H

#include <string>

class Card {
private:
    std::string value;
    bool isFront;
public:
    Card(std::string val);
    ~Card();

    void flip();

    // accessors
    std::string getValue() const noexcept;
    bool getIsFront();

};
#endif //MEMORY_GAME_CARD_H
