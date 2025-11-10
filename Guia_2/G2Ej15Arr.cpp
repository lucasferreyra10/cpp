
/*
Id.Programa: G2Ej15Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Ventas por modelo (1..7) y color (A..E). Emitir totales por modelo, por color y total general.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    const int MODELOS = 7;
    const int COLORES = 5; // A..E
    long mat[MODELOS+1][COLORES] = {0}; // indices 1..7, 0..4 para A..E
    long totModelo[MODELOS+1] = {0};
    long totColor[COLORES] = {0};
    long total = 0;

    int R;
    cout << "Cantidad de registros de ventas: ";
    cin >> R;
    for (int i=0;i<R;++i) {
        int mod; char col; int cant;
        cout << "Venta #" << (i+1) << " (modelo 1..7, color A..E, cantidad): ";
        cin >> mod >> col >> cant;
        if (mod<1||mod>7) continue;
        int idx = (col-'A');
        if (idx<0||idx>=COLORES) continue;
        mat[mod][idx] += cant;
    }

    // calcular totales
    for (int m=1;m<=MODELOS;++m)
        for (int c=0;c<COLORES;++c) {
            totModelo[m] += mat[m][c];
            totColor[c] += mat[m][c];
            total += mat[m][c];
        }

    cout << "\nTotales por modelo y color\n";
    cout << "       ";
    for (int c=0;c<COLORES;++c) cout << "  " << char('A'+c) << "  ";
    cout << " | Total\n";
    for (int m=1;m<=MODELOS;++m) {
        cout << "Mod " << m << " ";
        for (int c=0;c<COLORES;++c) cout << setw(4) << mat[m][c] << " ";
        cout << " | " << totModelo[m] << "\n";
    }
    cout << "TotalC ";
    for (int c=0;c<COLORES;++c) cout << setw(4) << totColor[c] << " ";
    cout << " | " << total << "\n";

    return 0;
}
