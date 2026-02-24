cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(EXE_NAME Asteroids_App)
project(${EXE_NAME})

add_subdirectory(SDL-Engine)

add_executable(
        ${EXE_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Asteroids_App.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/SpaceShip.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/SpaceShipParticleEmitter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameScenes/MainGameScene.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Actions/ActionStack.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameActionStack.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameActions/PlayerControlAction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameActions/SpaceshipMoveAction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/Asteroid.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/UnitManager.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/PlayerProjectile.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameActions/EnemyControlAction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/EnemySpaceship.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/ProjectileBase.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameObjects/EnemyProjectile.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/GameActions/PlayerRespawnAction.cpp
)

set_target_properties(
        ${EXE_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${EXE_NAME}>")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXE_NAME})

EnableASANCompileOptions(${EXE_NAME})

target_include_directories(
        ${EXE_NAME}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
        ${EXE_NAME}
            PRIVATE
                SDLEngineLib)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E make_directory "$<TARGET_FILE_DIR:${EXE_NAME}>/Assets"
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets"
            "$<TARGET_FILE_DIR:${EXE_NAME}>/Assets"
)




