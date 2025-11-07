/*
Id.Programa: G1Ej18.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Crear una funcion que recibe dos valores enteros y retorna su M.C.D.
             Estrategia: algoritmo de Euclides (division sucesiva por resto).
*/

#include <iostream>
using namespace std;

// Funcion que calcula el M.C.D. usando el metodo de Euclides
int MCD(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int main() {
    int num1, num2;

    cout << "Calculo del M.C.D. (Metodo de Euclides)" << endl;
    cout << "Ingrese el primer numero entero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero entero: ";
    cin >> num2;

    int resultado = MCD(num1, num2);

    cout << "El M.C.D. de " << num1 << " y " << num2 << " es: " << resultado << endl;

    return 0;
}