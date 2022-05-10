//
// Created by Jin on 5/9/22.
//

#include "ConnectionPanel.h"

ConnectionPanel::ConnectionPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY)
{
    wxColor white = wxColor(255, 255, 255);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    wxString default_server_host = "5035";
    this->_serverAddressField = new InputField(
            this,
            "Server Address",
            100,
            default_server_host,
            240);
    verticalLayout->Add(this->_serverAddressField, 0,wxALIGN_CENTER, 10);



    this->SetSizerAndFit(verticalLayout);
}