/*
Id.Programa: G1Ej01.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dados los catetos a y b, ambos reales y positivos, de un triángulo
             rectángulo, se solicita hallar la medida de su hipotenusa.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c;

    cout << "Calculo de la hipotenusa de un triangulo rectangulo" << endl;
    cout << "Ingrese el cateto a: ";
    cin >> a;
    cout << "Ingrese el cateto b: ";
    cin >> b;

    if (a <= 0 || b <= 0) {
        cout << "Error: ambos catetos deben ser valores positivos." << endl;
        return 1;
    }

    c = sqrt(a * a + b * b);

    cout << "La hipotenusa del triangulo es: " << c << endl;

    return 0;
}
