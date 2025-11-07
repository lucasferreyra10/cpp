/*
Id.Programa: G1Ej13.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Dada una lista de valores enteros y un valor x tambien entero,
             determinar si x esta en la lista e informar su posicion si se encuentra,
             o un mensaje apropiado en caso contrario.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    bool encontrado = false;
    int posicion = -1;

    cout << "Busqueda de un valor x dentro de una lista de enteros" << endl;

    // Ingreso del tamaño de la lista
    do {
        cout << "Ingrese la cantidad de elementos n (entero > 0): ";
        cin >> n;
        if (n <= 0)
            cout << "Error: n debe ser mayor que cero." << endl;
    } while (n <= 0);
    // Declaracion del arreglo dinamico
    int* valores = new int[n];

    // Carga de la lista
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el valor " << i + 1 << ": ";
        cin >> valores[i];
    }

    // Ingreso de x
    cout << "Ingrese el valor x a buscar: ";
    cin >> x;

        // Busqueda lineal de x
        for (int i = 0; i < n; i++) {
            if (valores[i] == x) {
                encontrado = true;
                posicion = i + 1; // posicion 1-indexada
                break;
            }
        }
    
        // Mostrar resultado
        if (encontrado) {
            cout << "El valor " << x << " se encuentra en la posicion " << posicion << endl;
        } else {
            cout << "El valor " << x << " no se encuentra en la lista." << endl;
        }
    
        return 0;
    }
