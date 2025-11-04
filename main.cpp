//
// Created by marta on 28/10/2025.
//
#include <iostream>
#include <array>

#include "Sudoku_Generator.h"
#include "Sudoku_Solver.h"
using namespace std;


enum Difficulty {
    EASY = 40,
    MEDIUM = 50,
    DIFFICULT = 60
  };
int main() {
    Sudoku_Solver solver;

    Sudoku_Generator sudoku_generator;
    array<array<__int8 , 9> , 9> sudoku = sudoku_generator.create_sudoku(DIFFICULT);
    solver.printSudoku(sudoku);


    solver.solveSudoku(sudoku);


    solver.printSudoku(sudoku);
    return 0;
}


