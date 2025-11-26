/*
Id.Programa: G5Ej11.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Dada una expresión en notación INFIIJA, convertirla a
    notación PREFIJA utilizando PILAS (implementadas con
    listas enlazadas). Luego emitir la expresión resultante.

    Estrategia:
      - Invertir la expresión infija.
      - Cambiar parentesis '(' <-> ')'.
      - Convertir la expresión invertida a POSTFIJA usando
        el algoritmo clásico (shunting-yard).
      - Invertir ese resultado → expresión prefija final.
*/

#include <iostream>
#include <cstring>
using namespace std;

// ========== PILA IMPLEMENTADA A MANO ==========
struct Nodo {
    char info;
    Nodo* sig;
};

void push(Nodo*& pila, char x) {
    Nodo* p = new Nodo();
    p->info = x;
    p->sig  = pila;
    pila = p;
}

char pop(Nodo*& pila) {
    if (pila == nullptr) return '\0';
    char x = pila->info;
    Nodo* p = pila;
    pila = pila->sig;
    delete p;
    return x;
}

char tope(Nodo* pila) {
    if (pila == nullptr) return '\0';
    return pila->info;
}

bool vacia(Nodo* pila) {
    return (pila == nullptr);
}

// ========== FUNCIONES AUXILIARES ==========

int prioridad(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool esOperando(char c) {
    return ( (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             (c >= '0' && c <= '9') );
}

// Invierte un string
void invertir(char s[]) {
    int n = strlen(s);
    for (int i = 0; i < n/2; i++) {
        char aux = s[i];
        s[i] = s[n-i-1];
        s[n-i-1] = aux;
    }
}

// Cambiar '(' por ')' y viceversa
void intercambiarParentesis(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
}

// Convierte una expresión infija a postfija
void infijaAPostfija(char infija[], char postfija[]) {
    Nodo* pila = nullptr;
    int j = 0;

    for (int i = 0; infija[i] != '\0'; i++) {
        char c = infija[i];

        if (esOperando(c)) {
            postfija[j++] = c;
        }
        else if (c == '(') {
            push(pila, c);
        }
        else if (c == ')') {
            while (!vacia(pila) && tope(pila) != '(') {
                postfija[j++] = pop(pila);
            }
            pop(pila); // descartar '('
        }
        else { // operador
            while (!vacia(pila) &&
                   prioridad(tope(pila)) >= prioridad(c)) {
                postfija[j++] = pop(pila);
            }
            push(pila, c);
        }
    }

    while (!vacia(pila)) {
        postfija[j++] = pop(pila);
    }

    postfija[j] = '\0';
}

// ========== PROGRAMA PRINCIPAL ==========

int main() {
    char infija[200];
    char invertida[200];
    char postfija[200];
    char prefija[200];

    cout << "Ingrese expresion infija: ";
    cin >> infija;

    // 1) Copiar la infija en invertida
    strcpy(invertida, infija);

    // 2) Invertir string
    invertir(invertida);

    // 3) Cambiar parentesis
    intercambiarParentesis(invertida);

    // 4) Convertir a postfija
    infijaAPostfija(invertida, postfija);

    // 5) La postfija invertida es la prefija
    strcpy(prefija, postfija);
    invertir(prefija);

    cout << "\nExpresion INF IJA : " << infija;
    cout << "\nExpresion PREFIJA : " << prefija << "\n";

    return 0;
}
