
/*
Id.Programa: G2Ej12Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Encuesta musical.
             a) Lista ordenada (desc) de codigos 1..30 por votos totales.
             b) Codigo mas votado por hombres de 30+.
             c) Codigos no elegidos por ninguna mujer.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

int main() {
    int M;
    cout << "Cantidad de encuestados: ";
    cin >> M;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    const int T = 30;
    long votosTot[T+1] = {0};
    long votosH30[T+1] = {0};
    long votosMuj[T+1] = {0};

    for (int i = 0; i < M; ++i) {
        char sexo; int edad; int t1, t2, t3;
        cout << "\nRegistro #" << (i+1) << "\n";
        cout << "Sexo (M/F): "; cin >> sexo;
        cout << "Edad (15..50): "; cin >> edad;
        cout << "3 temas preferidos (1..30): ";
        cin >> t1 >> t2 >> t3;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int temas[3] = {t1, t2, t3};
        for (int k = 0; k < 3; ++k) {
            int c = temas[k];
            if (c >= 1 && c <= T) {
                votosTot[c]++;
                if (sexo=='M' || sexo=='m') {
                    if (edad >= 30) votosH30[c]++;
                } else if (sexo=='F' || sexo=='f') {
                    votosMuj[c]++;
                }
            }
        }
    }

    // a) ordenar codigos por votos totales desc
    vector<pair<long,int>> orden;
    for (int c = 1; c <= T; ++c) orden.push_back({votosTot[c], c});
    sort(orden.begin(), orden.end(), [](auto& A, auto& B){
        if (A.first != B.first) return A.first > B.first;
        return A.second < B.second;
    });

    cout << "\nLista ordenada por votos (desc):\n";
    for (auto &pr : orden) {
        cout << "Tema " << pr.second << " -> " << pr.first << " votos\n";
    }

    // b) mas votado por hombres 30+
    int bestC = 1; long bestV = votosH30[1];
    for (int c = 2; c <= T; ++c) if (votosH30[c] > bestV) { bestV = votosH30[c]; bestC = c; }
    cout << "\nTema mas votado por hombres de 30+ : " << bestC << " (" << bestV << " votos)\n";

    // c) temas no elegidos por ninguna mujer
    cout << "\nTemas sin votos de mujeres: ";
    bool alguno = false;
    for (int c = 1; c <= T; ++c) if (votosMuj[c] == 0) { cout << c << " "; alguno = true; }
    if (!alguno) cout << "(ninguno)";
    cout << "\n";

    return 0;
}
