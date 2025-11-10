
/*
Id.Programa: G2Ej09Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Dos vectores p y q (sin repetir, valores 1..90). Ordenarlos y menu:
             a) Union, b) Interseccion, c) Diferencia p-q, d) Dif. simetrica, e) Complemento de p+q.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

void imprimir(const vector<int>& v, const string& nombre) {
    cout << nombre << " (" << v.size() << "): ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    int m, n;
    cout << "Vectores p y q en [1,90] sin repetir\n";
    cout << "Ingrese m (tam de p, 0..90): "; cin >> m;
    cout << "Ingrese n (tam de q, 0..90): "; cin >> n;
    if (m < 0 || m > 90 || n < 0 || n > 90) { cout << "Tamanos invalidos.\n"; return 0; }

    // generar p y q aleatorios sin repetir
    random_device rd; mt19937 gen(rd());
    vector<int> universo(90); for (int i = 0; i < 90; ++i) universo[i] = i+1;
    shuffle(universo.begin(), universo.end(), gen);
    vector<int> p(universo.begin(), universo.begin()+m);
    shuffle(universo.begin(), universo.end(), gen);
    vector<int> q(universo.begin(), universo.begin()+n);

    sort(p.begin(), p.end());
    sort(q.begin(), q.end());

    imprimir(p, "p");
    imprimir(q, "q");

    int op;
    do {
        cout << "\nMENU\n";
        cout << "1) Union\n";
        cout << "2) Interseccion\n";
        cout << "3) Diferencia p - q\n";
        cout << "4) Diferencia simetrica\n";
        cout << "5) Complemento de p+q (en 1..90)\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> op;
        vector<int> r;
        if (op == 1) {
            set_union(p.begin(), p.end(), q.begin(), q.end(), back_inserter(r));
            imprimir(r, "Union r");
        } else if (op == 2) {
            set_intersection(p.begin(), p.end(), q.begin(), q.end(), back_inserter(r));
            imprimir(r, "Interseccion r");
        } else if (op == 3) {
            set_difference(p.begin(), p.end(), q.begin(), q.end(), back_inserter(r));
            imprimir(r, "Diferencia r = p-q");
        } else if (op == 4) {
            set_symmetric_difference(p.begin(), p.end(), q.begin(), q.end(), back_inserter(r));
            imprimir(r, "Dif. simetrica r");
        } else if (op == 5) {
            vector<int> uni; uni.reserve(p.size()+q.size());
            set_union(p.begin(), p.end(), q.begin(), q.end(), back_inserter(uni));
            vector<int> U(90); for (int i=0;i<90;++i) U[i]=i+1;
            set_difference(U.begin(), U.end(), uni.begin(), uni.end(), back_inserter(r));
            imprimir(r, "Complemento r");
        } else if (op != 0) {
            cout << "Opcion invalida\n";
        }
    } while (op != 0);

    return 0;
}
