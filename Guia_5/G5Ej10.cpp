/*
Id.Programa: G5Ej10.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Dada una cola con elementos enteros generada en forma aleatoria,
    ordenar la cola en forma creciente utilizando SOLO OTRA COLA
    como estructura auxiliar (no usar vectores ni pilas).

    Estrategia:
      - Algoritmo tipo "selection" adaptado a colas:
        Repetir hasta vaciar la cola original:
          1) Recorrer toda la cola original pasándola a una cola AUX y
             buscando el valor mínimo.
          2) Recorrer AUX devolviendo todos los elementos a la cola original,
             excepto la primera ocurrencia del mínimo, que se encolará en la
             cola ORDENADA.
      - Repetir el proceso hasta vaciar la cola original; la cola ORDENADA
        contendrá los elementos en orden creciente (frente -> fin).
      - El programa genera la cola original con N valores aleatorios,
        muestra la cola original, ejecuta el ordenamiento y muestra la cola
        ordenada (frente -> fin).

    Nota:
      - Las operaciones de encolar/desencolar están implementadas con
        listas enlazadas (Nodo) en estilo procedural, al estilo de la guía.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Nodo {
    int info;
    Nodo* sig;
};

// Operaciones de cola con punteros (frente y fin)
void encolar(Nodo*& frente, Nodo*& fin, int x) {
    Nodo* p = new Nodo();
    p->info = x;
    p->sig = nullptr;
    if (frente == nullptr) {
        frente = p;
    } else {
        fin->sig = p;
    }
    fin = p;
}

int desencolar(Nodo*& frente, Nodo*& fin) {
    if (frente == nullptr) return 0; // no usado si se chequea antes
    Nodo* p = frente;
    int val = p->info;
    frente = frente->sig;
    if (frente == nullptr) fin = nullptr;
    delete p;
    return val;
}

bool vacia(Nodo* frente) {
    return (frente == nullptr);
}

void imprimirCola(Nodo* frente) {
    if (frente == nullptr) {
        cout << "<vacia>\n";
        return;
    }
    Nodo* p = frente;
    bool primero = true;
    while (p) {
        if (!primero) cout << " ";
        cout << p->info;
        primero = false;
        p = p->sig;
    }
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Nodo* Q = nullptr;   // frente de la cola original
    Nodo* FQ = nullptr;  // fin de la cola original

    Nodo* AUX = nullptr; // frente auxiliar
    Nodo* FAUX = nullptr; // fin auxiliar

    Nodo* ORD = nullptr; // cola ordenada (frente)
    Nodo* FORD = nullptr; // fin cola ordenada

    int N;
    cout << "Cantidad de elementos a generar en la cola: ";
    if (!(cin >> N) || N <= 0) {
        cout << "Valor invalido. Se usara N = 10 por defecto.\n";
        N = 10;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    const int MINVAL = -99;
    const int MAXVAL = 999;

    // Generar N valores aleatorios y encolarlos en Q
    for (int i = 0; i < N; ++i) {
        int v = MINVAL + (rand() % (MAXVAL - MINVAL + 1));
        encolar(Q, FQ, v);
    }

    cout << "\nCola original (frente -> fin): ";
    imprimirCola(Q);

    // --- Ordenamiento usando SOLO otra cola AUX y la cola ORD ---
    // Repetir hasta que Q quede vacia
    while (!vacia(Q)) {
        // 1) Encontrar el minimo recorriendo Q y pasando los elementos a AUX
        int minimo = INT32_MAX;
        while (!vacia(Q)) {
            int x = desencolar(Q, FQ);
            if (x < minimo) minimo = x;
            encolar(AUX, FAUX, x);
        }

        // 2) Recorrer AUX y devolver a Q todos los elementos excepto
        //    la PRIMERA ocurrencia del minimo (esa la pasamos a ORD)
        bool minPasado = false;
        while (!vacia(AUX)) {
            int x = desencolar(AUX, FAUX);
            if (x == minimo && !minPasado) {
                // Enviar el minimo a la cola ordenada (solo una vez)
                encolar(ORD, FORD, x);
                minPasado = true;
            } else {
                // Devolver el resto a Q para la siguiente iteracion
                encolar(Q, FQ, x);
            }
        }
        // En este punto Q contiene los elementos restantes; se repite
    }

    cout << "\nCola ordenada (frente -> fin): ";
    imprimirCola(ORD);

    cout << "\nElementos emitidos en orden creciente (desencolando ORD):\n";
    while (!vacia(ORD)) {
        int val = desencolar(ORD, FORD);
        cout << setw(6) << val << "\n";
    }

    return 0;
}