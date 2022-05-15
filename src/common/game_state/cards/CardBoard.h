//
// Created by Jin on 5/11/22.
//

#ifndef MEMORY_GAME_CARDBOARD_H
#define MEMORY_GAME_CARDBOARD_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Card.h"
#include "../player/Player.h"
#include "../../serialization/serializable.h"
#include "../../serialization/serializable_value.h"
#include "../../../../rapidjson/include/rapidjson/document.h"

class CardBoard : public unique_serializable {
private:
    std::vector<Card*> _cards;

    // deserialization constructor
    CardBoard(std::string id, std::vector<Card*> & cards);

    // from_diff constructor
    CardBoard(std::string id);

public:
    CardBoard();
    ~CardBoard();

    bool flipCard(int row, int col);
    bool isVanishable(int r1, int c1, int r2, int c2); // check if two cards are vanishable
    void vanishPairs(int r1, int c1, int r2, int c2); // vanish a pair of cards if possible
    bool processEndGame(); // check if the number of cards remaining is 0
    void handleTurnedCards(); // called when the number of turned cards reaches 2
    // TODO: Shuffle()

    //accessors
    int getAvailableCards(); // returns the number of available cards on the cardboard
    std::vector<Card*> getCards();
    int getNofTurnedCards();

#ifdef MEMORY_SERVER
    // state update functions
    void setup_game(std::string & err); // clears the stack
#endif

    // serializable interface
    virtual void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType & allocator) const override;
    static CardBoard* from_json(const rapidjson::Value& json);
};
#endif //MEMORY_GAME_CARDBOARD_H
