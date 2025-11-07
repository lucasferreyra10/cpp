/*
Id.Programa: G1Ej07.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Hallar el numero irracional e, ingresando n (n >= 0) que indica
             la cantidad de terminos a sumar en la serie.
*/

#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Calculo aproximado de e mediante serie" << endl;

    // validar n >= 0
    do {
        cout << "Ingrese n (entero >= 0): ";
        cin >> n;
        if (n < 0) cout << "Error: n no puede ser negativo." << endl;
    } while (n < 0);

    // e = sum_{k=0..n} 1/k!
    double e = 1.0;    // termino k=0 -> 1/0! = 1
    double fact = 1.0; // iremos construyendo k! en una sola pasada

    for (int k = 1; k <= n; ++k) {
        fact *= k;        // fact = k!
        e += 1.0 / fact;  // sumar 1/k!
    }

    cout << "Aproximacion de e con " << n << " terminos: " << e << endl;
    return 0;
}
