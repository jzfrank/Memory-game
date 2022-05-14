//
// Created by Jin on 5/9/22.
//

#include "GameWindow.h"

GameWindow::GameWindow(const wxString & title, const wxPoint & pos, const wxSize & size)
: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    // Set up layout that will contain and center all content

    this->_mainLayout = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* outerLayout = new wxBoxSizer(wxHORIZONTAL);
    outerLayout->Add(this->_mainLayout, 1, wxCENTER);
    this->SetSizerAndFit(outerLayout);
    this->_currentPanel = nullptr;

    // Set up status bar
    this->_statusBar = this->CreateStatusBar(1);

    // Set background
    wxColor lightPurple = wxColor(151, 114, 251);
    this->SetBackgroundColour(lightPurple);

    // set the minimum size of the window
    this->SetMinSize(wxSize(1000, 720));
}

void GameWindow::showPanel(wxPanel *panel)
{
    // if we are showing the panel, nothing is needed
    if (this->_currentPanel == panel) {
        return;
    }

    // remove previous panel
    if (this->_currentPanel != nullptr) {
        this->_mainLayout->Detach(this->_currentPanel);
        this->_currentPanel->Show(false);
        this->_currentPanel = nullptr;
    }

    // add new panel
    int border_spacing = 10;
    this->_mainLayout->Add(panel, 0, wxALIGN_CENTER | wxALL, border_spacing);
    panel->Show(true);
    this->_currentPanel = panel;

    // update layout
    this->_mainLayout->Layout();

    // update window size
    this->Fit();
}

void GameWindow::setStatus(const std::string &message)
{
    this->_statusBar->SetStatusText(message, 0);
}