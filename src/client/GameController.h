//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_GAMECONTROLLER_H
#define MEMORY_GAME_GAMECONTROLLER_H

#include "windows/GameWindow.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"
#include "network/ResponseListenerThread.h"
#include "../common/game_state/GameState.h"
#include "../common/game_state/player/Player.h"

class GameController
{
public:
    static void init(GameWindow* gameWindow);

    static void connectToServer();
    static void updateGameState(GameState* newGameState);
    static void startGame();
    static void flipCard(int row, int col);

    static void showGameOverMessage();

    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string & title, const std::string & message);
    static void showMessage(const std::string & title, const std::string & message);
    static void showStatus(const std::string & message);

//    static void showNewRoundMessage(GameState* oldGameState, GameState* newGameState);
//    static void showGameOverMessage();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;

    static Player* _me;
    static GameState* _currentGameState;
};

#endif //MEMORY_GAME_GAMECONTROLLER_H
