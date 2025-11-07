/*
Id.Programa: G1Ej09.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Calcular la sumatoria de los numeros naturales hasta n inclusive
             usando formula cerrada para optimizar el tiempo de proceso.
*/

#include <iostream>
using namespace std;

int main() {
    long long n;

    cout << "Calculo optimizado de la sumatoria hasta n (n >= 1)" << endl;

    // Validacion de entrada
    do {
        cout << "Ingrese n (entero >= 1): ";
        cin >> n;
        if (n < 1) cout << "Error: n debe ser >= 1." << endl;
    } while (n < 1);

    // Formula cerrada: suma = n * (n + 1) / 2
    long long suma = n * (n + 1) / 2;

    cout << "La sumatoria desde 1 hasta " << n << " es: " << suma << endl;
    return 0;
}
