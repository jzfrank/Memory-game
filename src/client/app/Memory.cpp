//
// Created by Jin on 5/9/22.
//

#include "Memory.h"

// Application entry point
bool Memory::OnInit()
{
    // Allow loading of JPEG  and PNG image files
    wxImage::AddHandler(new wxJPEGHandler());
    wxImage::AddHandler(new wxPNGHandler());

    // Open main game window
    GameWindow* gameWindow = new GameWindow(
            "Memory", // title of window,
            wxDefaultPosition, // position of the window
            wxDefaultSize // size of the window
    );
    gameWindow->Show(true);

    // Initialize GameController
    GameController::init(gameWindow);

    return true;
}