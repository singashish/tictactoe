cmake_minimum_required(VERSION 3.12)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

# Add the include directory for header files
include_directories(include)

# Define your source files
set(SOURCE_FILES
    src/main.cpp
    src/game.cpp
    src/board.cpp
)

# Add an executable target
add_executable(TicTacToe ${SOURCE_FILES})
