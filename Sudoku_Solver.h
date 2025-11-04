#ifndef SUDOKU_SOLVER_SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_SUDOKU_SOLVER_H
#include <iostream>
#include <array>

namespace std {

    /**
     * Classe che implementa un risolutore di Sudoku tramite backtracking.
     * Contiene metodi per verificare la validità della griglia, risolverla e contare quante soluzioni esistono.
     */
    class Sudoku_Solver {

    public:

        /**
         * Stampa la matrice del Sudoku in formato leggibile
         * @param sudoku matrice 9x9 contenente valori da 0 a 9
         *        (0 rappresenta una cella vuota)
         */
        static void printSudoku(array<array<__int8, 9>, 9> &sudoku ) {
            for (int i = 0; i < 9; i++) {
                cout << '|';
                for (int j = 0; j < 9; j++) {
                    cout << (int)sudoku[i][j] ;
                    if ((j+1) % 3 == 0 and j!= 0) {
                        cout << '|';
                    } else {
                        cout << "  ";
                    }
                }
                cout << '\n';
                if ((i+1) % 3 == 0 and i!= 0)
                    cout << "+-------+-------+-------+"<<endl;
            }
        }

        /**
         * Controlla se la griglia del Sudoku è valida
         * Ritorna false se rileva duplicati in una riga, colonna o sottoblocco 3x3
         */
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

        /**
         * Controlla se un numero può essere inserito in una data cella
         * rispettando le regole del Sudoku
         */
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

        /**
         * Risolve il Sudoku usando backtracking
         * @return true se viene trovata una soluzione
         */
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
                        return false; // nessun numero valido trovato
                    }
                }
            }
            return true; // puzzle completato
        }

        /**
         * Conta il numero di soluzioni della griglia
         * @param grid griglia del Sudoku (modificata e ripristinata durante l'esecuzione)
         * @param limit limite oltre cui interrompere il conteggio (default 2)
         * @return numero di soluzioni trovate (minimo tra soluzioni reali e limit)
         *
         * Il limite evita tempo di calcolo inutile: se si trovano già 2 soluzioni,
         * non serve continuare per verificarne altre.
         */
        int countSolutions(array<array<__int8,9>,9> &grid, int limit = 2) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (grid[i][j] == 0) {

                        for (int num = 1; num <= 9; num++) {
                            if (isValid(grid, i, j, num)) {

                                grid[i][j] = num;
                                int result = countSolutions(grid, limit);
                                grid[i][j] = 0; // ripristina la cella dopo test

                                if (result >= limit)
                                    return result; // interrompe se raggiunto il limite
                            }
                        }

                        return 0; // nessuna soluzione possibile da qui
                    }
                }
            }
            return 1; // soluzione completa trovata
        }
    };

} // namespace std

#endif //SUDOKU_SOLVER_SUDOKU_SOLVER_H
