cmake_minimum_required(VERSION 3.11)

project(AlanGarciaGame)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(game src/main.cpp src/Player.cpp src/Level.cpp src/Enemy.cpp)

target_link_libraries(game raylib)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game>/assets)
