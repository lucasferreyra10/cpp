/*
Id.Programa: CrearDeudores.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Crea el archivo DEUDORES.DAT con cuotas adeudadas
    y algunas ya canceladas.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Deudor {
    char codContrib[6];
    int anio;
    int mes;
    double importe;
    char estado;
    int fechaCobro;
};

int main() {
    ofstream f("DEUDORES.DAT", ios::binary);

    Deudor arr[] = {
        {"00001", 2005,  3, 1500.00, 'A', 0},
        {"00001", 2005,  4, 1500.00, 'C', 20050415},
        {"00002", 2006,  1, 1800.00, 'A', 0},
        {"00002", 2006,  2, 1800.00, 'A', 0},
        {"00003", 2007, 12, 2200.00, 'A', 0},
        {"00004", 2004, 11, 1000.00, 'C', 20041120},
        {"00005", 2003,  5, 900.00,  'A', 0},
    };

    int n = sizeof(arr)/sizeof(Deudor);

    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&arr[i]), sizeof(Deudor));
    }

    cout << "DEUDORES.DAT creado correctamente." << endl;
    return 0;
}
