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
    void buildTurnIndicator(GameState * gameState, Player * me);

    wxStaticText* buildStaticText(std::string content, wxPoint position, wxSize size,
                                  long textAlignment, bool bold=false);

    std::unordered_map<int, std::string> val_to_filename = {
            {1, "card-K.png"},
            {2, "card-Q.png"}
    };

    wxPoint const turnIndicatorOffset = wxPoint(-400, -200);
    wxPoint const thisPlayerPositionOffset = wxPoint(-100, 300);
    wxPoint const tableCenter = wxPoint(480, 300);

    wxSize const panelSize = wxSize(960, 680);
    wxSize const cardSize = wxSize(80, 124);
    wxSize const backGroundSize = wxSize(160, 250);



};

#endif //MEMORY_GAME_MAINGAMEPANEL_H
