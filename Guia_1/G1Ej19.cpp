/*
Id.Programa: G1Ej19.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Crear la funcion sgn(x) que retorna -1 si x < 0, 1 si x > 0, y 0 si x = 0.
*/

#include <iostream>
using namespace std;

// Funcion sgn(x)
int sgn(int x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return 0;
}

int main() {
    int valor;

    cout << "Funcion sgn(x) - Determina el signo de un numero entero" << endl;
    cout << "Ingrese un valor entero: ";
    cin >> valor;

    int resultado = sgn(valor);

    cout << "sgn(" << valor << ") = " << resultado << endl;

    return 0;
}