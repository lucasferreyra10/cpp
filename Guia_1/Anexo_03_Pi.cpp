/*
Id.Programa: Anexo_03_Pi.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dado un valor entero n, se aproxima el valor de la constante irracional pi
             utilizando la serie de Leibniz:
             pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - ... + (-1)^i / (2*i + 1))
             Cuantos mas terminos se utilicen (n grande), mayor sera la precision.
*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Calcula la aproximacion de pi usando n terminos de la serie de Leibniz
double AproximarPi(int n) {
    double suma = 0.0;

    for (int i = 0; i < n; i++) {
        double termino = pow(-1, i) / (2.0 * i + 1.0);
        suma += termino;
    }

    return 4.0 * suma;
}

int main() {
    int n;
    cout << "Aproximacion de la constante PI mediante la serie de Leibniz" << endl;
    cout << "Ingrese la cantidad de terminos a calcular (entero positivo): ";
    cin >> n;

    if (n <= 0) {
        cout << "El valor debe ser mayor que cero." << endl;
        return 1;
    }

    double piAprox = AproximarPi(n);

    cout << fixed << setprecision(10);
    cout << "\nAproximacion de pi con " << n << " terminos = " << piAprox << endl;
    cout << "Valor real de pi (M_PI) = " << M_PI << endl;
    cout << "Error absoluto = " << fabs(M_PI - piAprox) << endl;

    cout << "\nObservacion:" << endl;
    cout << "- El metodo de Leibniz converge lentamente; se requieren muchos terminos para gran precision." << endl;
    cout << "- Otros metodos mas eficientes: Nilakantha, Monte Carlo o Gauss-Legendre." << endl;

    return 0;
}