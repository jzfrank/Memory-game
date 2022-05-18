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

    this->buildOtherPlayers(gameState, myPosition);

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
    // TODO: build cardboards' background
    std::string background_image = "assets/question-mark-background.png";
    wxPoint backgroundStartPosition = (MainGamePanel::tableCenter -
                                       wxPoint(MainGamePanel::backgroundSize.x / 2,
                                               MainGamePanel::backgroundSize.y / 2) +
                                       wxPoint(0, MainGamePanel::cardSize.y / 2));
    new ImagePanel(this, background_image, wxBITMAP_TYPE_ANY,
                                            backgroundStartPosition,
                                            MainGamePanel::backgroundSize);
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
                                              + wxPoint(col * MainGamePanel::cardSize.x, row * MainGamePanel::cardSize.y),
                                              MainGamePanel::cardSize);
            card->SetToolTip("card: click to flip");
            card->SetCursor(wxCursor(wxCURSOR_HAND));
            card->Bind(wxEVT_LEFT_UP, [row, col] (wxMouseEvent & event) {
                GameController::flipCard(row, col);
            });
        }
    }
    // otherwise, render a funny picture
    else {
          std::cout << " no cards left! " << std::endl;
    }

}

void MainGamePanel::buildThisPlayer(GameState *gameState, Player *me) {

    wxBoxSizer* outerLayout = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(outerLayout);
    wxBoxSizer* innerLayout = new wxBoxSizer(wxVERTICAL);
    outerLayout->Add(innerLayout, 1, wxALIGN_BOTTOM);

    wxStaticText* playerName = this->buildStaticText(
        me->get_player_name(),
        wxDefaultPosition,
        wxSize(200, 18),
        wxALIGN_CENTER,
        true
    );
    innerLayout->Add(playerName, 1, wxALIGN_CENTER);

    if (!gameState->is_started()) {
        // show button that allows out player to start the game
        wxButton * startGameButton = new wxButton(
                this, wxID_ANY, "Start Game!",
                wxDefaultPosition,
                wxSize(160, 64));
        startGameButton->Bind(wxEVT_BUTTON, [](wxCommandEvent & event) {
            GameController::startGame();
        });
        innerLayout->Add(startGameButton, 0, wxALIGN_CENTER | wxBOTTOM, 8);
    } else {
        // build score
        wxStaticText * scoreIndicator = this->buildStaticText(
                "score: " + std::to_string(me->get_score()),
                wxDefaultPosition,
                wxSize(200, 18),
                wxALIGN_CENTER
        );
        innerLayout->Add(scoreIndicator, 0, wxALIGN_CENTER | wxBOTTOM, 8);
    }
}

void MainGamePanel::buildOtherPlayers(GameState *gameState, int myPosition) {
    std::vector<Player *> players = gameState->get_players();
    int numberOfPlayers = gameState->get_players().size();
    double anglePerPlayer = MainGamePanel::twoPi / (double) numberOfPlayers;

    // show all other players
    for(int i = 1; i < numberOfPlayers; i++) {

        // get player at i-th position after myself
        Player* otherPlayer = players.at((myPosition + i) % numberOfPlayers);

        double playerAngle = (double) i * anglePerPlayer;
        int side = (2 * i) - numberOfPlayers; // side < 0 => right, side == 0 => center, side > 0 => left

        this->buildOtherPlayerLabel(gameState, otherPlayer, playerAngle, side);
    }
}

void MainGamePanel::buildOtherPlayerLabel(GameState *gameState, Player *otherPlayer, double playerAngle, int side) {

    long textAlignment = wxALIGN_CENTER;
    int labelOffsetX = 0;

    if(side < 0) { // right side
        textAlignment = wxALIGN_LEFT;
        labelOffsetX = 85;

    } else if(side > 0) { // left side
        textAlignment = wxALIGN_RIGHT;
        labelOffsetX = -85;
    }

    // define the ellipse which represents the virtual player circle
    double horizontalRadius = MainGamePanel::otherPlayerLabelDistanceFromCenter * 1.25; // 1.25 to horizontally elongate players' circle (but less than the hands' circle)
    double verticalRadius = MainGamePanel::otherPlayerLabelDistanceFromCenter;

    // get this player's position on that ellipse
    wxPoint labelPosition = MainGamePanel::tableCenter;
    labelPosition += this->getPointOnEllipse(horizontalRadius, verticalRadius, playerAngle);
    labelPosition += wxSize(labelOffsetX, 0);

    // if game has not yet started, we only have two lines
    if(!gameState->is_started()) {
        this->buildStaticText(
                otherPlayer->get_player_name(),
                labelPosition + wxSize(-100, -18),
                wxSize(200, 18),
                textAlignment,
                true
        );
        this->buildStaticText(
                "waiting...",
                labelPosition + wxSize(-100, 0),
                wxSize(200, 18),
                textAlignment
        );

    } else {
        this->buildStaticText(
                otherPlayer->get_player_name(),
                labelPosition + wxSize(-100, -27),
                wxSize(200, 18),
                textAlignment,
                true
        );
        this->buildStaticText(
                "score: " + std::to_string(otherPlayer->get_score()),
                labelPosition + wxSize(-100, -9),
                wxSize(200, 18),
                textAlignment
        );

        // Show other player's status label
        std::string statusText;
        if (!gameState->is_finished()) {
            if (gameState->get_current_player() == otherPlayer) {
                statusText = "their turn";
            } else {
                statusText = "waiting...";
            }
        } else {
            statusText = "";
        }

        bool bold = true;
        this->buildStaticText(
                statusText,
                labelPosition + wxSize(-100, 9),
                wxSize(200, 18),
                textAlignment,
                bold
        );
    }
}

void MainGamePanel::buildTurnIndicator(GameState *gameState, Player *me) {
    if (gameState->is_started()
        && gameState->get_current_player() != nullptr
        && !gameState->is_finished()) {
        // TODO: what if the name are repeated? Could be a bug to handle
        std::string turnIndicatorText;
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

wxPoint MainGamePanel::getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle) {
    return wxPoint((int) (sin(angle) * horizontalRadius), (int) (cos(angle) * verticalRadius));
}
