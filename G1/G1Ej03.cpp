/*
Id.Programa: G1Ej03.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Conociendo sus catetos a y b, hallar la superficie de
             un cuadrado con lado igual a la medida de la hipotenusa
             de un triángulo rectángulo si es > 100, sino el doble
             de su valor.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c, SupCuad;

    cout << "Emitir superficie de un cuadrado con hipotenusa > 100" << endl;
    cout << "o con el doble de su valor si la hipotenusa es <= 100" << endl;

    cout << "Cateto a: ";
    cin >> a;
    cout << "Cateto b: ";
    cin >> b;

    // Calcular hipotenusa
    c = sqrt(a * a + b * b);

    // Calcular superficie del cuadrado según condición
    if (c > 100)
        SupCuad = pow(c, 2);
    else
        SupCuad = pow(2 * c, 2);

    cout << "Superficie del cuadrado = " << SupCuad << " (con hipotenusa = " << c << ")" << endl;

    return 0;
}
