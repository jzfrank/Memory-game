//
// Created by Jin on 5/10/22.
//

#include "MainGamePanel.h"
#include <vector>
#include "../GameController.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
//    wxColor white = wxColor(255, 255, 255);
//    this->SetBackgroundColour(white);
}

void MainGamePanel::buildGameState(GameState *gameState) {

    // remove any existing UI
    this->DestroyChildren();

    this->buildCardMatrix(gameState);
    this->Layout();
}

void MainGamePanel::buildCardMatrix(GameState* gameState) {

    CardBoard * cardBoard = gameState->getCardBoard();
    std::vector<std::vector<Card*>> cards = cardBoard->getCards();

//    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);
    wxPoint cardStartPosition = MainGamePanel::tableCenter
                                + wxPoint(-cardSize.x * cards[0].size() / 2, -cardSize.y * cards.size() / 2);

    for (int row=0; row < cards.size(); row++){
//        wxBoxSizer* horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

        std::string cardImage;


        for (int col=0; col < cards[row].size(); col++) {
            if (cards[row][col] == nullptr) {
                cardImage = "assets/memory-logo.png";
            }
            else if (! cards[row][col]->getIsFront()) {
                cardImage = "assets/card-back.png";
            }
            else {
                cardImage = "assets/card-" + cards[row][col]->getValue() + ".png";
            }
//            std::cout << cardImage << std::endl;
            ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
                                              cardStartPosition + wxPoint(col * cardSize.x, row * cardSize.y),
                                              cardSize);
            card->SetToolTip("card: click to flip");
            card->SetCursor(wxCursor(wxCURSOR_HAND));
            card->Bind(wxEVT_LEFT_UP, [row, col, this] (wxMouseEvent & event) {
//                std::cout << row << col << std::endl;
                GameController::flipCard(row, col);
            });
//            horizontalLayout->Add(card, 0, wxALIGN_CENTER | wxALL, 20);
        }
//        verticalLayout->Add(horizontalLayout);
    }

}

