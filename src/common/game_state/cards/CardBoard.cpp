//
// Created by Jin on 5/11/22.
//

#include "CardBoard.h"
#include <algorithm>
#include <random>
#include <vector>

#include "../../serialization/vector_utils.h"
#include "../../exceptions/MemoryException.h"

// deserialization constructor
CardBoard::CardBoard(std::string id, std::vector<Card*> & cards)
    : unique_serializable(id),
      _cards(cards)
{ }

// from_diff constructor
CardBoard::CardBoard(std::string id) : unique_serializable(id)
        {}

CardBoard::CardBoard()
                     : unique_serializable()
                     {}

CardBoard::~CardBoard() {
    for (int i=0; i < this->_cards.size(); i++) {
        delete this->_cards[i];
    }
    this->_cards.clear();
}

std::vector<Card *> CardBoard::getCards() {
    return this->_cards;
}

bool CardBoard::isVanishable(int r1, int c1, int r2, int c2) {
    if (r1 == r2 && c1 == c2) return false;

    Card * card1 = nullptr, * card2 = nullptr;
    for (int i=0; i < _cards.size(); i++) {
        if (_cards[i] != nullptr
        && _cards[i]->getPosition() == std::tuple<int, int>{r1, c1}) {
            card1 = _cards[i];
        }
        else if (_cards[i] != nullptr
                 && _cards[i]->getPosition() == std::tuple<int, int>{r2, c2}) {
            card2 = _cards[i];
        }
    }
    if (card1 == nullptr || card2 == nullptr) return false;
    else return (card1->getValue() == card2->getValue());
}

void CardBoard::vanishPairs(int r1, int c1, int r2, int c2) {
    if (! this->isVanishable(r1, c1, r2, c2)) {
        return;
    }
    else {
        Card * old_card = nullptr;
        for (int i=0; i<_cards.size(); i++) {
            if (_cards[i] != nullptr
                && _cards[i]->getPosition() == std::tuple<int, int>{r1, c1}) {
                old_card = _cards[i];
                _cards[i] = nullptr;
                delete old_card;
            }
            else if (_cards[i] != nullptr
                     && _cards[i]->getPosition() == std::tuple<int, int>{r2, c2}) {
                old_card = _cards[i];
                _cards[i] = nullptr;
                delete old_card;
            }
        }
    }
}

bool CardBoard::flipCard(int row, int col) {
    Card * card = nullptr;
    for (int i=0; i < _cards.size(); i++) {
        if (_cards[i] != nullptr
        && _cards[i]->getPosition() == std::tuple<int, int>{row, col}
        && !_cards[i]->getIsFront()) {
            card = _cards[i];
            card->flip();
            return true;
        }
    }
    // if row col is not found
    return false;
}

void CardBoard::handleTurnedCards() {
    std::vector<std::tuple<int, int>> turned_cards_position;
    for (int i=0; i < _cards.size(); i++) {
        if (_cards[i] != nullptr
        && !_cards[i]->getIsFront()) {
            turned_cards_position.push_back(_cards[i]->getPosition());
        }
    }
    if (turned_cards_position.size() == 2) {
        this->vanishPairs(
                std::get<0>(turned_cards_position[0]), std::get<1>(turned_cards_position[0]),
                std::get<0>(turned_cards_position[1]), std::get<1>(turned_cards_position[1])
                );
    }
}

// accessors

int CardBoard::getAvailableCards() {
    int cnt = 0;
    for (int i = 0; i < _cards.size(); i++) {
        if (_cards[i] != nullptr) cnt ++;
    }
    return cnt;
}

bool CardBoard::processEndGame() {
    return this->getAvailableCards() == 0;
}

int CardBoard::getNofTurnedCards() {
    int cnt = 0;
    for (int i = 0; i < _cards.size(); i++) {
        if (_cards[i] != nullptr
        && !_cards[i]->getIsFront()) cnt ++;
    }
    return cnt;
}

#ifdef MEMORY_SERVER
void CardBoard::setup_game(std::string &err) {
    // remove all cards (if any) and add the change to the "cards" array_diff
    for (int i = 0; i < _cards.size(); i++) {
        delete _cards[i];
    }
    _cards.clear();

    // add a fresh set of cards
    int row_num = 3, col_num = 4;
    for (int i=0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            _cards.push_back(new Card( i*j % 2 ? 0 : 1, false, i, j));
        }
    }

//    // shuffle them
// TODO: shuffle
//    this->shuffle();
}
#endif

void CardBoard::write_into_json(rapidjson::Value &json, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);
    json.AddMember("cards", vector_utils::serialize_vector(_cards, allocator), allocator);
}

CardBoard *CardBoard::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id") && json.HasMember("cards")) {
        std::vector<Card*> deserialized_cards = std::vector<Card*>();
        for (auto & serialized_card : json["cards"].GetArray()) {
            deserialized_cards.push_back(Card::from_json(serialized_card.GetObject()));
        }
        return new CardBoard(json["id"].GetString(), deserialized_cards);
    } else {
        throw MemoryException("Could not parse CardBoard from json. 'id' or 'cards' were missing.");
    }
}

