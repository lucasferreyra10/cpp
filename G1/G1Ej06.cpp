/*
Id.Programa: G1Ej06.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dado un valor entero n, hallar su factorial.
*/

#include <iostream>
using namespace std;

int main() {
    int n, i;
    long fact = 1;

    cout << "Hallar el factorial de n" << endl;
    cout << "Entero n: ";
    cin >> n;

    if (n < 0) {
        cout << "Error: el factorial no está definido para números negativos." << endl;
        return 1; // salir con error
    }

    for (i = n; i >= 1; i--)
        fact *= i;

    cout << n << "! = " << fact << endl;

    return 0;
}
