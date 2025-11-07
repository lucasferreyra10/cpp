/*
Id.Programa: Anexo_02_Cuadratica.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dada f(x) = a*x^2 + b*x + c, emitir:
             - Raices: reales iguales, reales distintas o complejas conjugadas
             - Maximo o minimo segun el signo de a
             - Coordenadas del vertice (xv, yv)
             - Si el eje y es simetrico (b=0). Si no, indicar desplazado a izquierda o derecha
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a, b, c;
    cout << "Analisis de funcion cuadratica f(x) = a*x^2 + b*x + c" << endl;

    cout << "Ingrese a: "; cin >> a;
    cout << "Ingrese b: "; cin >> b;
    cout << "Ingrese c: "; cin >> c;

    if (a == 0.0) {
        cout << "No es cuadratica (a=0). Es lineal o constante." << endl;
        return 0;
    }

    cout << fixed << setprecision(4);

    // Discriminante
    double D = b*b - 4.0*a*c;

    // Raices
    cout << "\n-- Raices --" << endl;
    if (D > 0.0) {
        double x1 = (-b + sqrt(D)) / (2.0*a);
        double x2 = (-b - sqrt(D)) / (2.0*a);
        cout << "Reales distintas: x1 = " << x1 << " , x2 = " << x2 << endl;
    } else if (D == 0.0) {
        double x = (-b) / (2.0*a);
        cout << "Reales iguales (doble): x = " << x << endl;
    } else {
        double parteReal = (-b) / (2.0*a);
        double parteImag = sqrt(-D) / (2.0*a);
        cout << "Complejas conjugadas:" << endl;
        cout << "x1 = " << parteReal << " + " << parteImag << "i" << endl;
        cout << "x2 = " << parteReal << " - " << parteImag << "i" << endl;
    }

    // Vertice y naturaleza (maximo/minimo)
    double xv = -b / (2.0*a);
    double yv = a*xv*xv + b*xv + c;

    cout << "\n-- Vertice --" << endl;
    cout << "Vertice (xv, yv) = (" << xv << ", " << yv << ")" << endl;

    cout << "\n-- Maximo / Minimo --" << endl;
    if (a > 0.0)
        cout << "Apertura hacia arriba -> tiene MINIMO en y = " << yv << " (x = " << xv << ")" << endl;
    else
        cout << "Apertura hacia abajo -> tiene MAXIMO en y = " << yv << " (x = " << xv << ")" << endl;

    // Simetria respecto del eje y (b = 0) o desplazamiento del eje de simetria x = -b/(2a)
    cout << "\n-- Eje de simetria --" << endl;
    if (b == 0.0) {
        cout << "Es simetrica respecto del eje y (x = 0)." << endl;
    } else {
        cout << "Eje de simetria: x = " << xv << " -> ";
        if (xv > 0.0) cout << "desplazado a la DERECHA del eje y." << endl;
        else if (xv < 0.0) cout << "desplazado a la IZQUIERDA del eje y." << endl;
        else cout << "coincide con el eje y." << endl; // caso muy cercano a 0 por redondeo
    }

    return 0;
}