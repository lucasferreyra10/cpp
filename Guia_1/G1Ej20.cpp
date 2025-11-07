/*
Id.Programa: G1Ej20.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Crear una funcion que recibe dos valores enteros y retorna 
             el resto de la division entera.
*/

#include <iostream>
using namespace std;

// Funcion que retorna el resto de la division entera
int RestoDivision(int dividendo, int divisor) {
    return dividendo % divisor;
}

int main() {
    int a, b;

    cout << "Calculo del resto de una division entera" << endl;

    cout << "Ingrese el dividendo (entero): ";
    cin >> a;

    cout << "Ingrese el divisor (entero distinto de 0): ";
    cin >> b;

    if (b == 0) {
        cout << "Error: el divisor no puede ser cero." << endl;
        return 1;
    }

    int resto = RestoDivision(a, b);

    cout << "El resto de la division " << a << " / " << b << " es: " << resto << endl;

    return 0;
}