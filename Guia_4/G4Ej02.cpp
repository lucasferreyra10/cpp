/*
Id.Programa: G4Ej02.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Actualiza el archivo ARTICULOS.DAT aplicando un porcentaje único
    de aumento o descuento sobre el campo Precio de todos los registros.
    El porcentaje se ingresa por teclado (puede ser positivo o negativo).
    Los cambios se graban en el mismo archivo binario.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Articulo {
    int codigo;
    char descripcion[21];
    float precio;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fstream arch("ARTICULOS.DAT", ios::in | ios::out | ios::binary);
    if (!arch) {
        cerr << "❌ No se pudo abrir el archivo ARTICULOS.DAT.\n";
        return 1;
    }

    float porc;
    cout << "Ingrese porcentaje de actualización (ej: 10 = +10%, -5 = -5%): ";
    cin >> porc;

    porc = porc / 100.0f; // convertir a fracción

    Articulo art;
    cout << fixed << setprecision(2);
    cout << "\n=== ACTUALIZACION DE PRECIOS ===\n";

    // Leer y actualizar en el mismo archivo
    while (arch.read(reinterpret_cast<char*>(&art), sizeof(art))) {
        float precio_ant = art.precio;
        art.precio += art.precio * porc;
        if (art.precio < 0) art.precio = 0; // por seguridad

        // Mover el puntero de escritura una posición atrás
        arch.seekp(-static_cast<int>(sizeof(art)), ios::cur);
        arch.write(reinterpret_cast<char*>(&art), sizeof(art));
        arch.flush();

        cout << "Cod:" << setw(3) << art.codigo
             << "  Desc:" << setw(20) << art.descripcion
             << "  Precio anterior: $" << setw(8) << precio_ant
             << "  Nuevo: $" << setw(8) << art.precio << "\n";
    }

    arch.close();
    cout << "\n✅ Archivo actualizado correctamente.\n";
    return 0;
}
