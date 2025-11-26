/*
Id.Programa: G5Ej12.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Convierte una expresión en notación infija a notación postfija
    utilizando una pila enlazada para operadores.
*/

#include <iostream>
#include <cstring>
using namespace std;

struct Nodo {
    char dato;
    Nodo *sig;
};

//------------------------------------------------------------------
// Operaciones de pila
//------------------------------------------------------------------
void push(Nodo *&pila, char x) {
    Nodo *nuevo = new Nodo;
    nuevo->dato = x;
    nuevo->sig = pila;
    pila = nuevo;
}

char pop(Nodo *&pila) {
    if (!pila) return '\0';
    char x = pila->dato;
    Nodo *aux = pila;
    pila = aux->sig;
    delete aux;
    return x;
}

char tope(Nodo *pila) {
    return pila ? pila->dato : '\0';
}

bool vacia(Nodo *pila) {
    return pila == nullptr;
}

//------------------------------------------------------------------
// Prioridad de operadores
//------------------------------------------------------------------
int prioridad(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

//------------------------------------------------------------------
// Conversión infija → postfija
//------------------------------------------------------------------
void infijaAPostfija(const char infija[], char postfija[]) {
    Nodo *pila = nullptr;
    int j = 0;

    for (int i = 0; infija[i] != '\0'; i++) {
        char c = infija[i];

        if (isalnum(c)) { 
            postfija[j++] = c;
        }
        else if (c == '(') {
            push(pila, c);
        }
        else if (c == ')') {
            while (!vacia(pila) && tope(pila) != '(') {
                postfija[j++] = pop(pila);
            }
            pop(pila);
        }
        else { 
            while (!vacia(pila) && prioridad(tope(pila)) >= prioridad(c)) {
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

//------------------------------------------------------------------
// Programa principal
//------------------------------------------------------------------
int main() {
    char infija[100], postfija[100];

    cout << "Ingrese expresion en notacion infija: ";
    cin >> infija;

    infijaAPostfija(infija, postfija);

    cout << "Expresion postfija: " << postfija << endl;

    return 0;
}
