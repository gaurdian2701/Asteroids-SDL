cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME SDLEngine)

project(${PROJECT_NAME})

set(ENGINE_BINARY_NAME SDLEngineLib)
set(VENDOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)

add_subdirectory(vendor)

add_library(
        ${ENGINE_BINARY_NAME}
            STATIC
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Application/Application.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/GameScene.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/ECS/ECSManager.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/ECS/Systems/RenderingSystem.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/CoreSystems/TextureResourceManager.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/CoreSystems/InputSystem.cpp
        include/Core/AssetPathHolder.h
        include/Core/Misc.h)

target_include_directories(
        ${ENGINE_BINARY_NAME}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
        ${ENGINE_BINARY_NAME}
            PUBLIC
                vendor)

set_target_properties(
        ${ENGINE_BINARY_NAME}
            PROPERTIES
                LINKER_LANGUAGE CXX)
