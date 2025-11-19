/*
Id.Programa: CrearDatoPers.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Crea el archivo DATOPERS.DAT con datos personales
    (ordenados por codContribuyente).
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct DatoPers {
    char codContrib[6];
    char apeNom[46];
    char domicilio[46];
    char codZona[5];
};

int main() {
    ofstream f("DATOPERS.DAT", ios::binary);

    DatoPers arr[] = {
        {"00001", "Juan Perez",          "Mitre 123",       "A001"},
        {"00002", "Maria Lopez",         "Sarmiento 555",   "A002"},
        {"00003", "Carlos Rodriguez",    "Belgrano 802",    "A001"},
        {"00004", "Ana Fernandez",       "Alsina 430",      "A003"},
        {"00005", "Luis Martinez",       "Rivadavia 900",   "A002"},
    };

    int n = sizeof(arr)/sizeof(DatoPers);

    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&arr[i]), sizeof(DatoPers));
    }

    cout << "DATOPERS.DAT creado correctamente." << endl;
    return 0;
}
