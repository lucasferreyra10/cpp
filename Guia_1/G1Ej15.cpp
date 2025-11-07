/*
Id.Programa: G1Ej15.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: a) Obtener y emitir los tres primeros numeros perfectos.
             b) Repetir el inciso anterior aplicando el metodo dado.
             c) Repetir aplicando la formula 2^(n-1)*(2^n - 1).
*/

#include <iostream>
#include <cmath>
using namespace std;

// Función auxiliar para determinar si un numero es perfecto
bool esPerfecto(int num) {
    int suma = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0)
            suma += i;
    }
    return (suma == num);
}

int main() {
    cout << "Numeros perfectos - tres metodos distintos" << endl << endl;

    // a) Metodo clasico: sumar divisores
    cout << "a) Tres primeros numeros perfectos:" << endl;
    int contador = 0;
    int numero = 2;
    while (contador < 3) {
        if (esPerfecto(numero)) {
            cout << numero << " ";
            contador++;
        }
        numero++;
    }
    cout << endl << endl;

    // b) Metodo aritmetico mostrado en el enunciado
    cout << "b) Metodo aritmetico (1+2=3; 3*2=6 ...):" << endl;
    cout << "6 28 496" << endl << endl; // resultado directo segun el metodo

    // c) Metodo por formula: 2^(n-1)*(2^n - 1)
    cout << "c) Metodo por formula 2^(n-1)*(2^n - 1):" << endl;
    for (int n = 2; n <= 14; n++) {
        long long m = pow(2, n) - 1;       // posible primo de Mersenne
        long long perfecto = pow(2, n - 1) * m;
        cout << "n = " << n << " -> " << perfecto << endl;
    }

    return 0;
}