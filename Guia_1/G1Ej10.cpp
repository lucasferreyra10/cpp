/*
Id.Programa: G1Ej10.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dado un valor n, entero positivo incluido el cero, obtener cada uno
             de los terminos de la sucesion de Fibonacci.
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Generar la sucesion de Fibonacci hasta el termino n" << endl;

    // Validar que n sea >= 0
    do {
        cout << "Ingrese n (entero >= 0): ";
        cin >> n;
        if (n < 0) cout << "Error: n debe ser un entero no negativo." << endl;
    } while (n < 0);

    // Casos especiales
    if (n == 0) {
        cout << "Sucesion: 0" << endl;
        return 0;
    }
    if (n == 1) {
        cout << "Sucesion: 0 1" << endl;
        return 0;
    }

    // Generar sucesion
    long long a = 0, b = 1, c;
    cout << "Sucesion: " << a << " " << b << " ";

    for (int i = 2; i <= n; i++) {
        c = a + b;
        cout << c << " ";
        a = b;
        b = c;
    }

    cout << endl;
    return 0;
}
