/*
Id.Programa: G5Ej02Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Genera el archivo GASTOS.DAT de prueba para el ejercicio G5Ej02.
    Cada registro contiene:
        - Importe del gasto (double)
        - Mes del gasto (1..12)
    Los registros se escriben en un orden específico para probar
    que el listado respete el orden de llegada.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct RegGasto {
    double importe;
    int mes;       // 1..12
};

int main() {
    ofstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo crear GASTOS.DAT" << endl;
        return 1;
    }

    // Orden intencional: mezclado para probar orden de llegada
    RegGasto v[] = {
        { 100.00, 1 },
        { 200.00, 2 },
        { 150.00, 1 },
        { 300.00, 3 },
        { 125.50, 2 },
        { 400.00, 1 },
        {  75.25, 12 },
        { 500.00, 7 },
        { 250.00, 2 },
        { 600.00, 12 },
        {  50.00, 1 }
    };

    int n = sizeof(v) / sizeof(RegGasto);
    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&v[i]), sizeof(RegGasto));
    }

    f.close();
    cout << "GASTOS.DAT generado correctamente." << endl;
    return 0;
}
