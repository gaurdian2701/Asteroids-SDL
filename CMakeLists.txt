cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 23)
set(EXE_NAME Asteroids_App)
project(${EXE_NAME})

add_subdirectory(SDL-Engine)

add_executable(
        ${EXE_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Asteroids_App.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/SpaceShip.cpp)

EnableASANCompileOptions(${EXE_NAME})

target_include_directories(
        ${EXE_NAME}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
        ${EXE_NAME}
            PRIVATE
                SDLEngineLib)




