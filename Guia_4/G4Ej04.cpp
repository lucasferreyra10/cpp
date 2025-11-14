/*
Id.Programa: G4Ej04.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Crea el archivo cascarón ARTREL.DAT con 100 registros.
    Cada registro tiene:
      - Código de artículo (1..100)
      - Nombre (cadena de 20 caracteres)
      - Precio unitario (float)
    El registro 0 se crea pero no se utiliza.
    Un código = 0 indica que el registro no está activo.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct ArticuloRel {
    int codigo;         // 0 = inactivo
    char nombre[21];
    float precio;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream arch("ARTREL.DAT", ios::binary | ios::trunc);
    if (!arch) {
        cerr << "❌ Error al crear ARTREL.DAT\n";
        return 1;
    }

    ArticuloRel art;
    cout << "=== CREACION DE ARCHIVO CASCARON ARTREL.DAT ===\n";
    cout << "(100 registros, registro 0 no utilizado)\n";

    for (int i = 0; i <= 100; ++i) {
        art.codigo = 0;  // todos inactivos al principio
        strcpy(art.nombre, ""); 
        art.precio = 0.0f;
        arch.write(reinterpret_cast<char*>(&art), sizeof(art));
    }

    arch.close();
    cout << "\n✅ Archivo ARTREL.DAT creado con éxito (101 registros: 0–100).\n";
    return 0;
}
