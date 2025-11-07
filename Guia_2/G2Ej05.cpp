/*
Id.Programa: G2Ej05.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Crear la funcion void CmbCar(char* cad, char car1, char car2)
             que reemplaza cada aparicion del caracter car1 en la cadena cad
             por el caracter car2.
*/

#include <iostream>
#include <cstring>
using namespace std;

// Funcion que reemplaza cada aparicion de car1 por car2
void CmbCar(char* cad, char car1, char car2) {
    int len = strlen(cad);

    for (int i = 0; i < len; i++) {
        if (cad[i] == car1)
            cad[i] = car2;
    }
}

int main() {
    const int N = 100;
    char cadena[N + 1];
    char origen, reemplazo;

    cout << "Funcion CmbCar - Reemplazo de caracteres en una cadena" << endl;
    cout << "Ingrese una cadena: ";
    cin.getline(cadena, N + 1);

    cout << "Ingrese el caracter a reemplazar: ";
    cin >> origen;

    cout << "Ingrese el caracter de reemplazo: ";
    cin >> reemplazo;

    CmbCar(cadena, origen, reemplazo);

    cout << "Cadena modificada: " << cadena << endl;
    return 0;
}