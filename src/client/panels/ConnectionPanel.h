//
// Created by Jin on 5/9/22.
//

#ifndef MEMORY_GAME_CONNECTIONPANEL_H
#define MEMORY_GAME_CONNECTIONPANEL_H


#include <wx/wx.h>
#include "../uiElements/InputField.h"
#include "../uiElements/ImagePanel.h"

class ConnectionPanel : public wxPanel {

public:
    ConnectionPanel(wxWindow* parent);

//    wxString getServerAddress();
//    wxString getServerPort();
//    wxString getPlayerName();

private:
    InputField* _serverAddressField;
    InputField* _serverPortField;
    InputField* _playerNameField;

};


#endif //MEMORY_GAME_CONNECTIONPANEL_H
