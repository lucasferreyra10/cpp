/*
Id.Programa: G4Ej03.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    A partir de ARTICULOS.DAT genera MAYORES.DAT con los registros
    cuyo precio sea mayor a un valor umbral ingresado por teclado.
    Formato de salida: (Codigo, Precio).
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct ArticuloIn {
    int   codigo;
    char  descripcion[21];
    float precio;
};

struct ArticuloOut {
    int   codigo;
    float precio;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("ARTICULOS.DAT", ios::binary);
    if (!in) {
        cerr << "❌ No se pudo abrir ARTICULOS.DAT (ejecute G4Ej01 primero).\n";
        return 1;
    }

    ofstream out("MAYORES.DAT", ios::binary | ios::trunc);
    if (!out) {
        cerr << "❌ No se pudo crear MAYORES.DAT.\n";
        return 1;
    }

    float umbral;
    cout << "Valor umbral de precio: ";
    cin  >> umbral;

    ArticuloIn  a;
    ArticuloOut b;
    std::size_t cant = 0;

    while (in.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        if (a.precio > umbral) {
            b.codigo = a.codigo;
            b.precio = a.precio;
            out.write(reinterpret_cast<char*>(&b), sizeof(b));
            ++cant;
        }
    }

    in.close();
    out.close();

    cout << "✅ Generado MAYORES.DAT con " << cant 
         << " registro(s) (precio > " << fixed << setprecision(2) << umbral << ").\n";
    return 0;
}