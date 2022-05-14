//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_MAINGAMEPANEL_H
#define MEMORY_GAME_MAINGAMEPANEL_H

#include <wx/wx.h>
#include "../uiElements/ImagePanel.h"
#include "../../common/game_state/GameState.h"


// TODO: set a card value to assets name dictionary

class MainGamePanel : public wxPanel {
public:
    MainGamePanel(wxWindow* parent);
    void buildGameState(GameState * gameState);

private:

    void buildCardMatrix(GameState * gameState);


    wxSize const panelSize = wxSize(960, 680);
    wxPoint const tableCenter = wxPoint(480, 300);
    wxSize const cardSize = wxSize(80, 124);

};

#endif //MEMORY_GAME_MAINGAMEPANEL_H
