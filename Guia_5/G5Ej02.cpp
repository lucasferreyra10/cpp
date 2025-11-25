/*
Id.Programa: G5Ej02.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Procesa un archivo de GASTOS de un año calendario.
    Cada registro del archivo contiene:
        - Importe del gasto (double)
        - Mes del gasto (1..12)

    El archivo se encuentra sin orden.
    Se requiere:
      - Emitir un listado de los gastos producidos en cada mes del año
        en el mismo orden en que se conocieron los datos (orden de llegada).
      - Informar el total por cada mes.
      - Informar el total anual.

    Implementación:
      - Se utiliza un vector de listas enlazadas con puntero al final (tail)
        para insertar al final y conservar el orden de llegada.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct RegGasto {
    double importe;
    int mes;       // 1..12
};

struct Nodo {
    double importe;
    Nodo* sig;
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
    const int MAX_MESES = 12;

    // Vector de punteros a lista (una lista por mes), con tail para append
    Nodo* head[MAX_MESES + 1];
    Nodo* tail[MAX_MESES + 1];
    double totalMes[MAX_MESES + 1];

    for (int i = 1; i <= MAX_MESES; i++) {
        head[i] = tail[i] = nullptr;
        totalMes[i] = 0.0;
    }

    double totalAnual = 0.0;

    ifstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo abrir el archivo GASTOS.DAT" << endl;
        return 1;
    }

    RegGasto reg;

    // Carga: insertamos al final -> queda en orden de llegada
    while (f.read(reinterpret_cast<char*>(&reg), sizeof(RegGasto))) {
        if (reg.mes >= 1 && reg.mes <= 12) {
            Nodo* nuevo = new Nodo;
            nuevo->importe = reg.importe;
            nuevo->sig = nullptr;

            if (head[reg.mes] == nullptr) {
                head[reg.mes] = tail[reg.mes] = nuevo;
            } else {
                tail[reg.mes]->sig = nuevo;
                tail[reg.mes] = nuevo;
            }

            totalMes[reg.mes] += reg.importe;
            totalAnual += reg.importe;
        }
    }
    f.close();

    cout << fixed << setprecision(2);
    cout << "Listado de gastos por mes (orden de llegada)" << endl;
    cout << "-------------------------------------------" << endl << endl;

    for (int m = 1; m <= MAX_MESES; m++) {
        cout << "Mes: " << nombreMes(m) << endl;
        cout << "Importes:" << endl;

        Nodo* p = head[m];
        if (!p) {
            cout << "  (Sin gastos registrados)" << endl;
        } else {
            while (p != nullptr) {
                cout << "  " << p->importe << endl;
                p = p->sig;
            }
        }

        cout << "Total del mes: " << totalMes[m] << endl;
        cout << "----------------------------------------" << endl << endl;
    }

    cout << "Total anual: " << totalAnual << endl;

    // Liberar memoria
    for (int m = 1; m <= MAX_MESES; m++) {
        Nodo* p = head[m];
        while (p != nullptr) {
            Nodo* aux = p;
            p = p->sig;
            delete aux;
        }
    }

    return 0;
}
