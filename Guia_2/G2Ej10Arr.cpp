
/*
Id.Programa: G2Ej10Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Generar dos vectores p y q (m y n elementos, max 90 cada uno) con enteros al azar,
             ordenarlos creciente e intercalarlos en r (merge). Emitir los tres.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

void imprimir(const vector<int>& v, const string& nombre) {
    cout << nombre << " (" << v.size() << "): ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    int m, n;
    cout << "Intercalar dos vectores ordenados\n";
    cout << "m (0..90): "; cin >> m;
    cout << "n (0..90): "; cin >> n;
    if (m<0||m>90||n<0||n>90) { cout << "Tamanos invalidos\n"; return 0; }

    random_device rd; mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 999);

    vector<int> p(m), q(n);
    for (int i = 0; i < m; ++i) p[i] = dist(gen);
    for (int j = 0; j < n; ++j) q[j] = dist(gen);

    sort(p.begin(), p.end());
    sort(q.begin(), q.end());

    vector<int> r;
    r.reserve(m+n);
    merge(p.begin(), p.end(), q.begin(), q.end(), back_inserter(r));

    imprimir(p, "p");
    imprimir(q, "q");
    imprimir(r, "r = merge(p,q)");

    return 0;
}
