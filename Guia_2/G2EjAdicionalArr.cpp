/*
Id.Programa: G2EjAdicionalArr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Normalizacion de un vector: convertirlo a longitud (modulo) 1
             sin cambiar su direccion. El vector normalizado mantiene la
             direccion original pero con modulo igual a 1.
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const int N = 3;
    float v[N];
    float modulo = 0, normalizado[N];

    cout << "Normalizacion de un vector de 3 componentes" << endl;

    // Ingreso del vector
    for (int i = 0; i < N; i++) {
        cout << "Ingrese componente " << i + 1 << ": ";
        cin >> v[i];
        modulo += pow(v[i], 2);
    }

    // Calculo del modulo
    modulo = sqrt(modulo);

    if (modulo == 0) {
        cout << "No se puede normalizar un vector nulo (modulo 0)." << endl;
        return 0;
    }

    // Normalizacion
    for (int i = 0; i < N; i++) {
        normalizado[i] = v[i] / modulo;
    }

    // Salida
    cout << fixed << setprecision(3);
    cout << "\nModulo del vector: " << modulo << endl;
    cout << "Vector normalizado:\n";
    for (int i = 0; i < N; i++) {
        cout << "  [" << i + 1 << "] = " << normalizado[i] << endl;
    }

    return 0;
}
