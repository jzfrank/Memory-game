//
// Created by Jin on 5/10/22.
//

#include "GameController.h"
#include "../common/network/requests/join_game_request.h"
#include "../common/network/requests/start_game_request.h"
#include "../common/network/requests/flip_card_request.h"
#include "network/ClientNetworkManager.h"

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
    // get values form UI input fields
    wxString inputServerAddress = GameController::_connectionPanel->getServerAddress().Trim();
    wxString inputServerPort = GameController::_connectionPanel->getServerPort().Trim();
    wxString inputPlayerName = GameController::_connectionPanel->getPlayerName().Trim();

    // check that all values were provided
    if(inputServerAddress.IsEmpty()) {
        GameController::showError("Input error", "Please provide the server's address");
        return;
    }
    if(inputServerPort.IsEmpty()) {
        GameController::showError("Input error", "Please provide the server's port number");
        return;
    }
    if(inputPlayerName.IsEmpty()) {
        GameController::showError("Input error", "Please enter your desired player name");
        return;
    }

    // convert host from wxString to std::string
    std::string host = inputServerAddress.ToStdString();

    // convert port from wxString to uint16_t
    unsigned long portAsLong;
    if(!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
        GameController::showError("Connection error", "Invalid port");
        return;
    }
    uint16_t port = (uint16_t) portAsLong;

    // convert player name from wxString to std::string
    std::string playerName = inputPlayerName.ToStdString();

    // connect to network
    ClientNetworkManager::init(host, port);

    // send request to join game
    GameController::_me = new Player(playerName, 0);
    join_game_request request = join_game_request(GameController::_me->get_id(), GameController::_me->get_player_name());
    ClientNetworkManager::sendRequest(request);
}

void GameController::updateGameState(GameState *newGameState) {

    GameState * oldGameState = GameController::_currentGameState;

    GameController::_currentGameState = newGameState;

    if (oldGameState != nullptr) {

        // check if a new round started
        if (oldGameState->get_round_number() > 0 && oldGameState->get_round_number() < newGameState->get_round_number()) {
//           TODO: GameController::showNewRoundMessage(oldGameState, newGameState);
            1;
        }
        // delete the old game state
        delete oldGameState;
    }

    // if game is finished, show game finished message
    if (GameController::_currentGameState->is_finished()) {
//        TODO: GameController::showGameOverMessage();
    }

    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);

    GameController::_mainGamePanel->buildGameState(GameController::_currentGameState, GameController::_me);
}

void GameController::startGame() {
    start_game_request request = start_game_request(GameController::_currentGameState->get_id(),
                                                    GameController::_me->get_id());
    ClientNetworkManager::sendRequest(request);
}

void GameController::flipCard(int row, int col) {
    flip_card_request request = flip_card_request(GameController::_currentGameState->get_id(),
                                                  GameController::_me->get_id(),
                                                  std::vector<int>{row, col});
    ClientNetworkManager::sendRequest(request);

//    GameController::_currentGameState->flipCard(row, col);
//    GameController::updateGameState(GameController::_currentGameState);
//    CardBoard * cardBoard = GameController::_currentGameState->getCardBoard();
//    if (cardBoard->getNofTurnedCards() == 2) {
//        // either the same card then vanish
//        // or different card but let next player to play
//        cardBoard->handleTurnedCards();
//        std::cout << "next player" << std::endl;
//
//        // Show message that current turn is finished
//        // TODO: add timeout
//        std::string message = "Your turn is finished";
//        std::string title = "Message";
//        wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
//        dialogBox.ShowModal();
//    }
//    GameController::updateGameState(GameController::_currentGameState);
}

wxEvtHandler *GameController::getMainThreadEventHandler() {
    return GameController::_gameWindow->GetEventHandler();
}

void GameController::showError(const std::string &title, const std::string &message) {
    wxMessageBox(message, title, wxICON_ERROR);
}

void showMessage(const std::string & title, const std::string & message) {
    wxMessageBox(message, title, wxOK);
}

void GameController::showStatus(const std::string &message) {
    GameController::_gameWindow->setStatus(message);
}