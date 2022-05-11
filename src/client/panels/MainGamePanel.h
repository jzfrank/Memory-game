//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_MAINGAMEPANEL_H
#define MEMORY_GAME_MAINGAMEPANEL_H

#include <wx/wx.h>
#include "../uiElements/ImagePanel.h"

class MainGamePanel : public wxPanel {
public:
    MainGamePanel(wxWindow* parent);

private:
    void buildCardMatrix();
};

#endif //MEMORY_GAME_MAINGAMEPANEL_H
