//
// Created by Jin on 5/10/22.
//

#include "GameController.h"

// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
//MainGamePanel* GameController::_mainGamePanel = nullptr;
//
//player* GameController::_me = nullptr;
//game_state* GameController::_currentGameState = nullptr;

void GameController::init(GameWindow *gameWindow)
{
    GameController::_gameWindow = gameWindow;

    // set up panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);

    // hide all panels
    GameController::_connectionPanel->Show(false);

    // Only show connection panel at the start of the game
    GameController::_gameWindow->showPanel(GameController::_connectionPanel);

    // Set status bar
    GameController::_gameWindow->setStatus("Not Connected");
}