/*
Id.Programa: G1Ej06.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dado un valor n, entero positivo incluido el cero, hallar el factorial de n.
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    long long factorial = 1;

    cout << "Calculo del factorial de n" << endl;

    // Validacion de entrada
    do {
        cout << "Ingrese n (entero >= 0): ";
        cin >> n;

        if (n < 0)
            cout << "Error: n debe ser un numero entero no negativo." << endl;

    } while (n < 0);

    // Caso especial: 0! = 1
    if (n == 0) {
        cout << "0! = 1" << endl;
        return 0;
    }

    // Calculo del factorial
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    cout << n << "! = " << factorial << endl;

    return 0;
}
