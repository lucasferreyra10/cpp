/*
Id.Programa: G3Ej03.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Se ingresan los conjuntos A y B (valores enteros entre 1 y 1000).
    A través de un menú se permite realizar operaciones entre ellos:
    - Unión (U)
    - Intersección (I)
    - Diferencia (D)
    - Diferencia Simétrica (S)
    - Complemento de la Unión (C)
    - Finalizar (F)
    El conjunto universal es U = {1, 2, 3, ..., 1000}.
*/

#include <bits/stdc++.h>
using namespace std;

const int UNIVERSAL_MIN = 1;
const int UNIVERSAL_MAX = 1000;

set<int> ingresarConjunto(char nombre) {
    set<int> cjto;
    int n;
    cout << "Cantidad de elementos del conjunto " << nombre << ": ";
    cin >> n;

    cout << "Ingrese los " << n << " elementos (" << UNIVERSAL_MIN 
         << " a " << UNIVERSAL_MAX << "):\n";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x >= UNIVERSAL_MIN && x <= UNIVERSAL_MAX)
            cjto.insert(x);
        else
            cout << "  Valor fuera de rango, omitido.\n";
    }
    return cjto;
}

set<int> complementoUnion(const set<int>& A, const set<int>& B) {
    set<int> univ, uni, comp;
    for (int i = UNIVERSAL_MIN; i <= UNIVERSAL_MAX; ++i)
        univ.insert(i);
    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(uni, uni.begin()));
    set_difference(univ.begin(), univ.end(), uni.begin(), uni.end(), inserter(comp, comp.begin()));
    return comp;
}

void mostrar(const set<int>& S, string nombre) {
    cout << nombre << " = { ";
    for (auto it = S.begin(); it != S.end(); ++it) {
        cout << *it;
        if (next(it) != S.end()) cout << ", ";
    }
    cout << " }\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> A = ingresarConjunto('A');
    set<int> B = ingresarConjunto('B');

    set<char> Cjto_Opc = {'U','I','D','S','C','F'};
    char op;

    do {
        cout << "\n===== MENU DE OPERACIONES =====\n";
        cout << "U - Union (A ∪ B)\n";
        cout << "I - Interseccion (A ∩ B)\n";
        cout << "D - Diferencia (A - B)\n";
        cout << "S - Diferencia Simetrica (A Δ B)\n";
        cout << "C - Complemento de la union (U - (A ∪ B))\n";
        cout << "F - Finalizar\n";
        cout << "Seleccione una opcion: ";
        cin >> op;
        op = toupper(op);

        if (Cjto_Opc.find(op) == Cjto_Opc.end()) {
            cout << "Opcion invalida.\n";
            continue;
        }

        set<int> resultado;

        switch (op) {
            case 'U':
                set_union(A.begin(), A.end(), B.begin(), B.end(),
                          inserter(resultado, resultado.begin()));
                mostrar(resultado, "A ∪ B");
                break;

            case 'I':
                set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                                 inserter(resultado, resultado.begin()));
                mostrar(resultado, "A ∩ B");
                break;

            case 'D':
                set_difference(A.begin(), A.end(), B.begin(), B.end(),
                               inserter(resultado, resultado.begin()));
                mostrar(resultado, "A - B");
                break;

            case 'S':
                set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(),
                                         inserter(resultado, resultado.begin()));
                mostrar(resultado, "A Δ B");
                break;

            case 'C':
                resultado = complementoUnion(A, B);
                mostrar(resultado, "Complemento de (A ∪ B)");
                break;

            case 'F':
                cout << "Fin del programa.\n";
                break;
        }

    } while (op != 'F');

    return 0;
}