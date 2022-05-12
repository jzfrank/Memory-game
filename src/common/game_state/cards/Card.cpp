//
// Created by Jin on 5/11/22.
//

#include "Card.h"

Card::Card(std::string val) {
    this->value = val;
    // by initialization cards are showing back cover
    this->isFront = false;
}


std::string Card::getValue() const noexcept {
    return this->value;
}

void Card::flip() {
    this->isFront = ! this->isFront;
}

bool Card::getIsFront() {
    return this->isFront;
}


Card::~Card() { }