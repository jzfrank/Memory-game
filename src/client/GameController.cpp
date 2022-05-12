//
// Created by Jin on 5/10/22.
//

#include "GameController.h"

// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;
//
//player* GameController::_me = nullptr;
GameState* GameController::_currentGameState = nullptr;

void GameController::init(GameWindow *gameWindow)
{
    GameController::_gameWindow = gameWindow;

    // set up panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);

    // hide all panels
    GameController::_connectionPanel->Show(false);
    GameController::_mainGamePanel->Show(false);

    // Only show connection panel at the start of the game
    GameController::_gameWindow->showPanel(GameController::_connectionPanel);

    // Set status bar
    GameController::_gameWindow->setStatus("Not Connected");
}

void GameController::connectToServer() {
    GameController::_currentGameState = new GameState();
    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);
    GameController::_mainGamePanel->buildGameState(_currentGameState);
}

void GameController::updateGameState(GameState *newGameState) {

    GameState * oldGameState = GameController::_currentGameState;

    GameController::_currentGameState = newGameState;

//    if (oldGameState != nullptr) {
//        delete oldGameState;
//    }

    // TODO: if game is finished, show game finished message

    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);

    GameController::_mainGamePanel->buildGameState(_currentGameState);

}

void GameController::flipCard(int row, int col) {
//    std::cout << "before flipping card.isFront=" <<
//        GameController::_currentGameState->getCardBoard()->getCards()[row][col]->getIsFront() << std::endl;
    GameController::_currentGameState->flipCard(row, col);

//    std::cout << "MainGamePanel::flipCard is called" << std::endl;
//    std::cout << "flipped card.isFront=" <<
//        GameController::_currentGameState->getCardBoard()->getCards()[row][col]->getIsFront() << std::endl;

    GameController::updateGameState(GameController::_currentGameState);
}