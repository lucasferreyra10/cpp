/*
Id.Programa: G1Ej05.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dados 2 valores enteros >= 0, hallar la potencia de a ^ b,
             siendo ambos simultáneamente distintos de cero.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b, i;
    long pot = 1;

    cout << "Hallar la potencia de a ^ b" << endl;

    // Validar que no sean ambos cero
    do {
        cout << "Entero a: ";
        cin >> a;
        cout << "Entero b: ";
        cin >> b;

        if (a == 0 && b == 0)
            cout << "Error: ambos no pueden ser cero simultáneamente." << endl;
    } while (a == 0 && b == 0);

    // Calcular potencia usando multiplicaciones sucesivas
    for (i = 1; i <= b; i++)
        pot *= a;

    cout << a << " ^ " << b << " = " << pot << endl;

    return 0;
}
