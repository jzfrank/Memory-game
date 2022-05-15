//
// Created by Jin on 5/9/22.
//

#include "ConnectionPanel.h"
#include "../uiElements//ImagePanel.h"
#include "../../common/network/default.conf"
#include "../GameController.h"

ConnectionPanel::ConnectionPanel(wxWindow *parent)
: wxPanel(parent, wxID_ANY)
{
    wxColor white = wxColor(255, 255, 255);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    ImagePanel* logo = new ImagePanel(
            this,
            "assets/memory-logo.png",
            wxBITMAP_TYPE_ANY,
            wxDefaultPosition,
            wxSize(200, 250)
            );
    verticalLayout->Add(logo, 0,
                        wxALIGN_CENTER | wxALL, 20);

    int labelWidth = 120, fieldWidth = 240;
    this->_serverAddressField = new InputField(
            this,
            "Server Address:",
            labelWidth,
            default_server_host, // default value (from "default.conf")
            fieldWidth);
    verticalLayout->Add(this->_serverAddressField, 0,wxALIGN_CENTER | wxALL, 10);

    this->_serverPortField = new InputField(
            this,
            "Server Port:",
            labelWidth,
            wxString::Format("%i", default_port), // default value (from "default.conf")
            fieldWidth
            );
    verticalLayout->Add(this->_serverPortField, 0, wxALIGN_CENTER | wxALL, 10);

    this->_playerNameField = new InputField(
            this,
            "Player name:",
            labelWidth,
            "",
            fieldWidth
            );
    verticalLayout->Add(this->_playerNameField, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton* connectButton = new wxButton(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(100, 50));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        GameController::connectToServer();
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 15);


    this->SetSizerAndFit(verticalLayout);
}

wxString ConnectionPanel::getServerAddress() {
    return this->_serverAddressField->getValue();
}

wxString ConnectionPanel::getServerPort() {
    return this->_serverPortField->getValue();
}

wxString ConnectionPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}
