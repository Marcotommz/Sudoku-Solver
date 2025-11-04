cmake_minimum_required(VERSION 3.22)
project(SudokuServer)

# Standard C++ 17
set(CMAKE_CXX_STANDARD 17)

# Aggiungi tutti i file del progetto
add_executable(SudokuServer
        main.cpp
        Sudoku_Solver.h
        Sudoku_Generator.h
        httplib.h
)

# Necessario per socket Windows (httplib)
target_link_libraries(SudokuServer ws2_32 wsock32)