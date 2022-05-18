//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_MAINGAMEPANEL_H
#define MEMORY_GAME_MAINGAMEPANEL_H

#include <wx/wx.h>
#include <unordered_map>
#include "../uiElements/ImagePanel.h"
#include "../../common/game_state/GameState.h"


// TODO: set a card value to assets name dictionary

class MainGamePanel : public wxPanel {
public:
    MainGamePanel(wxWindow* parent);
    void buildGameState(GameState * gameState, Player * me);

private:
    void buildCardMatrix(GameState * gameState);
    void buildThisPlayer(GameState * gameState, Player * me);
    void buildOtherPlayers(GameState * gameState, int myPosition);
    void buildOtherPlayerLabel(GameState* gameState, Player * otherPlayer, double playerAngle, int side);
    void buildTurnIndicator(GameState * gameState, Player * me);

    wxStaticText* buildStaticText(std::string content, wxPoint position, wxSize size,
                                  long textAlignment, bool bold=false);
    wxPoint getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle);

    std::unordered_map<int, std::string> val_to_filename = {
            {1, "card-K.png"},
            {2, "card-Q.png"}
    };

    wxPoint const turnIndicatorOffset = wxPoint(-400, -200);
    wxPoint const thisPlayerPositionOffset = wxPoint(-100, 300);
    wxPoint const tableCenter = wxPoint(480, 300);

//    wxSize const panelSize = wxSize(960, 680);
    wxSize const cardSize = wxSize(80, 124);
//    wxSize const cardSize = wxSize(60, 90);
    wxSize const backgroundSize = wxSize(600, 450);

    double twoPi = 6.28;
    double const otherPlayerHandSize = 160.0;
    double const otherPlayerHandDistanceFromCenter = 180.0;
    double const otherPlayerLabelDistanceFromCenter = 275.0;



};

#endif //MEMORY_GAME_MAINGAMEPANEL_H
