/*
Id.Programa: G5Ej13.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Lee un archivo DATOS13.DAT desordenado y lo ordena
    por el campo clave (entero). Luego genera un archivo
    ORDENADO13.DAT y emite los registros ordenados.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct Registro {
    int clave;
    char valor[20];
};

int main() {
    ifstream f("DATOS13.DAT", ios::binary);

    if (!f) {
        cout << "No se pudo abrir DATOS13.DAT\n";
        return 1;
    }

    // Cargo los registros en memoria
    Registro vec[500];  // hasta 500 como máximo
    int n = 0;

    while (f.read((char*)&vec[n], sizeof(Registro))) {
        n++;
    }
    f.close();

    // Ordenamiento por clave (burbujeo simple UTN)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j].clave > vec[j + 1].clave) {
                Registro aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }

    // Regrabo archivo ordenado
    ofstream fo("ORDENADO13.DAT", ios::binary);

    for (int i = 0; i < n; i++) {
        fo.write((char*)&vec[i], sizeof(Registro));
    }

    fo.close();

    // Emito
    cout << "Registros ordenados por clave:\n";
    cout << "Clave  Valor\n";

    for (int i = 0; i < n; i++) {
        cout << vec[i].clave << "      " << vec[i].valor << endl;
    }

    return 0;
}
