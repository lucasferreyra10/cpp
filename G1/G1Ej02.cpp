/*
Id.Programa: G1Ej02.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dados 2 valores enteros y distintos, emitir un cartel que informe 
             cuál es el mayor entre ellos.
*/

#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "Mostrar cartel que informe el mayor entre 2 enteros diferentes" << endl;
    cout << "Entero a: ";
    cin >> a;

    // Validar que b sea distinto de a
    do {
        cout << "Entero b: ";
        cin >> b;
        if (a == b)
            cout << "Error: los valores deben ser distintos." << endl;
    } while (a == b);

    // Comparar y mostrar el mayor
    if (a > b)
        cout << "El mayor es a (" << a << ")" << endl;
    else
        cout << "El mayor es b (" << b << ")" << endl;

    return 0;
}
