/*
Id.Programa: G1Ej16.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Leer pares de enteros positivos y emitir su MCD y mcm.
             Bloque 1: entrada; Bloque 2: mcd; Bloque 3: mcm.
*/

#include <iostream>
using namespace std;

// Bloque 2: MCD por Euclides
long long mcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Bloque 3: mcm usando mcd (forma segura)
long long mcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / mcd(a, b)) * b;
}

// Bloque 1: lectura y validacion
bool leerPar(long long &a, long long &b) {
    cout << "Ingrese a (<=0 para terminar): ";
    if (!(cin >> a) || a <= 0) return false;
    cout << "Ingrese b (<=0 para terminar): ";
    if (!(cin >> b) || b <= 0) return false;
    return true;
}

int main() {
    cout << "MCD y mcm (termina con a<=0 o b<=0)" << endl;

    long long a, b;
    while (leerPar(a, b)) {
        long long g = mcd(a, b);
        long long l = mcm(a, b);
        cout << "MCD(" << a << "," << b << ") = " << g << endl;
        cout << "mcm(" << a << "," << b << ") = " << l << endl << endl;
    }

    return 0;
}