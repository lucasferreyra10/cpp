/*
Id.Programa: G2Ej04.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Crear la funcion char* InvCad(char* cad) que invierte una cadena
             dentro del mismo arreglo y retorna el puntero a la cadena invertida.
*/

#include <iostream>
#include <cstring>
using namespace std;

// Funcion que invierte una cadena
char* InvCad(char* cad) {
    int len = strlen(cad);
    for (int i = 0; i < len / 2; i++) {
        char aux = cad[i];
        cad[i] = cad[len - 1 - i];
        cad[len - 1 - i] = aux;
    }
    return cad;
}

int main() {
    const int N = 50;
    char cadena[N + 1];

    cout << "Funcion InvCad - Inversion de cadena" << endl;
    cout << "Ingrese una cadena: ";
    cin.getline(cadena, N + 1);

    InvCad(cadena);

    cout << "Cadena invertida: " << cadena << endl;
    return 0;
}