/*
Id.Programa: G1Ej05.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dados dos valores a y b, enteros positivos (incluido el cero),
             hallar la potencia de a^b. 
             Si a = 0 entonces b > 0; si b = 0 entonces a > 0.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b;
    long long resultado = 1;

    cout << "Calculo de la potencia a^b" << endl;

    do {
        cout << "Ingrese a (entero >= 0): ";
        cin >> a;
        cout << "Ingrese b (entero >= 0): ";
        cin >> b;

        if ((a == 0 && b == 0) || (a < 0 || b < 0))
            cout << "Error: los valores no cumplen las condiciones." << endl;

    } while ((a == 0 && b == 0) || (a < 0 || b < 0));

    // Calculo iterativo de la potencia
    for (int i = 1; i <= b; i++) {
        resultado *= a;
    }

    cout << a << " ^ " << b << " = " << resultado << endl;

    return 0;
}
