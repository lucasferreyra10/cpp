/*
Id.Programa: G5Ej03Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Genera archivo GASTOS.DAT para probar G5Ej03.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct RegGasto {
    double importe;
    int mes;
};

int main() {

    ofstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo crear GASTOS.DAT" << endl;
        return 1;
    }

    RegGasto v[] = {
        { 500, 1 }, { 120, 1 }, { 300, 1 },
        {  50, 2 }, {  75, 2 }, { 700, 2 },
        { 900, 12 }, { 100, 12 }, { 450, 12 },
        { 600, 7 }, { 200, 7 }
    };

    int n = sizeof(v) / sizeof(RegGasto);
    for (int i = 0; i < n; i++)
        f.write(reinterpret_cast<char*>(&v[i]), sizeof(RegGasto));

    f.close();

    cout << "GASTOS.DAT generado correctamente." << endl;
    return 0;
}
