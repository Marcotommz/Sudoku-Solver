#ifndef SUDOKU_SOLVER_SUDOKU_GENERATOR_H
#define SUDOKU_SOLVER_SUDOKU_GENERATOR_H

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include "Sudoku_Solver.h"
using namespace std;

/**
 * Classe che genera un Sudoku completo e poi rimuove celle
 * per creare un puzzle giocabile con difficoltà variabile.
 * Utilizza backtracking tramite Sudoku_Solver.
 */
class Sudoku_Generator {
    private:

    Sudoku_Solver solver;  // istanza del solver per validazioni e backtracking

    array<array<__int8 , 9 >, 9 > base_sudoku;   // matrice finale del sudoku
    array<array<int , 2> , 81> cells;            // lista di coordinate (r,c) mescolate

    /**
     * Genera un sudoku completo tramite backtracking ricorsivo
     * @param sudoku matrice da riempire
     * @param i riga corrente
     * @param j colonna corrente
     * @return true se completato
     */
    bool populate_sudoku(array<array<__int8, 9>, 9> &sudoku, int i, int j) {
        if (i == 9) return true; // tutta la griglia è riempita

        int next_i = i;
        int next_j = j + 1;
        if (next_j == 9) {
            next_j = 0;
            next_i++;
        }

        // Se la cella è già compilata salta alla prossima
        if (sudoku[i][j] != 0) {
            return populate_sudoku(sudoku, next_i, next_j);
        }

        // Prova numeri 1-9 in ordine casuale
        vector<__int8> nums = {1,2,3,4,5,6,7,8,9};
        random_device rd;
        mt19937 gen(rd());
        shuffle(nums.begin(), nums.end(), gen);

        for (__int8 n : nums) {
            if (solver.isValid(sudoku, i, j, n)) {
                sudoku[i][j] = n;

                if (populate_sudoku(sudoku, next_i, next_j))
                    return true;

                sudoku[i][j] = 0; // backtracking
            }
        }

        return false; // nessun numero valido trovato
    }

    /**
     * Rimuove celle dal sudoku cercando di mantenere una griglia valida
     * @param sudoku matrice sudoku
     * @param count quante celle rimuovere
     * @param index indice attuale nel vettore cells mescolato
     */
    bool add_spaces(array<array<__int8, 9>, 9> &sudoku , int count , int index ) {
        if (count == 0 or index == 81) {
            return true;
        }

        int tmp = sudoku[cells[index][0]][cells[index][1]];
        sudoku[cells[index][0]][cells[index][1]] = 0;

        // Metodo provvisorio: controlla solo validità formale
        if (solver.test_all_sudoku(sudoku)) {

            return add_spaces(sudoku, --count, ++index);
        }
        else {
            sudoku[cells[count][0]][cells[count][1]] = tmp;
            return add_spaces(sudoku , count , ++index);
        }
    }

    /**
     * Prepara la lista di tutte le posizioni (0..80) e la mescola
     * Serve per decidere in ordine casuale quali celle svuotare
     */
    void inizializeCells() {
        random_device rd;
        mt19937 gen(rd());

        int tmp_r = 0;
        int tmp_c = 0;

        for (int i = 0; i < 81; i++) {
            tmp_r = i / 9;
            tmp_c = i % 9;
            cells[i] = {tmp_r, tmp_c};
        }

        shuffle(cells.begin(), cells.end(), gen);
    }
public:

    /**
     * Crea un sudoku completo e rimuove celle in base alla difficoltà
     * @param difficulty numero di celle da svuotare
     * @return griglia Sudoku parzialmente riempita
     */
    array<array<__int8 , 9 >, 9 > create_sudoku(int difficulty){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1,9);

        // Reset griglia
        for (int i = 0; i < 9; i++) {
            base_sudoku[i].fill(0);
        }

        // Inizializza lista random di celle
        inizializeCells();

        // Posiziona un numero casuale per avviare la generazione
        int r = dist(gen);
        int c = dist(gen);
        __int8 n = dist(gen);
        base_sudoku[r][c] = n;

        // Genera sudoku completo con backtracking
        populate_sudoku(base_sudoku, 0, 0);

        // Rimuove celle mantenendo validità
        add_spaces(base_sudoku , difficulty , 0);

        return base_sudoku;
    }

};

#endif //SUDOKU_SOLVER_SUDOKU_GENERATOR_H
