/*
Id.Programa: G1Ej07.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dado un valor entero n, generar una aproximación del número irracional e.
*/

#include <iostream>
using namespace std;

int main() {
    int n, i, j;
    long fact;
    double e = 1.0; // e comienza con el primer término 1/0! = 1

    cout << "Hallar una aproximacion del numero irracional e" << endl;
    cout << "Ingrese el valor entero n (cantidad de terminos): ";
    cin >> n;

    if (n < 0) {
        cout << "Error: n debe ser un numero entero no negativo." << endl;
        return 1;
    }

    // Serie de e = 1 + 1/1! + 1/2! + 1/3! + ... + 1/n!
    for (i = 1; i <= n; i++) {
        fact = 1;
        for (j = i; j >= 1; j--) {
            fact *= j;
        }
        e += 1.0 / fact;
    }

    cout << "Aproximacion de e usando " << n << " terminos: " << e << endl;

    return 0;
}
