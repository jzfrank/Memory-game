cmake_minimum_required(VERSION 3.22)
project(memory_game)


set(CMAKE_CXX_STANDARD 20)

set(wxWidgets_ROOT_DIR </usr/include/wx-3.0>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(memory_game
        src/client/main.cpp src/client/app/Memory.cpp
        src/client/app/Memory.h
        src/client/windows/GameWindow.cpp
        src/client/windows/GameWindow.h
        src/client/panels/ConnectionPanel.cpp
        src/client/panels/ConnectionPanel.h
        src/client/GameController.cpp
        src/client/GameController.h
        src/client/uiElements/InputField.cpp
        src/client/uiElements/InputField.h
        src/client/uiElements/ImagePanel.cpp
        src/client/uiElements/ImagePanel.h
        src/client/panels/MainGamePanel.cpp
        src/client/panels/MainGamePanel.h
        src/common/game_state/GameState.cpp
        src/common/game_state/GameState.h
        src/common/game_state/cards/Card.cpp
        src/common/game_state/cards/Card.h
        src/common/game_state/cards/CardBoard.cpp
        src/common/game_state/cards/CardBoard.h src/common/game_state/player/Player.cpp src/common/game_state/player/Player.h src/common/exceptions/MemoryException.h src/common/serialization/json_utils.h src/common/serialization/serializable.h src/common/serialization/serializable_value.h src/common/serialization/unique_serializable.cpp src/common/serialization/unique_serializable.h src/common/serialization/uuid_generator.h src/common/serialization/value_type_helpers.h src/common/serialization/vector_utils.h src/common/network/client/client_request.cpp src/common/network/client/client_request.h src/common/network/client/join_game_request.cpp src/common/network/client/join_game_request.h src/common/network/client/start_game_request.cpp src/common/network/client/start_game_request.h)

# copy assets (images) to binary directory
file(INSTALL assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(memory_game ${wxWidgets_LIBRARIES})
