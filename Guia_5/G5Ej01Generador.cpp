/*
Id.Programa: G5Ej01Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Genera el archivo GASTOS.DAT de prueba para el ejercicio G5Ej01.
    Cada registro contiene:
        - Importe del gasto (double)
        - Mes del gasto (1..12)
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

    RegGasto v[] = {
        { 1500.50, 1 },
        {  200.00, 1 },
        {  750.25, 3 },
        { 3200.00, 12 },
        {  999.99, 5 },
        {  450.00, 3 },
        { 1800.00, 12 },
        {  600.00, 5 },
        {  300.00, 1 },
        { 2100.00, 8 },
        {  700.00, 8 },
        {  500.00, 2 }
    };

    int n = sizeof(v) / sizeof(RegGasto);
    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&v[i]), sizeof(RegGasto));
    }

    f.close();
    cout << "GASTOS.DAT generado correctamente." << endl;
    return 0;
}
