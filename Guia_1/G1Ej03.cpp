/*
Id.Programa: G1Ej03.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dados los catetos de un triangulo rectangulo, hallar la superficie
             de un cuadrado cuyo lado sea la hipotenusa si esta es mayor a 100;
             en caso contrario, usar el doble de la hipotenusa.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c, superficie;

    cout << "Calculo de la superficie del cuadrado segun la hipotenusa" << endl;
    cout << "Ingrese el cateto a: ";
    cin >> a;
    cout << "Ingrese el cateto b: ";
    cin >> b;

    if (a <= 0 || b <= 0) {
        cout << "Error: los catetos deben ser positivos." << endl;
        return 1;
    }

    c = sqrt(a * a + b * b); // hipotenusa

    if (c > 100)
        superficie = pow(c, 2);
    else
        superficie = pow(2 * c, 2);

    cout << "Superficie del cuadrado = " << superficie << " (hipotenusa = " << c << ")" << endl;

    return 0;
}
