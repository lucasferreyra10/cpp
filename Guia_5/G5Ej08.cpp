/*
Id.Programa: G5Ej08.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Programa que permite cargar términos de dos polinomios,
    sumarlos y listarlos mediante un menú.
    Cada polinomio se representa como una lista enlazada de términos
    (coeficiente y exponente).
*/

#include <iostream>
using namespace std;

struct Nodo {
    float coef;
    int exp;
    Nodo* sig;
};

void insertarTermino(Nodo*& poly, float coef, int exp) {
    Nodo* nuevo = new Nodo();
    nuevo->coef = coef;
    nuevo->exp = exp;
    nuevo->sig = nullptr;

    if (!poly || exp > poly->exp) {
        nuevo->sig = poly;
        poly = nuevo;
        return;
    }

    Nodo* act = poly;
    Nodo* ant = nullptr;

    while (act && act->exp > exp) {
        ant = act;
        act = act->sig;
    }

    if (act && act->exp == exp) {
        act->coef += coef;
        delete nuevo;
    } else {
        nuevo->sig = act;
        ant->sig = nuevo;
    }
}

void listarPolinomio(Nodo* poly) {
    if (!poly) {
        cout << "   <vacio>\n";
        return;
    }

    Nodo* p = poly;
    bool primero = true;

    while (p) {
        if (!primero && p->coef >= 0) cout << " + ";
        cout << p->coef << "x^" << p->exp;
        primero = false;
        p = p->sig;
    }
    cout << "\n";
}

Nodo* sumar(Nodo* p1, Nodo* p2) {
    Nodo* resultado = nullptr;

    while (p1) {
        insertarTermino(resultado, p1->coef, p1->exp);
        p1 = p1->sig;
    }
    while (p2) {
        insertarTermino(resultado, p2->coef, p2->exp);
        p2 = p2->sig;
    }

    return resultado;
}

int main() {
    Nodo* pol1 = nullptr;
    Nodo* pol2 = nullptr;
    Nodo* suma = nullptr;

    int opcion;
    float coef;
    int exp;

    do {
        cout << "----------------------------------\n";
        cout << " MENU - POLINOMIOS\n";
        cout << "1. Agregar termino al Polinomio 1\n";
        cout << "2. Agregar termino al Polinomio 2\n";
        cout << "3. Sumar Polinomios\n";
        cout << "4. Listar Polinomios\n";
        cout << "0. Salir\n";
        cout << "----------------------------------\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Coeficiente: "; cin >> coef;
            cout << "Exponente: "; cin >> exp;
            insertarTermino(pol1, coef, exp);
            break;

        case 2:
            cout << "Coeficiente: "; cin >> coef;
            cout << "Exponente: "; cin >> exp;
            insertarTermino(pol2, coef, exp);
            break;

        case 3:
            suma = sumar(pol1, pol2);
            cout << "Polinomios sumados correctamente.\n";
            break;

        case 4:
            cout << "Polinomio 1: ";
            listarPolinomio(pol1);
            cout << "Polinomio 2: ";
            listarPolinomio(pol2);
            cout << "Suma: ";
            listarPolinomio(suma);
            break;
        }

    } while (opcion != 0);

    return 0;
}
