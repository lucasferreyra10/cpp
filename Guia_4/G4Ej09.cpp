/*
Id.Programa: G4Ej09.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Procesa un archivo de gastos anuales usando técnica de hashing directo.
    El archivo GASTOS.DAT contiene registros sin orden con:
        - Mes (1..12)
        - Día (1..31)
        - Importe del gasto (real)
    Puede haber varios gastos en un mismo día de un mismo mes.

    El programa genera:
      ✔ Listado ordenado por Mes y Día con el total acumulado del día
      ✔ Total del mes
      ✔ Día de menor gasto por cada mes
      ✔ Total anual
      ✔ Mes cuyo menor gasto fue el más alto ("mayor de los menores")

    Usa una tabla hash directa de 12x31 para acumular importes por día.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Gasto {
    int mes;      // 1..12
    int dia;      // 1..31
    double importe;
};

string nombreMes(int mes) {
    static string nombres[13] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    return (mes >= 1 && mes <= 12) ? nombres[mes] : "Mes inválido";
}

int main() {

    const int MAX_MES = 12;
    const int MAX_DIA = 31;

    double gastos[MAX_MES + 1][MAX_DIA + 1] = {0};

    ifstream fG("GASTOS.DAT", ios::binary);
    if (!fG) {
        cout << "No se pudo abrir el archivo GASTOS.DAT" << endl;
        return 1;
    }

    Gasto reg;
    while (fG.read(reinterpret_cast<char*>(&reg), sizeof(Gasto))) {
        if (reg.mes >= 1 && reg.mes <= 12 && reg.dia >= 1 && reg.dia <= 31) {
            gastos[reg.mes][reg.dia] += reg.importe;
        }
    }
    fG.close();

    cout << fixed << setprecision(2);
    cout << "Listado de Gastos ordenado por Mes y Dia acumulado" << endl << endl;

    double totalAnual = 0.0;
    int mesMayorGastoMenor = 0;
    double mayorGastoMenor = -1;

    for (int m = 1; m <= MAX_MES; m++) {
        cout << "Mes: " << nombreMes(m) << endl;
        cout << " Dia  Importe Acumulado" << endl;

        double totalMes = 0.0;
        bool tieneGastos = false;
        double minGastoMes = 0.0;
        int diaMinGasto = 0;
        bool primerDia = true;

        for (int d = 1; d <= MAX_DIA; d++) {
            if (gastos[m][d] != 0) {
                cout << setw(3) << d << "  " << setw(10) << gastos[m][d] << endl;
                totalMes += gastos[m][d];
                tieneGastos = true;

                if (primerDia) {
                    minGastoMes = gastos[m][d];
                    diaMinGasto = d;
                    primerDia = false;
                } else if (gastos[m][d] < minGastoMes) {
                    minGastoMes = gastos[m][d];
                    diaMinGasto = d;
                }
            }
        }

        cout << "Total del mes: " << totalMes << endl;

        if (tieneGastos) {
            cout << "Dia de menor gasto: " << diaMinGasto << endl;

            if (mesMayorGastoMenor == 0 || minGastoMes > mayorGastoMenor) {
                mayorGastoMenor = minGastoMes;
                mesMayorGastoMenor = m;
            }

        } else {
            cout << "Dia de menor gasto: - (sin gastos)" << endl;
        }

        cout << endl;
        totalAnual += totalMes;
    }

    cout << "Total anual: " << totalAnual << endl;
    cout << "Nro. de mes de mayor gasto de los menores: " << mesMayorGastoMenor << endl;

    return 0;
}