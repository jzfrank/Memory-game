//
// Created by Jin on 5/10/22.
//

#include "GameController.h"

// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;

Player* GameController::_me = nullptr;
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
    GameController::_gameWindow->setStatus("Connected");
    GameController::_mainGamePanel->buildGameState(_currentGameState);
}

void GameController::updateGameState(GameState *newGameState) {

    GameState * oldGameState = GameController::_currentGameState;

    GameController::_currentGameState = newGameState;


    // TODO: if game is finished, show game finished message

    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);

    GameController::_mainGamePanel->buildGameState(_currentGameState);

}

void GameController::flipCard(int row, int col) {
    GameController::_currentGameState->flipCard(row, col);
    GameController::updateGameState(GameController::_currentGameState);
    CardBoard * cardBoard = GameController::_currentGameState->getCardBoard();
    if (cardBoard->getNofTurnedCards() == 2) {
        // either the same card then vanish
        // or different card but let next player to play
        cardBoard->handleTurnedCards();
        std::cout << "next player" << std::endl;

        // Show message that current turn is finished
        // TODO: add timeout
        std::string message = "Your turn is finished";
        std::string title = "Message";
        wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
        dialogBox.ShowModal();
    }
    GameController::updateGameState(GameController::_currentGameState);
}