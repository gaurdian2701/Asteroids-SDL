add_subdirectory(SDL)

add_library(vendor INTERFACE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)

target_include_directories(
        vendor
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/glm)

target_link_libraries(
        vendor
            INTERFACE
                SDL3::SDL3)