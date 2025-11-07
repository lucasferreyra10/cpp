/*
Id.Programa: G2Ej03.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Crear la funcion char LowCase(char car) que convierte el caracter dado
             a minuscula si esta en mayuscula, caso contrario retorna el mismo caracter.
*/

#include <iostream>
using namespace std;

// Funcion que convierte un caracter mayuscula a minuscula
char LowCase(char car) {
    if (car >= 'A' && car <= 'Z')
        return car + ('a' - 'A'); // diferencia entre mayuscula y minuscula en ASCII
    else
        return car;
}

int main() {
    char c;
    cout << "Funcion LowCase - Conversion a minuscula" << endl;
    cout << "Ingrese un caracter: ";
    cin >> c;

    char resultado = LowCase(c);

    cout << "Caracter convertido: " << resultado << endl;
    return 0;
}