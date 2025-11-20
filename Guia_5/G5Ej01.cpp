/*
Id.Programa: G5Ej01.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    A partir del archivo GASTOS.DAT, que contiene los gastos de un año calendario:
        - Importe (double)
        - Mes (1..12)

    El programa:
      - Lee los gastos sin orden y los distribuye en 12 pilas (una por mes),
        de modo que queden almacenados en el orden de llegada.
      - Luego emite, para cada mes del año, el listado de importes en
        ORDEN INVERSO respecto de cómo fueron leídos.
      - Informa el total de cada mes y el total anual.

    Archivo de entrada:
      GASTOS.DAT  (binario)
        struct Gasto {
            double importe;
            int mes;      // 1..12
        };
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Gasto {
    double importe;
    int mes; // 1..12
};

const int MAX_GASTOS_MES = 5000;  // capacidad máxima por mes

struct PilaMes {
    double importe[MAX_GASTOS_MES];
    int tope;
};

string nombreMes(int mes) {
    static string nombres[13] = {
        "", "Enero","Febrero","Marzo","Abril","Mayo","Junio",
        "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
    };
    if (mes >= 1 && mes <= 12) return nombres[mes];
    return "Mes invalido";
}

int main() {
    // Inicializar pilas por mes
    PilaMes pilas[13]; // usamos índices 1..12
    for (int m = 1; m <= 12; m++) {
        pilas[m].tope = -1;
    }

    double totalMes[13] = {0.0};
    double totalAnual = 0.0;

    ifstream fG("GASTOS.DAT", ios::binary);
    if (!fG) {
        cout << "No se pudo abrir el archivo GASTOS.DAT" << endl;
        return 1;
    }

    Gasto reg;
    while (fG.read(reinterpret_cast<char*>(&reg), sizeof(Gasto))) {
        if (reg.mes >= 1 && reg.mes <= 12) {
            if (pilas[reg.mes].tope < MAX_GASTOS_MES - 1) {
                pilas[reg.mes].tope++;
                pilas[reg.mes].importe[pilas[reg.mes].tope] = reg.importe;

                totalMes[reg.mes] += reg.importe;
                totalAnual += reg.importe;
            } else {
                cout << "Pila llena para el mes " << reg.mes << ", gasto ignorado." << endl;
            }
        } else {
            cout << "Registro con mes invalido (" << reg.mes << ") ignorado." << endl;
        }
    }
    fG.close();

    cout << fixed << setprecision(2);
    cout << "Listado de gastos por mes (en orden inverso de lectura)\n" << endl;

    for (int m = 1; m <= 12; m++) {
        cout << "Mes: " << nombreMes(m) << " (" << m << ")" << endl;
        cout << "Importes:" << endl;

        if (pilas[m].tope == -1) {
            cout << "  (Sin gastos para este mes)" << endl;
        } else {
            // Desapilar para listar en orden inverso al de lectura
            while (pilas[m].tope >= 0) {
                double imp = pilas[m].importe[pilas[m].tope];
                pilas[m].tope--;
                cout << "  " << imp << endl;
            }
        }

        cout << "Total del mes: " << totalMes[m] << "\n" << endl;
    }

    cout << "Total anual: " << totalAnual << endl;

    return 0;
}
