
/*
Id.Programa: G2Ej11Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Campeonato de tiro: 15 tiradores, 3 puntajes cada uno.
             Emitir clasificacion ordenada por puntaje total.
*/

#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Tirador {
    int num;       // 1..15
    double p1, p2, p3;
    double total() const { return p1 + p2 + p3; }
};

int main() {
    array<Tirador, 15> v{};
    cout << "Ingresar 15 registros (num, p1, p2, p3)\n";
    for (int i = 0; i < 15; ++i) {
        cout << "Registro #" << (i+1) << " - num p1 p2 p3: ";
        cin >> v[i].num >> v[i].p1 >> v[i].p2 >> v[i].p3;
    }

    sort(v.begin(), v.end(), [](const Tirador& a, const Tirador& b){
        if (a.total() != b.total()) return a.total() > b.total(); // desc
        return a.num < b.num;
    });

    cout << "\nPosic.  Tirador  Puntaje\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < 15; ++i) {
        cout << setw(5) << (i+1) << "  " << setw(7) << v[i].num << "  " << setw(7) << v[i].total() << "\n";
    }
    return 0;
}
