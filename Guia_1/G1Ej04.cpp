/*
Id.Programa: G1Ej04.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Leer catetos de triangulos rectangulos y calcular su hipotenusa
             hasta que se ingrese un valor <= 0. Al finalizar, informar:
             - cantidad total de triangulos
             - cantidades y porcentajes con hipotenusa > 100 y <= 100
             - promedio de las hipotenusas
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a, b, c;
    int total = 0;
    int cont_mas_100 = 0;
    int cont_men_igual_100 = 0;
    double suma_hip = 0.0;

    cout << "Calculo de hipotenusas (finaliza si ingresas un cateto <= 0)" << endl;

    while (true) {
        cout << "Cateto a: ";
        cin >> a;
        if (a <= 0) break;

        cout << "Cateto b: ";
        cin >> b;
        if (b <= 0) break;

        c = hypot(a, b);

        ++total;
        suma_hip += c;

        if (c > 100.0) ++cont_mas_100;
        else           ++cont_men_igual_100;

        cout << "Hipotenusa: " << fixed << setprecision(2) << c << endl;
    }

    cout << "\n---- Resumen ----" << endl;

    if (total == 0) {
        cout << "No se ingresaron triangulos validos." << endl;
        return 0;
    }

    double pct_mas_100 = 100.0 * cont_mas_100 / total;
    double pct_men_igual_100 = 100.0 * cont_men_igual_100 / total;
    double promedio = suma_hip / total;

    cout << "Cantidad de triangulos: " << total << endl;
    cout << "Hipotenusa > 100: " << cont_mas_100
         << " (" << fixed << setprecision(2) << pct_mas_100 << "%)" << endl;
    cout << "Hipotenusa <= 100: " << cont_men_igual_100
         << " (" << fixed << setprecision(2) << pct_men_igual_100 << "%)" << endl;
    cout << "Promedio de hipotenusas: " << fixed << setprecision(2) << promedio << endl;

    return 0;
}
