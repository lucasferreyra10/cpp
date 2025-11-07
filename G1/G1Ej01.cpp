/*
Id.Programa: G1Ej01.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dadas las medidas de los catetos de un triángulo rectángulo,
             hallar la medida de su hipotenusa.
Versión modularizada.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c;

    cout << "Calcular hipotenusa con datos de catetos a y b" << endl;
    cout << "Cateto a: ";
    cin >> a;
    cout << "Cateto b: ";
    cin >> b;

    c = sqrt(a * a + b * b);

    cout << "Hipotenusa: " << c << endl;
    return 0;
}
