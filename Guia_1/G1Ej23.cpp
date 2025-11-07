/*
Id.Programa: G1Ej23.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dado un valor entero n y n ternas de valores enteros, 
             emitir cada terna en forma ordenada decreciente.
             Al finalizar, emitir el menor y el mayor valor de todas las ternas.
*/

#include <iostream>
using namespace std;

// Ordena tres valores en forma decreciente (de mayor a menor)
void OrdenarDesc(int &a, int &b, int &c) {
    int aux;
    if (a < b) { aux = a; a = b; b = aux; }
    if (a < c) { aux = a; a = c; c = aux; }
    if (b < c) { aux = b; b = c; c = aux; }
}

int main() {
    int n;
    cout << "Ordenamiento de ternas de numeros enteros en forma decreciente" << endl;

    cout << "Ingrese la cantidad de ternas: ";
    cin >> n;

    int a, b, c;
    int menorGlobal, mayorGlobal;

    // Inicializacion de los extremos
    bool primera = true;

    for (int i = 1; i <= n; i++) {
        cout << "\nTerna #" << i << endl;
        cout << "Ingrese el primer valor: ";
        cin >> a;
        cout << "Ingrese el segundo valor: ";
        cin >> b;
        cout << "Ingrese el tercer valor: ";
        cin >> c;

        // Ordenar la terna
        OrdenarDesc(a, b, c);

        cout << "Terna ordenada (decreciente): " << a << "  " << b << "  " << c << endl;

        // Actualizar minimo y maximo global
        if (primera) {
            menorGlobal = c; // el menor esta en c tras el ordenamiento
            mayorGlobal = a; // el mayor esta en a
            primera = false;
        } else {
            if (c < menorGlobal) menorGlobal = c;
            if (a > mayorGlobal) mayorGlobal = a;
        }
    }

    cout << "\n---- RESULTADOS FINALES ----" << endl;
    cout << "Menor valor de todas las ternas: " << menorGlobal << endl;
    cout << "Mayor valor de todas las ternas: " << mayorGlobal << endl;

    return 0;
}