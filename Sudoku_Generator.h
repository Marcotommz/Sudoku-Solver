//
// Created by marta on 31/10/2025.
//

#ifndef SUDOKU_SOLVER_SUDOKU_GENERATOR_H
#define SUDOKU_SOLVER_SUDOKU_GENERATOR_H

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include "Sudoku_Solver.h"
using namespace std;
class Sudoku_Generator {
    public:

    Sudoku_Solver solver;

     // generatore Mersenne Twister



    array<array<__int8 , 9 >, 9 > base_sudoku;



    array<array<__int8 , 9 >, 9 > create_sudoku(){
        for (int i = 0; i < 9; i++) {
            base_sudoku[i].fill(0);
        }


        random_device rd; // genera un seed casuale
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1,9);


        int r = dist(gen);
        int c = dist(gen);
        __int8 n = dist(gen);



        base_sudoku[r][c] = n;

        populate_sudoku(base_sudoku, 0,0);


        solver.printSudoku(base_sudoku);

        return base_sudoku;
    }



    bool populate_sudoku(array<array<__int8, 9>, 9> &sudoku, int i, int j) {
        if (i == 9) return true; // griglia completata

        int next_i = i;
        int next_j = j + 1;
        if (next_j == 9) {
            next_j = 0;
            next_i++;
        }

        if (sudoku[i][j] != 0) {
            return populate_sudoku(sudoku, next_i, next_j);
        }

        // genera numeri da 1 a 9 mescolati
        vector<__int8> nums = {1,2,3,4,5,6,7,8,9};
        random_device rd;
        mt19937 gen(rd());
        shuffle(nums.begin(), nums.end(), gen);

        for (__int8 n : nums) {
            if (solver.isValid(sudoku, i, j, n)) {
                sudoku[i][j] = n;

                if (populate_sudoku(sudoku, next_i, next_j))
                    return true;

                sudoku[i][j] = 0; // backtrack
            }
        }

        return false; // nessun numero valido
    }
};


#endif //SUDOKU_SOLVER_SUDOKU_GENERATOR_H