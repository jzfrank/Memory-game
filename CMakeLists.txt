cmake_minimum_required(VERSION 3.22)
project(memory_game)


set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR </usr/include/wx-3.0>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(memory_game
        src/client/main.cpp src/client/app/Memory.cpp src/client/app/Memory.h src/client/windows/GameWindow.cpp src/client/windows/GameWindow.h src/client/panels/ConnectionPanel.cpp src/client/panels/ConnectionPanel.h src/client/GameController.cpp src/client/GameController.h src/client/uiElements/InputField.cpp src/client/uiElements/InputField.h)


target_link_libraries(memory_game ${wxWidgets_LIBRARIES})
