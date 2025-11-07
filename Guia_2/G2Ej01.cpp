/*
Id.Programa: G2Ej01.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Crear la funcion char* Replicate(char car, short n)
             que retorna una cadena con el caracter dado repetido n veces.
*/

#include <iostream>
#include <cstring>   // para strcpy
using namespace std;

// Funcion que replica un caracter n veces
char* Replicate(char car, short n) {
    if (n <= 0) {
        // retornar cadena vacia
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }

    char* result = new char[n + 1];  // +1 para el terminador nulo
    for (int i = 0; i < n; i++)
        result[i] = car;

    result[n] = '\0';
    return result;
}

int main() {
    char caracter;
    short cantidad;

    cout << "Funcion Replicate - Repite un caracter n veces" << endl;
    cout << "Ingrese un caracter: ";
    cin >> caracter;

    cout << "Ingrese la cantidad de repeticiones: ";
    cin >> cantidad;

    char* cadena = Replicate(caracter, cantidad);

    cout << "Resultado: \"" << cadena << "\"" << endl;

    delete[] cadena; // liberar memoria dinamica
    return 0;
}