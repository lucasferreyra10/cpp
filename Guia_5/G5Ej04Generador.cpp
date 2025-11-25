/*
Id.Programa: G5Ej04Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Genera GASTOS.DAT con registros:
      - Importe (double)
      - Mes (1..12)
      - Dia (1..31)

    Incluye varios gastos repetidos para un mismo dia/mes
    para probar la acumulación por día.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct RegGasto {
    double importe;
    int mes;
    int dia;
};

int main() {
    ofstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo crear GASTOS.DAT" << endl;
        return 1;
    }

    RegGasto v[] = {
        { 100.00, 1,  1 },
        { 200.00, 1,  1 }, // mismo dia -> acumulado 300
        { 150.00, 1, 15 },
        {  50.25, 2,  3 },
        {  75.75, 2,  3 }, // acumulado 126.00
        { 500.00, 2, 10 },
        { 300.00, 3,  5 },
        { 120.00, 3,  5 }, // acumulado 420.00? actually 420? (300+120)
        { 999.99,12,31 },
        {1800.00,12,31 }, // acum
        {  60.00, 5, 20 },
        {  40.00, 5, 20 }, // acum
        { 250.00, 7,  7 },
        { 250.00, 7,  7 }, // acum
        {  30.00,11,11 }
    };

    int n = sizeof(v) / sizeof(RegGasto);
    for (int i = 0; i < n; i++) {
        f.write(reinterpret_cast<char*>(&v[i]), sizeof(RegGasto));
    }

    f.close();
    cout << "GASTOS.DAT generado correctamente." << endl;
    return 0;
}
