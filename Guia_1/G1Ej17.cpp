/*
Id.Programa: G1Ej17.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Crear una funcion que recibe un valor booleano y dos enteros, 
             retornando el primer entero si el booleano es verdadero, 
             o el segundo si es falso.
*/

#include <iostream>
using namespace std;

// Funcion que elige un valor segun el booleano
int Seleccionar(bool condicion, int valor1, int valor2) {
    if (condicion)
        return valor1;
    else
        return valor2;
}

int main() {
    bool condicion;
    int a, b;

    cout << "Funcion que retorna un entero segun un valor booleano" << endl;

    cout << "Ingrese el valor booleano (1 = verdadero, 0 = falso): ";
    cin >> condicion;

    cout << "Ingrese el primer entero: ";
    cin >> a;

    cout << "Ingrese el segundo entero: ";
    cin >> b;

    int resultado = Seleccionar(condicion, a, b);

    cout << "El valor retornado es: " << resultado << endl;

    return 0;
}