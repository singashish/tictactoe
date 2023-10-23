@echo off

rem Step 1: Create a build directory if it doesn't exist
if not exist build mkdir build

rem Step 2: Change to the build directory
cd build

rem Step 3: Run CMake to configure the project for MinGW
cmake -G "MinGW Makefiles" ..

rem Step 4: Build the project using mingw32-make
mingw32-make

rem Step 5: Run the executable
TicTacToe.exe

rem Pause to keep the console window open so you can see the output
pause
