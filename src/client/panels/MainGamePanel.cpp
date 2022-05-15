//
// Created by Jin on 5/10/22.
//

#include "MainGamePanel.h"
#include <vector>
#include "../GameController.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {

}

void MainGamePanel::buildGameState(GameState *gameState, Player * me) {

    // remove any existing UI
    this->DestroyChildren();

    std::vector<Player *> players = gameState->get_players();
    int numberOfPlayers = players.size();

    // find our own player object
    int myPosition = -1;
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->get_id() == me->get_id()) {
            myPosition = i;
            break;
        }
    }
    if (myPosition == -1) {
        GameController::showError("Game State error", "could not find this player among players of server game");
        return;
    }


    this->buildCardMatrix(gameState);

    // show our own player (or start game button in the beginning)
    this->buildThisPlayer(gameState, me);

    this->Layout();
}

void MainGamePanel::buildCardMatrix(GameState* gameState) {

    CardBoard * cardBoard = gameState->getCardBoard();
    std::vector<Card*> cards = cardBoard->getCards();

    wxPoint cardStartPosition = MainGamePanel::tableCenter
                                + wxPoint(-cardSize.x * 2, -cardSize.y * 1);

    std::cout << "number of cards: " << cards.size() << std::endl;
    for (int i=0; i < cards.size(); i++) {
        std::string cardImage;
        if (cards[i] == nullptr) {
            cardImage = "assets/memory-logo.png";
        } else if (! cards[i]->getIsFront()) {
            cardImage = "assets/card-back.png";
        } else {
            cardImage = "assets/" + val_to_filename[cards[i]->getValue()];
        }
        int row = i / 4, col = i % 4;
        ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
                                          cardStartPosition
                                          + wxPoint(col * cardSize.x, row * cardSize.y),
                                          cardSize);
        card->SetToolTip("card: click to flip");
        card->SetCursor(wxCursor(wxCURSOR_HAND));
        card->Bind(wxEVT_LEFT_UP, [row, col, this] (wxMouseEvent & event) {
            GameController::flipCard(row, col);
        });
    }

//    for (int row=0; row < cards.size(); row++){
////        wxBoxSizer* horizontalLayout = new wxBoxSizer(wxHORIZONTAL);
//
//        std::string cardImage;
//        for (int col=0; col < cards[row].size(); col++) {
//            if (cards[row][col] == nullptr) {
//                cardImage = "assets/memory-logo.png";
//            }
//            else if (! cards[row][col]->getIsFront()) {
//                cardImage = "assets/card-back.png";
//            }
//            else {
//                cardImage = "assets/" + val_to_filename[cards[row][col]->getValue()];
//            }
////            std::cout << cardImage << std::endl;
//            ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
//                                              cardStartPosition + wxPoint(col * cardSize.x, row * cardSize.y),
//                                              cardSize);
//            card->SetToolTip("card: click to flip");
//            card->SetCursor(wxCursor(wxCURSOR_HAND));
//            card->Bind(wxEVT_LEFT_UP, [row, col, this] (wxMouseEvent & event) {
//                GameController::flipCard(row, col);
//            });
////            horizontalLayout->Add(card, 0, wxALIGN_CENTER | wxALL, 20);
//        }
////        verticalLayout->Add(horizontalLayout);
//    }

}

void MainGamePanel::buildThisPlayer(GameState *gameState, Player *me) {
    if (!gameState->is_started()) {
        // show button that allows out player to start the game
        wxButton * startGameButton = new wxButton(this, wxID_ANY, "Start Game!", wxDefaultPosition, wxSize(160, 64));
        startGameButton->Bind(wxEVT_BUTTON, [](wxCommandEvent & event) {
            GameController::startGame();
        });

    } else {
        // TODO: to be implemented
        std::cout << "build this player part 2: not yet implemented" << std::endl;
    }
}