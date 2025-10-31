//
// Created by marta on 28/10/2025.
//
#include <iostream>
#include <array>

#include "Sudoku_Generator.h"
#include "Sudoku_Solver.h"
using namespace std;


int main() {
    array<array<__int8, 9>, 9> puzzle = {{
        {{5,3,0,0,7,0,0,0,0}},
        {{6,0,0,1,9,5,0,0,0}},
        {{0,9,8,0,0,0,0,6,0}},
        {{8,0,0,0,6,0,0,0,3}},
        {{4,0,0,8,0,3,0,0,1}},
        {{7,0,0,0,2,0,0,0,6}},
        {{0,6,0,0,0,0,2,8,0}},
        {{0,0,0,4,1,9,0,0,5}},
        {{0,0,0,0,8,0,0,7,9}}
    }};
    /*Sudoku_Solver solver;
    solver.solveSudoku(puzzle);
    solver.printSudoku(puzzle);
    */


    Sudoku_Generator sudoku_generator;
    sudoku_generator.create_sudoku();
}


