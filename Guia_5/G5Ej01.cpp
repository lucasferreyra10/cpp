/*
Id.Programa: G5Ej01.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025
Comentario.: Archivo de Gastos (importe real, mes 1..12) sin orden.
             Emitir por cada mes los gastos en orden inverso al de llegada,
             ademas total por mes y total anual.
             Se usan listas enlazadas por mes y recursion para imprimir en reversa.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Nodo {
    double importe;
    Nodo* sig;
    Nodo(double x) : importe(x), sig(nullptr) {}
};

// agrega al final para conservar orden de llegada
void append(Nodo*& head, Nodo*& tail, double importe) {
    Nodo* n = new Nodo(importe);
    if (!head) { head = tail = n; }
    else { tail->sig = n; tail = n; }
}

// imprime en orden inverso al de llegada usando recursion
void imprimirReverso(Nodo* head) {
    if (!head) return;
    imprimirReverso(head->sig);
    cout << "  - $" << fixed << setprecision(2) << head->importe << "\n";
}

// libera memoria de una lista
void liberar(Nodo*& head) {
    while (head) {
        Nodo* t = head;
        head = head->sig;
        delete t;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 12 listas (1..12). Usamos 13 para indexar directo por mes.
    Nodo* head[13] = {nullptr};
    Nodo* tail[13] = {nullptr};
    double totalMes[13] = {0.0};
    double totalAnual = 0.0;

    // abrir archivo
    ifstream in("gastos.txt");
    if (!in) {
        cout << "No se pudo abrir el archivo 'gastos.txt'.\n";
        cout << "Formato esperado por linea: <importe> <mes>\n";
        cout << "Ejemplo:\n";
        cout << "  1234.50 3\n  980.00 3\n  250.75 12\n";
        return 1;
    }

    // lectura
    double importe;
    int mes;
    int registros = 0;
    while (in >> importe >> mes) {
        if (mes < 1 || mes > 12) {
            cout << "Registro ignorado (mes invalido): " << importe << " " << mes << "\n";
            continue;
        }
        append(head[mes], tail[mes], importe);
        totalMes[mes] += importe;
        totalAnual += importe;
        registros++;
    }
    in.close();

    cout << "GASTOS ANUALES (" << registros << " registros leidos)\n";
    cout << "Listado por mes en orden inverso de llegada\n\n";

    // emitir por mes
    for (int m = 1; m <= 12; ++m) {
        static const char* nombreMes[13] = {
            "", "Enero","Febrero","Marzo","Abril","Mayo","Junio",
            "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
        };

        cout << "Mes " << setw(2) << m << " - " << nombreMes[m] << "\n";
        if (!head[m]) {
            cout << "  (sin gastos)\n";
        } else {
            imprimirReverso(head[m]); // recursion -> imprime al reves del ingreso
        }
        cout << "  Total mes: $" << fixed << setprecision(2) << totalMes[m] << "\n\n";
    }

    cout << "---------------------------------------------\n";
    cout << "TOTAL ANUAL: $" << fixed << setprecision(2) << totalAnual << "\n";

    // liberar memoria
    for (int m = 1; m <= 12; ++m) liberar(head[m]);

    return 0;
}
