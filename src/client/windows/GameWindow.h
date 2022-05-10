//
// Created by Jin on 5/9/22.
//


#ifndef MEMORY_GAME_GAMEWINDOW_H
#define MEMORY_GAME_GAMEWINDOW_H
#include <wx/wx.h>
#include "../panels/ConnectionPanel.h"


class GameWindow : public wxFrame
{
public:
    GameWindow(const wxString & title, const wxPoint & pos, const wxSize & size);

    void showPanel(wxPanel* panel);
    void setStatus(const std::string& message);

private:
    wxBoxSizer* _mainLayout;
    wxStatusBar* _statusBar;

    wxPanel* _currentPanel;
};

#endif //MEMORY_GAME_GAMEWINDOW_H
