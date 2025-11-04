// main.cpp
// Server HTTP minimo che riceve un sudoku in JSON e risponde con la soluzione.
// Richiede: httplib.h, json.hpp (nlohmann::json) e Sudoku_Solver.h

#ifdef _WIN32
// usa l'API Win32 socket implementation di cpp-httplib su Windows
#define CPPHTTPLIB_USE_WIN32_SOCKET
#endif

#include "httplib.h"        // cpp-httplib (single-header)
#include "json.hpp"         // nlohmann::json (single-header)
#include "Sudoku_Solver.h"  // il tuo solver documentato
#include <array>
#include <iostream>

using json = nlohmann::json;
using namespace std;

int main() {
    httplib::Server svr;

    // CORS: rispondi alle richieste preflight per tutte le rotte
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 200;
    });

    // Endpoint POST /solve
    svr.Post("/solve", [](const httplib::Request& req, httplib::Response& res) {
        // Aggiungi header CORS alla risposta effettiva (singolo valore)
        res.set_header("Access-Control-Allow-Origin", "*");

        // limite semplice sulla dimensione del body
        if (req.body.size() > 64 * 1024) {
            res.status = 413;
            res.set_content(R"({"status":"error","message":"Payload too large"})", "application/json");
            return;
        }

        // parsing JSON
        json j;
        try {
            j = json::parse(req.body);
        } catch (...) {
            res.status = 400;
            res.set_content(R"({"status":"error","message":"Invalid JSON"})", "application/json");
            return;
        }

        // validazione base: chiave "grid" 9x9 con valori 0..9
        if (!j.contains("grid") || !j["grid"].is_array() || j["grid"].size() != 9) {
            res.status = 400;
            res.set_content(R"({"status":"error","message":"Missing or invalid grid"})", "application/json");
            return;
        }

        array<array<__int8,9>,9> grid;
        for (int i = 0; i < 9; ++i) {
            if (!j["grid"][i].is_array() || j["grid"][i].size() != 9) {
                res.status = 400;
                res.set_content(R"({"status":"error","message":"Grid must be 9x9"})", "application/json");
                return;
            }
            for (int k = 0; k < 9; ++k) {
                int v = j["grid"][i][k].get<int>();
                if (v < 0 || v > 9) {
                    res.status = 400;
                    res.set_content(R"({"status":"error","message":"Grid values must be 0..9"})", "application/json");
                    return;
                }
                grid[i][k] = static_cast<__int8>(v);
            }
        }

        // opzionale: verifica che i numeri forniti non violino le regole
        if (!Sudoku_Solver::test_all_sudoku(grid)) {
            res.status = 400;
            res.set_content(R"({"status":"error","message":"Grid violates Sudoku rules"})", "application/json");
            return;
        }

        // risolvi su una copia
        array<array<__int8,9>,9> working = grid;
        bool ok = Sudoku_Solver::solveSudoku(working);

        if (!ok) {
            res.status = 200;
            res.set_content(R"({"status":"error","message":"No solution"})", "application/json");
            return;
        }

        // costruisci risposta JSON con la soluzione
        json out;
        out["status"] = "ok";
        out["solution"] = json::array();
        for (int i = 0; i < 9; ++i) {
            json row = json::array();
            for (int j2 = 0; j2 < 9; ++j2) row.push_back(static_cast<int>(working[i][j2]));
            out["solution"].push_back(row);
        }

        res.set_content(out.dump(), "application/json");
    });

    cout << "Server listening on http://localhost:8080\n";
    // ascolta su tutte le interfacce (o "localhost" se preferisci)
    svr.listen("0.0.0.0", 8080);

    return 0;
}
