/*
Id.Programa: G1Ej07Ef.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dado un valor entero n, generar una aproximación del número irracional e.
             Versión optimizada.
*/

#include <iostream>
using namespace std;

int main() {
    int n, i;
    long fact = 1;
    double e = 1.0; // Mejor precision usando double

    cout << "Hallar una aproximacion del numero irracional e (version optimizada)" << endl;
    cout << "Ingrese el valor entero n (cantidad de terminos): ";
    cin >> n;

    if (n < 0) {
        cout << "Error: n debe ser un numero entero no negativo." << endl;
        return 1;
    }

    // Calculo eficiente: reutiliza fact sin recalcularlo desde cero
    for (i = 1; i <= n; i++) {
        fact *= i;       // fact = i!
        e += 1.0 / fact; // suma 1/i!
    }

    cout << "Aproximacion de e usando " << n << " terminos: " << e << endl;

    return 0;
}
