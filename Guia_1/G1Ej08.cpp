/*
Id.Programa: G1Ej08.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Ingresar un valor n, luego calcular la sumatoria de los numeros
             naturales hasta n inclusive y emitir su resultado.
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    long long suma = 0;

    cout << "Calculo de la sumatoria de los numeros naturales hasta n" << endl;

    // Validacion de entrada
    do {
        cout << "Ingrese n (entero >= 1): ";
        cin >> n;

        if (n < 1)
            cout << "Error: n debe ser un numero natural mayor o igual a 1." << endl;

    } while (n < 1);

    // Calculo de la sumatoria: 1 + 2 + ... + n
    for (int i = 1; i <= n; i++) {
        suma += i;
    }

    cout << "La sumatoria desde 1 hasta " << n << " es: " << suma << endl;

    return 0;
}
