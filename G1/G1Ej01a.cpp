/*
Id.Programa: G1Ej01a.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dados las medidas de los 2 catetos de un triángulo
             rectángulo, hallar la medida de su hipotenusa.
             Versión modularizada.
*/

#include <iostream>
#include <cmath>
using namespace std;

// Función para obtener los catetos
void ObtDatos(float &cata, float &catb) {
    cout << "Cálculo de hipotenusa con datos de catetos a y b" << endl;
    cout << "Cateto a: ";
    cin >> cata;
    cout << "Cateto b: ";
    cin >> catb;
}

// Función para calcular la hipotenusa
float CalcHipot(float cata, float catb) {
    return sqrt(pow(cata, 2) + pow(catb, 2));
}

// Función para mostrar el resultado
void EmiteHipot(float hipot) {
    cout << "Hipotenusa: " << hipot << endl;
}

int main() {
    float a, b, c;

    ObtDatos(a, b);
    c = CalcHipot(a, b);
    EmiteHipot(c);

    return 0;
}
