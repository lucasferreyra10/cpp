
/*
Id.Programa: G2Ej07Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Dado un vector de N elementos, calcular segun menu:
             a) promedio, b) maximo, c) minimo, d) sumatoria.
*/

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cout << "Vector de N elementos - Menu de estadisticas\n";
    do {
        cout << "Ingrese N (N > 0): ";
        cin >> N;
    } while (N <= 0);

    vector<double> v(N);
    for (int i = 0; i < N; ++i) {
        cout << "v[" << i << "]: ";
        cin >> v[i];
    }

    cout << fixed << setprecision(4);

    int opcion;
    do {
        cout << "\nMENU\n";
        cout << "1) Promedio\n";
        cout << "2) Maximo\n";
        cout << "3) Minimo\n";
        cout << "4) Sumatoria\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            double suma = 0;
            for (double x : v) suma += x;
            cout << "Promedio = " << (suma / N) << "\n";
        } else if (opcion == 2) {
            double mx = v[0];
            for (double x : v) if (x > mx) mx = x;
            cout << "Maximo = " << mx << "\n";
        } else if (opcion == 3) {
            double mn = v[0];
            for (double x : v) if (x < mn) mn = x;
            cout << "Minimo = " << mn << "\n";
        } else if (opcion == 4) {
            double suma = 0;
            for (double x : v) suma += x;
            cout << "Sumatoria = " << suma << "\n";
        } else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
