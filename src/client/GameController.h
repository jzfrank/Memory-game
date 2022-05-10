//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_GAMECONTROLLER_H
#define MEMORY_GAME_GAMECONTROLLER_H

#include "windows/GameWindow.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"
//#include "network/ResponseListenerThread.h"
//#include "../common/game_state/game_state.h"

class GameController
{
public:
    static void init(GameWindow* gameWindow);

    static void connectToServer();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;
};

#endif //MEMORY_GAME_GAMECONTROLLER_H
