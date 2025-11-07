/*
Id.Programa: G1Ej02.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dados dos valores enteros a y b, distintos entre sí,
             emitir un cartel que informe cuál de los dos es mayor.
*/

#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "Comparacion entre dos valores enteros distintos" << endl;
    cout << "Ingrese el valor de a: ";
    cin >> a;
    cout << "Ingrese el valor de b: ";
    cin >> b;

    // Validar que sean distintos
    if (a == b) {
        cout << "Error: los valores deben ser distintos." << endl;
        return 1;
    }

    // Determinar cual es mayor
    if (a > b)
        cout << "El mayor es a (" << a << ")." << endl;
    else
        cout << "El mayor es b (" << b << ")." << endl;

    return 0;
}
