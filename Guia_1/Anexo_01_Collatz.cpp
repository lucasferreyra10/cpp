/*
Id.Programa: Anexo_01_Collatz.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Se aplica la Conjetura de Collatz a un valor entero positivo.
             Reglas:
             #1 - Si es impar -> n = 3 * n + 1
             #2 - Si es par  -> n = n / 2
             El proceso finaliza al llegar al valor 1.
*/

#include <iostream>
using namespace std;

// Funcion que aplica la conjetura de Collatz sobre un numero positivo
void Collatz(int n) {
    int pasos = 0;
    cout << "Secuencia de Collatz para " << n << ":" << endl;

    while (n != 1) {
        cout << n << " -> ";
        if (n % 2 == 0)
            n = n / 2;        // Regla #2
        else
            n = 3 * n + 1;    // Regla #1
        pasos++;
    }

    cout << "1" << endl;
    cout << "Cantidad de pasos: " << pasos << endl;
}

int main() {
    int n;
    cout << "Conjetura de Collatz" << endl;
    cout << "Ingrese un valor entero positivo: ";
    cin >> n;

    if (n <= 0) {
        cout << "El valor debe ser mayor que cero." << endl;
        return 1;
    }

    Collatz(n);

    cout << "\nObservacion:" << endl;
    cout << "- Si a 1 se le vuelven a aplicar las reglas, se repite la secuencia 1 -> 4 -> 2 -> 1." << endl;
    cout << "- Para todos los valores enteros positivos probados hasta hoy, siempre se alcanza el valor 1." << endl;
    cout << "- Aunque no se ha demostrado matematicamente, se cree que es cierta para todo n > 0." << endl;
    cout << "- Aplicaciones: se estudia en teoria de numeros, algoritmos y comportamiento caotico." << endl;

    return 0;
}