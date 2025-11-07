/*
Id.Programa: G1Ej08.cpp
Autor......: Lic. Hugo Cuello
Fecha......: julio-2013
Comentario.: Dado un valor entero n > 0, generar la sumatoria
             desde 1 hasta n.
*/

#include <iostream>
using namespace std;

int main() {
    int n, i;
    long sum = 0;

    cout << "Hallar la sumatoria desde 1 hasta n" << endl;

    // Validar que n sea mayor que 0
    do {
        cout << "Entero n: ";
        cin >> n;

        if (n <= 0)
            cout << "Error: n debe ser un numero entero mayor que 0." << endl;

    } while (n <= 0);

    // Calcular la sumatoria
    for (i = 1; i <= n; i++)
        sum += i;

    cout << "Sumatoria desde 1 hasta " << n << " = " << sum << endl;

    return 0;
}
