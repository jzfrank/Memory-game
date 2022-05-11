//
// Created by Jin on 5/11/22.
//

#include "card.h"

card::card(int val) {
    this->value = val;
    // by initialization cards are showing back cover
    this->is_front = false;
}


int card::get_value() const noexcept {
    return this->value;
}

bool card::get_is_front() {
    return this->is_front;
}

card::~card() { }