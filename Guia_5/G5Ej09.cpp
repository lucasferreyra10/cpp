/*
Id.Programa: G5Ej09.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Dada una pila con elementos enteros generada aleatoriamente,
    ordenarla en forma creciente usando otra pila auxiliar.
    - Genera N elementos aleatorios (rango configurable).
    - Muestra la pila original (top a base), la pila ordenada (top a base)
      y finalmente emite los elementos en orden creciente.
    Técnica: uso exclusivo de pilas (std::stack<int>) para la ordenación.
*/

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void imprimirPila(stack<int> s, const string &titulo) {
    cout << titulo << " (tope -> base): ";
    if (s.empty()) {
        cout << "<vacia>\n";
        return;
    }
    bool primero = true;
    while (!s.empty()) {
        if (!primero) cout << " ";
        cout << s.top();
        s.pop();
        primero = false;
    }
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int N;
    const int MINVAL = -99;
    const int MAXVAL = 999;

    cout << "Cantidad de elementos a generar en la pila: ";
    if (!(cin >> N) || N <= 0) {
        cout << "Valor invalido. Usando N = 10 por defecto.\n";
        N = 10;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    stack<int> orig;

    // Generar pila con N valores aleatorios (empujados en el orden de llegada)
    for (int i = 0; i < N; ++i) {
        int v = MINVAL + (rand() % (MAXVAL - MINVAL + 1));
        orig.push(v);
    }

    // Mostrar pila original (top->base)
    imprimirPila(orig, "Pila original");

    // Algoritmo de ordenación usando otra pila auxiliar
    stack<int> aux;

    while (!orig.empty()) {
        int x = orig.top();
        orig.pop();

        // mover desde aux de vuelta a orig mientras el tope de aux sea mayor que x
        while (!aux.empty() && aux.top() > x) {
            orig.push(aux.top());
            aux.pop();
        }

        // colocar x en aux
        aux.push(x);
    }

    // Ahora aux tiene los elementos ordenados con el mayor en la cima (top)
    imprimirPila(aux, "Pila ordenada (mayor en tope)");

    // Para emitir en orden creciente: pasar de aux -> orig (inversión)
    while (!aux.empty()) {
        orig.push(aux.top());
        aux.pop();
    }

    // Finalmente imprimimos orig: ahora su tope es el menor -> muestra creciente al desapilar
    cout << "Elementos en ORDEN CRECIENTE:\n";
    while (!orig.empty()) {
        cout << setw(6) << orig.top() << "\n";
        orig.pop();
    }

    return 0;
}
