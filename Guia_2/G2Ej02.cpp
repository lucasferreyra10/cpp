/*
Id.Programa: G2Ej02.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Crear la funcion char* FillBlank(char* cad, short n)
             que rellena la cadena con espacios en blanco a la derecha
             hasta alcanzar la longitud fisica n.
*/

#include <iostream>
#include <cstring>
using namespace std;

// Funcion que rellena una cadena con espacios a la derecha
char* FillBlank(char* cad, short n) {
    short len = strlen(cad);

    // Si la cadena es mas larga que n, se trunca
    if (len >= n) {
        cad[n] = '\0';
        return cad;
    }

    // Rellenar con espacios hasta completar n caracteres
    for (int i = len; i < n; i++) {
        cad[i] = ' ';
    }

    cad[n] = '\0'; // terminador nulo
    return cad;
}

int main() {
    const short N = 20; // longitud fisica
    char cadena[N + 1];

    cout << "Funcion FillBlank - Rellenar con espacios a la derecha" << endl;
    cout << "Ingrese una cadena (max 20 caracteres): ";
    cin.getline(cadena, N + 1);

    FillBlank(cadena, N);

    cout << "Cadena rellena: |" << cadena << "|" << endl;
    cout << "Longitud final: " << strlen(cadena) << endl;

    return 0;
}