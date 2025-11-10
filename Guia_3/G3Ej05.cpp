/*
Id.Programa: G3Ej05.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Implementa la Criba de Eratóstenes utilizando conjuntos.
    Se inicializa un conjunto Criba_Eratostenes con los valores
    consecutivos del 2 al 100.
    Luego se eliminan todos los múltiplos de cada número primo
    encontrado, quedando finalmente los números primos entre 2 y 100.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> Criba_Eratostenes;

    // 1. Inicializar el conjunto con valores de 2 a 100
    for (int i = 2; i <= 100; ++i)
        Criba_Eratostenes.insert(i);

    // 2. Aplicar la criba
    for (int p = 2; p * p <= 100; ++p) {
        if (Criba_Eratostenes.find(p) != Criba_Eratostenes.end()) {
            // Eliminar múltiplos de p (mayores que p)
            for (int mult = p * p; mult <= 100; mult += p) {
                Criba_Eratostenes.erase(mult);
            }
        }
    }

    // 3. Mostrar resultado
    cout << "=== CRIBA DE ERATOSTENES ===\n";
    cout << "Numeros primos entre 2 y 100:\n{ ";

    for (auto it = Criba_Eratostenes.begin(); it != Criba_Eratostenes.end(); ++it) {
        cout << *it;
        if (next(it) != Criba_Eratostenes.end()) cout << ", ";
    }
    cout << " }\n";

    cout << "\nCantidad de numeros primos encontrados: " 
         << Criba_Eratostenes.size() << "\n";

    return 0;
}