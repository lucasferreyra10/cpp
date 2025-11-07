/*
Id.Programa: G1Ej12.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dada una lista de n valores enteros, encontrar el mayor valor y su posicion.
*/

#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Busqueda del mayor valor y su posicion en una lista" << endl;

    // Validacion de n
    do {
        cout << "Ingrese la cantidad de elementos n (entero > 0): ";
        cin >> n;
        if (n <= 0)
            cout << "Error: n debe ser mayor que cero." << endl;
    } while (n <= 0);

    int valor;
    int mayor;
    int posicion_mayor = 1;

    cout << "Ingrese el valor 1: ";
    cin >> mayor;  // el primero se asume como el mayor inicial

    // Leer los demas valores
    for (int i = 2; i <= n; i++) {
        cout << "Ingrese el valor " << i << ": ";
        cin >> valor;

        if (valor > mayor) {
            mayor = valor;
            posicion_mayor = i;
        }
    }

    cout << "El mayor valor es: " << mayor << " (posicion " << posicion_mayor << ")" << endl;

    return 0;
}