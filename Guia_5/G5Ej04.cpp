/*
Id.Programa: G5Ej04.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Procesa un archivo GASTOS.DAT con registros:
      - Importe (double)
      - Mes (1..12)
      - Dia (1..31)

    Requerido:
      - Emitir por cada mes el listado de gastos ordenado por Dia,
        acumulando los importes si hay varios gastos en un mismo día.
      - Informar total por cada mes y total anual.

    Implementación:
      - Se utiliza una tabla estática gastos[13][32] que acumula por mes/día.
      - Recorre meses 1..12 y días 1..31 para imprimir los días con importe>0.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct RegGasto {
    double importe;
    int mes;   // 1..12
    int dia;   // 1..31
};

string nombreMes(int m) {
    static string nombres[13] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    if (m >= 1 && m <= 12) return nombres[m];
    return "Mes invalido";
}

int main() {
    const int MAX_MES = 12;
    const int MAX_DIA = 31;

    // Tabla de acumulación: gastos[mes][dia]
    double gastos[MAX_MES + 1][MAX_DIA + 1] = {0.0};
    double totalMes[MAX_MES + 1] = {0.0};
    double totalAnual = 0.0;

    ifstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo abrir el archivo GASTOS.DAT" << endl;
        return 1;
    }

    RegGasto r;
    while (f.read(reinterpret_cast<char*>(&r), sizeof(RegGasto))) {
        if (r.mes >= 1 && r.mes <= MAX_MES && r.dia >= 1 && r.dia <= MAX_DIA) {
            gastos[r.mes][r.dia] += r.importe;
            totalMes[r.mes] += r.importe;
            totalAnual += r.importe;
        }
        // registros fuera de rango se ignoran
    }
    f.close();

    cout << fixed << setprecision(2);
    cout << "Listado de Gastos por Mes (ordenado por Dia acumulado)" << endl;
    cout << "-----------------------------------------------------" << endl << endl;

    for (int m = 1; m <= MAX_MES; m++) {
        cout << "Mes: " << nombreMes(m) << endl;
        cout << " Dia  Importe Acumulado" << endl;

        bool hubo = false;
        for (int d = 1; d <= MAX_DIA; d++) {
            if (gastos[m][d] > 0.0) {
                cout << setw(3) << d << "  " << setw(12) << gastos[m][d] << endl;
                hubo = true;
            }
        }

        if (!hubo) {
            cout << "  (Sin gastos registrados en este mes)" << endl;
        }

        cout << "Total del mes: " << totalMes[m] << endl;
        cout << "----------------------------------------" << endl << endl;
    }

    cout << "Total anual: " << totalAnual << endl;

    return 0;
}
