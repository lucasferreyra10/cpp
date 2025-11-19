/*
Id.Programa: CrearCobroMes.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Crea el archivo COBROMES.DAT ordenado por fecha de cobro
    y luego por contribuyente.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct CobroMes {
    char codContrib[6];
    int anio;
    int mes;
    int fechaCobro;
};

int main() {
    ofstream f("COBROMES.DAT", ios::binary);

    CobroMes arr[] = {
        {"00001", 2005, 3, 20250910},  // paga cuota que adeuda
        {"00002", 2006, 1, 20250911},
        {"00003", 2007, 12, 20250912},
        {"00001", 2005, 4, 20250913},  // esta ya está cancelada -> error E
        {"00005", 2003, 5, 20250914},
    };

    int n = sizeof(arr)/sizeof(CobroMes);

    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&arr[i]), sizeof(CobroMes));
    }

    cout << "COBROMES.DAT creado correctamente." << endl;
    return 0;
}
