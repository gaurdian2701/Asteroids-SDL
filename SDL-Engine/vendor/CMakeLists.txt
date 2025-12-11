add_library(vendor INTERFACE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL_ttf-main)

target_include_directories(
        vendor
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/glm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(SDLTTF_VENDORED ON)

target_link_libraries(
        vendor
            INTERFACE
                SDL3::SDL3-static
                SDL3_ttf::SDL3_ttf)