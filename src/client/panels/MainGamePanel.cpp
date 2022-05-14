//
// Created by Jin on 5/10/22.
//

#include "MainGamePanel.h"
#include <vector>
#include "../GameController.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {

}

void MainGamePanel::buildGameState(GameState *gameState) {

    // remove any existing UI
    this->DestroyChildren();

    this->buildCardMatrix(gameState);
    this->Layout();
}

void MainGamePanel::buildCardMatrix(GameState* gameState) {

    CardBoard * cardBoard = gameState->getCardBoard();
    std::vector<Card*> cards = cardBoard->getCards();

//    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);
    wxPoint cardStartPosition = MainGamePanel::tableCenter
                                + wxPoint(-cardSize.x * 2, -cardSize.y * 1);

    int row = 3, col = 4;
    for (int i=0; i < cards.size(); i++) {
        std::string cardImage;
        if (cards[i] == nullptr) {
            cardImage = "assets/images/memory-logo.png";
        } else if (! cards[i]->getIsFront()) {
            cardImage = "assets/card-back.png";
        } else {
            cardImage = "assets/" + val_to_filename[cards[i]->getValue()];
        }

        ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
                                          cardStartPosition + wxPoint(col * cardSize.x, row * cardSize.y),
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

