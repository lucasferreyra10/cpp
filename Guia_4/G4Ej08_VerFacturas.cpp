/*
Id.Programa: G4Ej08_VerFacturas.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025
Comentario.:
    Lista el contenido de FACTURAS.DAT por pantalla.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Factura {
    int  nroFactura;
    int  fecha;     // ddmmaa
    int  codCli;
    float importe;
    char estado;    // 'A' / 'P'
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream f("FACTURAS.DAT", ios::binary);
    if (!f) {
        cerr << "No se pudo abrir FACTURAS.DAT\n";
        return 1;
    }

    Factura fac;
    cout << left << setw(10) << "NroFac"
         << setw(10) << "Fecha"
         << setw(12) << "CodCli"
         << setw(12) << "Importe"
         << "Estado\n";
    cout << "---------------------------------------------\n";

    while (f.read(reinterpret_cast<char*>(&fac), sizeof(fac))) {
        cout << left << setw(10) << fac.nroFactura
             << setw(10) << fac.fecha
             << setw(12) << fac.codCli
             << setw(12) << fixed << setprecision(2) << fac.importe
             << fac.estado << "\n";
    }

    f.close();
    return 0;
}