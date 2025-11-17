/*
Id.Programa: G4Ej08_VerVendedores.cpp
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Vendedor {
    int  codVend;
    char nombre[21];
    int  porcComision;
    float importeAcumulado;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream f("VENDEDORES_ACT.DAT", ios::binary);
    if (!f) {
        cerr << "No se pudo abrir VENDEDORES_ACT.DAT\n";
        return 1;
    }

    Vendedor v;
    cout << left << setw(8) << "Cod"
         << setw(20) << "Nombre"
         << setw(8) << "%Com."
         << "Importe Acum.\n";
    cout << "---------------------------------------------\n";

    while (f.read(reinterpret_cast<char*>(&v), sizeof(v))) {
        cout << left << setw(8) << v.codVend
             << setw(20) << v.nombre
             << setw(8) << v.porcComision
             << fixed << setprecision(2) << v.importeAcumulado << "\n";
    }

    f.close();
    return 0;
}
