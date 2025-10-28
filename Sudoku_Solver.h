//
// Created by marta on 28/10/2025.
//

#ifndef SUDOKU_SOLVER_SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_SUDOKU_SOLVER_H
#include <iostream>
#include <array>
namespace std {
    class Sudoku_Solver {

        public:
        /**
         * Stampa il Sudoku su terminale
         * @param sudoku
         */
        static void printSudoku(array<array<__int8, 9>, 9> &sudoku ) {
            for (int i = 0; i < 9; i++) {
                cout << '|';
                for (int j = 0; j < 9; j++) {
                    cout << (int)sudoku[i][j] ;
                    if ((j+1) % 3 == 0 and j!= 0) {
                        cout << '|';
                    }else {
                        cout << "  ";
                    }
                }
                cout << '\n';
                if ((i+1) % 3 == 0 and i!= 0)
                cout << "+-------+-------+-------+"<<endl;
            }
        }


        static bool test_all_sudoku(array<array<__int8, 9>, 9> &sudoku) {
            array<bool,9> map;

            // Controllo righe
            for (int i = 0;i<9;i++) {
                map.fill(false);
                for (int j = 0;j<9;j++) {
                    if (sudoku[i][j] != 0) {
                        if ( map[sudoku[i][j]-1]) {
                            cout << "Errore riga: " << i << ", colonna: " << j << endl;
                            return false;
                        }
                        map[sudoku[i][j]-1] = true;
                    }
                }
            }

            // Controllo colonne
            for (int i = 0;i<9;i++) {
                map.fill(false);
                for (int j = 0;j<9;j++) {
                    if (sudoku[j][i] != 0) {
                        if (map[sudoku[j][i]-1]) {
                            cout << "Errore colonna: " << i << ", riga: " << j << endl;
                            return false;
                        }
                        map[sudoku[j][i]-1] = true;
                    }
                }
            }

            // Controllo blocchi 3x3
            for (int bi = 0;bi<9;bi+=3) {
                for (int bj = 0;bj<9;bj+=3) {
                    map.fill(false);
                    for (int i = 0;i<3;i++) {
                        for (int j = 0;j<3;j++) {
                            if (sudoku[i+bi][j+bj] != 0 ) {
                                if (map[sudoku[i+bi][j+bj]-1]) {
                                    cout << "Errore blocco: " << bi << "," << bj << endl;
                                    return false;
                                }
                                map[sudoku[i+bi][j+bj]-1] = true;
                            }
                        }
                    }
                }
            }

            return true;

        }

        static bool isValid(const array<array<__int8, 9>, 9> &sudoku, __int8 row, __int8 col, __int8 num) {
            for (int i = 0; i < 9; i++) {
                if (sudoku[row][i] == num || sudoku[i][col] == num) return false;
            }
            int startRow = (row / 3) * 3;
            int startCol = (col / 3) * 3;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (sudoku[startRow + i][startCol + j] == num) return false;
            return true;
        }


        static bool solveSudoku(array<array<__int8, 9>, 9> &sudoku) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (sudoku[i][j] == 0) {
                        for (int n = 1; n <= 9; n++) {
                            if (isValid(sudoku, i, j, n)) {
                                sudoku[i][j] = n;
                                if (solveSudoku(sudoku)) return true;
                                sudoku[i][j] = 0; // backtrack
                            }
                        }
                        return false; // nessun numero valido
                    }
                }
            }
            return true; // completato
        }
    };
} // std

#endif //SUDOKU_SOLVER_SUDOKU_SOLVER_H