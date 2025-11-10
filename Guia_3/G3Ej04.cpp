/*
Id.Programa: G3Ej04.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Se ingresa dos valores enteros: num y den.
    Se generan dos conjuntos: Divisores(num) y Divisores(den).
    Luego se obtiene la intersección entre ambos conjuntos.
    El valor máximo de dicha intersección corresponde al M.C.D.
*/

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// Devuelve el conjunto de divisores positivos de un número
set<int> obtenerDivisores(int n) {
    set<int> divisores;
    n = (n < 0) ? -n : n; // Asegurar que sea positivo
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0)
            divisores.insert(i);
    }
    return divisores;
}

// Muestra un conjunto
void mostrarConjunto(const set<int>& cjto, const string& nombre) {
    cout << nombre << " = { ";
    for (auto it = cjto.begin(); it != cjto.end(); ++it) {
        cout << *it;
        if (next(it) != cjto.end()) cout << ", ";
    }
    cout << " }\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num, den;
    cout << "Ingrese primer valor (num): ";
    cin >> num;
    cout << "Ingrese segundo valor (den): ";
    cin >> den;

    set<int> A = obtenerDivisores(num);
    set<int> B = obtenerDivisores(den);
    set<int> interseccion;

    // Calcular intersección
    set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                     inserter(interseccion, interseccion.begin()));

    // Mostrar conjuntos
    cout << "\n=== DIVISORES ===\n";
    mostrarConjunto(A, "Divisores(" + to_string(num) + ")");
    mostrarConjunto(B, "Divisores(" + to_string(den) + ")");

    cout << "\n=== INTERSECCION ===\n";
    mostrarConjunto(interseccion, "Interseccion");

    // Calcular el M.C.D.
    if (!interseccion.empty()) {
        int mcd = *interseccion.rbegin(); // último (máximo)
        cout << "\nEl M.C.D. de " << num << " y " << den << " es: " << mcd << "\n";
    } else {
        cout << "\nNo hay divisores comunes. El M.C.D. es 1.\n";
    }

    return 0;
}