cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME Asteroids_App)
project(${PROJECT_NAME})

add_subdirectory(SDL-Engine)

add_executable(
        ${PROJECT_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Asteroids_App.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/SpaceShip.cpp)

target_include_directories(
        ${PROJECT_NAME}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
        ${PROJECT_NAME}
            PRIVATE
                SDLEngineLib)
