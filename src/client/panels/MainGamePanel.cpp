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
//    int numberOfPlayers = players.size();

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
    } else {
        me = players[myPosition];
    }


    this->buildCardMatrix(gameState);

    // indicator whose turn to play
    this->buildTurnIndicator(gameState, me);

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
    // if the cards number is more than 0, render the cardboard
    if (cards.size() > 0) {
        for (int i=0; i < cards.size(); i++) {
            std::string cardImage;
            if (cards[i] == nullptr) {
                cardImage = "assets/memory-logo.png";
            } else if (! cards[i]->getIsFront()) {
                cardImage = "assets/card-back.png";
            } else {
                cardImage = "assets/" + val_to_filename[cards[i]->getValue()];
            }
            std::cout << "cardImage" << cardImage << std::endl;
            std::tuple<int,int> pos = cards[i]->getPosition();
            int row = std::get<0>(pos), col = std::get<1>(pos);
            ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
                                              cardStartPosition
                                              + wxPoint(col * cardSize.x, row * cardSize.y),
                                              cardSize);
            card->SetToolTip("card: click to flip");
            card->SetCursor(wxCursor(wxCURSOR_HAND));
            card->Bind(wxEVT_LEFT_UP, [row, col] (wxMouseEvent & event) {
                GameController::flipCard(row, col);
            });
        }
    }
    // otherwise, render a funny picture
    else {
        std::string funny_image = "assets/card-back.png";
        new ImagePanel(this, funny_image, wxBITMAP_TYPE_ANY,
                       (MainGamePanel::tableCenter -
                       wxPoint(MainGamePanel::backGroundSize.x / 2,
                                        MainGamePanel::backGroundSize.y / 2)),
                       MainGamePanel::backGroundSize);
    }

}

void MainGamePanel::buildThisPlayer(GameState *gameState, Player *me) {

    wxPoint thisPlayerPosition = MainGamePanel::tableCenter + MainGamePanel::thisPlayerPositionOffset;
//    wxStaticText* playerName =
    this->buildStaticText(
        me->get_player_name(),
        thisPlayerPosition,
        wxSize(200, 18),
        wxALIGN_CENTER,
        true
    );

    if (!gameState->is_started()) {
        // show button that allows out player to start the game
        wxButton * startGameButton = new wxButton(
                this, wxID_ANY, "Start Game!",
                thisPlayerPosition + wxPoint(50, 0),
                wxSize(160, 64));
        startGameButton->Bind(wxEVT_BUTTON, [](wxCommandEvent & event) {
            GameController::startGame();
        });

    } else {
        // TODO: to be implemented
        // build score
        this->buildStaticText(
                "score: " + std::to_string(me->get_score()),
                thisPlayerPosition + wxPoint(0, 30),
                wxSize(200, 18),
                wxALIGN_CENTER,
                true
        );
        std::cout << "build this player part 2: not yet implemented" << std::endl;
    }
}

void MainGamePanel::buildTurnIndicator(GameState *gameState, Player *me) {
    if (gameState->is_started() && gameState->get_current_player() != nullptr) {
        // TODO: what if the name are repeated? Could be a bug to handle
        std::string turnIndicatorText;
//        std::cout << "current_player: " << gameState->get_current_player()->get_player_name() << " "
//                << gameState->get_current_player()->get_score() << " "
//                << gameState->get_current_player()->get_id() << std::endl;
//        std::cout << "me: " << me->get_player_name() << " "
//                << me->get_score() << " "
//                << me->get_id() << std::endl;
//        std::cout << "are they equal? " << (gameState->get_current_player() == me) << std::endl;
        if (gameState->get_current_player() == me) {
            turnIndicatorText = "It's your turn!";
        } else{
            turnIndicatorText = "...Waiting " + gameState->get_current_player()->get_player_name() + " to turn cards...";
        }


        wxPoint turnIndicatorPosition = MainGamePanel::tableCenter + MainGamePanel::turnIndicatorOffset;
        this->buildStaticText(
                turnIndicatorText,
                turnIndicatorPosition,
                wxSize(200, 20),
                wxALIGN_CENTER,
                true
                );
    }
}

wxStaticText * MainGamePanel::buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold) {
    wxStaticText * staticText = new wxStaticText(this, wxID_ANY, content, position, size, textAlignment);
    // if bold, modify the style
    if (bold) {
        wxFont font = staticText->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        staticText->SetFont(font);
    }
    return staticText;
}