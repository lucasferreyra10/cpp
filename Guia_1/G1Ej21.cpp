/*
Id.Programa: G1Ej21.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Crear una funcion que recibe dos valores enteros y retorna verdadero
             si el primero es divisible por el segundo; caso contrario retorna falso.
*/

#include <iostream>
using namespace std;

// Funcion que determina si a es divisible por b
bool EsDivisible(int a, int b) {
    if (b == 0) {
        cout << "Error: el divisor no puede ser cero." << endl;
        return false;
    }
    return (a % b == 0);
}

int main() {
    int a, b;

    cout << "Determinacion de divisibilidad entre dos numeros enteros" << endl;

    cout << "Ingrese el primer numero (a): ";
    cin >> a;

    cout << "Ingrese el segundo numero (b): ";
    cin >> b;

    bool resultado = EsDivisible(a, b);

    if (b != 0) {
        if (resultado)
            cout << a << " es divisible por " << b << "." << endl;
        else
            cout << a << " no es divisible por " << b << "." << endl;
    }

    return 0;
}