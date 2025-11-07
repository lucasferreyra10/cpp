/*
Id.Programa: G1Ej11.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dado un valor n, entero positivo, obtener la sumatoria de la
             sucesion de Fibonacci hasta encontrar un valor mayor a n.
*/

#include <iostream>
using namespace std;

int main() {
    long long n;
    cout << "Calculo de la sumatoria de Fibonacci hasta superar n" << endl;

    // Validacion de entrada
    do {
        cout << "Ingrese n (entero > 0): ";
        cin >> n;
        if (n <= 0) cout << "Error: n debe ser un entero positivo." << endl;
    } while (n <= 0);

    long long a = 0, b = 1, c = 0;
    long long suma = a + b;

    cout << "Sucesion: " << a << " " << b << " ";

    // Generar y acumular terminos hasta que se supere n
    while (true) {
        c = a + b;
        if (c > n) break;  // detener al superar n
        cout << c << " ";
        suma += c;
        a = b;
        b = c;
    }

    cout << endl;
    cout << "Sumatoria de los terminos de Fibonacci <= " << n << " = " << suma << endl;

    return 0;
}