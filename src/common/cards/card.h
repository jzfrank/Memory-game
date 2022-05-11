//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARD_H
#define MEMORY_GAME_CARD_H

#include <string>

class card {
private:
    int value;
    bool is_front;
public:
    card(int val);
    ~card();

    // accessors
    int get_value() const noexcept;
    bool get_is_front();

};
#endif //MEMORY_GAME_CARD_H
