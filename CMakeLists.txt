cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME SDLGame)
project(${PROJECT_NAME})

add_subdirectory(SDL-Engine)

add_executable(
        ${PROJECT_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/AsteroidsApp.cpp
        include/GameObjects/SpaceShip.h
        src/GameObjects/SpaceShip.cpp
        include/FolderPaths.h)

target_include_directories(
        ${PROJECT_NAME}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
        ${PROJECT_NAME}
            PRIVATE
                SDLEngineLib)
