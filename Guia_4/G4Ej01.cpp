/*
Id.Programa: G4Ej01.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Crea el archivo ARTICULOS.DAT en forma secuencial.
    Cada registro contiene:
      - Código de artículo (1..100)
      - Descripción (cadena de 20 caracteres)
      - Precio unitario (>0)
    Los datos se ingresan por teclado sin orden.
    Se valida cada campo antes de grabar.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Articulo {
    int codigo;
    char descripcion[21];
    float precio;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream arch("ARTICULOS.DAT", ios::binary);
    if (!arch) {
        cerr << "Error al crear el archivo.\n";
        return 1;
    }

    cout << "=== CARGA DE ARTICULOS ===\n";
    cout << "(Ingrese codigo 0 para finalizar)\n\n";

    Articulo art;
    while (true) {
        cout << "Codigo de articulo (1..100): ";
        cin >> art.codigo;
        if (art.codigo == 0) break;

        if (art.codigo < 1 || art.codigo > 100) {
            cout << "  ❌ Codigo fuera de rango.\n";
            continue;
        }

        cout << "Descripcion (max 20 caracteres, sin espacios): ";
        cin >> ws; // limpiar espacios previos
        string desc;
        getline(cin, desc);

        if (desc.empty() || desc.size() > 20) {
            cout << "  ❌ Descripcion invalida.\n";
            continue;
        }
        strncpy(art.descripcion, desc.c_str(), 20);
        art.descripcion[20] = '\0';

        cout << "Precio unitario (>0): ";
        cin >> art.precio;

        if (art.precio <= 0) {
            cout << "  ❌ Precio invalido.\n";
            continue;
        }

        arch.write(reinterpret_cast<char*>(&art), sizeof(art));
        cout << "✅ Articulo grabado correctamente.\n\n";
    }

    arch.close();
    cout << "\nArchivo ARTICULOS.DAT creado exitosamente.\n";
    return 0;
}