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
    outerLayout->Add(this->_mainLayout, 0.1, wxCENTER);
    this->SetSizerAndFit(outerLayout);
    this->_currentPanel = nullptr;

    // Set up status bar
    this->_statusBar = this->CreateStatusBar(1);

    // Set background
    wxColor lightPurple = wxColor(151, 114, 251);
    this->SetBackgroundColour(lightPurple);

    // set the mimimum size of the window
    this->SetMinSize(wxSize(1000, 720));
}

void GameWindow::setStatus(const std::string &message)
{
    this->_statusBar->SetStatusText(message);
}