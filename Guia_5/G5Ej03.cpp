/*
Id.Programa: G5Ej03.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Procesa el archivo GASTOS.DAT con:
        - Importe (double)
        - Mes (1..12)

    Requerido:
      - Emitir los gastos de cada mes ORDENADOS por importe (creciente).
      - Informar total por mes.
      - Informar total anual.

    Implementación:
      - Vector de 12 listas enlazadas.
      - Inserción ordenada por importe dentro de cada mes.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct RegGasto {
    double importe;
    int mes;   // 1..12
};

struct Nodo {
    double importe;
    Nodo* sig;
};

string nombreMes(int m) {
    static string n[13] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    return (m >= 1 && m <= 12 ? n[m] : "Mes invalido");
}

void insertarOrdenado(Nodo*& lista, double importe) {
    Nodo* nuevo = new Nodo;
    nuevo->importe = importe;

    // Insertar al inicio si corresponde
    if (lista == nullptr || importe < lista->importe) {
        nuevo->sig = lista;
        lista = nuevo;
        return;
    }

    // Búsqueda de posición
    Nodo* p = lista;
    while (p->sig != nullptr && p->sig->importe <= importe)
        p = p->sig;

    nuevo->sig = p->sig;
    p->sig = nuevo;
}

int main() {
    const int MAX_MES = 12;

    Nodo* lista[MAX_MES + 1];
    double totalMes[MAX_MES + 1];
    double totalAnual = 0;

    for (int i = 1; i <= MAX_MES; i++) {
        lista[i] = nullptr;
        totalMes[i] = 0;
    }

    ifstream f("GASTOS.DAT", ios::binary);
    if (!f) {
        cout << "No se pudo abrir GASTOS.DAT" << endl;
        return 1;
    }

    RegGasto r;

    // Carga e inserción ordenada
    while (f.read(reinterpret_cast<char*>(&r), sizeof(RegGasto))) {
        if (r.mes >= 1 && r.mes <= 12) {
            insertarOrdenado(lista[r.mes], r.importe);
            totalMes[r.mes] += r.importe;
            totalAnual += r.importe;
        }
    }

    f.close();

    cout << fixed << setprecision(2);
    cout << "Listado de gastos por mes (ordenado por importe)" << endl;
    cout << "-------------------------------------------------" << endl << endl;

    for (int m = 1; m <= MAX_MES; m++) {
        cout << "Mes: " << nombreMes(m) << endl;

        Nodo* p = lista[m];
        if (!p) {
            cout << "  (Sin gastos)" << endl;
        } else {
            while (p != nullptr) {
                cout << "  " << p->importe << endl;
                p = p->sig;
            }
        }

        cout << "Total del mes: " << totalMes[m] << endl;
        cout << "----------------------------------------" << endl << endl;
    }

    cout << "TOTAL ANUAL: " << totalAnual << endl;

    // Liberar memoria
    for (int m = 1; m <= MAX_MES; m++) {
        Nodo* p = lista[m];
        while (p != nullptr) {
            Nodo* aux = p;
            p = p->sig;
            delete aux;
        }
    }

    return 0;
}
