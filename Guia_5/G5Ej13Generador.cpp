/*
Id.Programa: G5Ej13Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Genera un archivo llamado DATOS13.DAT con registros desordenados.
    Cada registro contiene:
      - clave (int)
      - valor  (char[20])
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Registro {
    int clave;
    char valor[20];
};

int main() {
    ofstream f("DATOS13.DAT", ios::binary);

    if (!f) {
        cout << "No se pudo crear el archivo.\n";
        return 1;
    }

    Registro r;

    int claves[] = {50, 12, 90, 3, 33, 18};
    const char* textos[] = {"A", "B", "C", "D", "E", "F"};

    for (int i = 0; i < 6; i++) {
        r.clave = claves[i];
        strcpy(r.valor, textos[i]);
        f.write((char*)&r, sizeof(r));
    }

    f.close();
    cout << "Archivo DATOS13.DAT generado correctamente.\n";
    return 0;
}
