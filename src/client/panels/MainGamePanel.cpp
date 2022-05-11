//
// Created by Jin on 5/10/22.
//

#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
    wxColor white = wxColor(255, 255, 255);
    this->SetBackgroundColour(white);
    this->buildCardMatrix();
}

void MainGamePanel::buildCardMatrix() {


    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    for (int row=0; row < 3; row++){
        wxBoxSizer* horizontalLayout = new wxBoxSizer(wxHORIZONTAL);
        int card_width = 100, card_height = 120;
        wxSize cardSize = wxSize(card_width, card_height);
        std::string cardKImage = "assets/card-K.png";
        std::string cardImage = "assets/card-back.png";

        for (int col=0; col < 4; col++) {
            ImagePanel* card = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY,
                                              wxDefaultPosition,
                                              cardSize);
            card->SetToolTip("card: click to flip");
            card->SetCursor(wxCursor(wxCURSOR_HAND));
            card->Bind(wxEVT_LEFT_UP, [cardKImage, row, col] (wxMouseEvent & event) {
                std::cout << row << ", " << col << std::endl;
            });
            horizontalLayout->Add(card, 0, wxALIGN_CENTER | wxALL, 20);
        }
        verticalLayout->Add(horizontalLayout);
    }


    this->SetSizerAndFit(verticalLayout);
}