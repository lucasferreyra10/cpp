
/*
Id.Programa: G2Ej08Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Generar vector N con enteros en [1,90].
             Caso 1: con reposicion (puede repetir).
             Caso 2: sin reposicion (no repite) -> N <= 90.
*/

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cout << "Generar vector aleatorio en [1,90]\n";
    cout << "Ingrese N: ";
    cin >> N;

    cout << "Elegir caso:\n";
    cout << "1) Con reposicion (puede repetir)\n";
    cout << "2) Sin reposicion (no repite)\n";
    int caso;
    cin >> caso;

    int v[100]; // Tamaño fijo suficiente para el problema
    mt19937 gen(static_cast<unsigned>(
        chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 90);

    if (caso == 1)
    {
        for (int i = 0; i < N; ++i)
            v[i] = dist(gen);
    }
    else
    {
        if (N > 90)
        {
            cout << "Error: para sin reposicion N debe ser <= 90.\n";
            return 0;
        }
        int bolsa[90];
        for (int i = 0; i < 90; ++i)
            bolsa[i] = i + 1;
        shuffle(bolsa, bolsa + 90, gen);
        for (int i = 0; i < N; ++i)
            v[i] = bolsa[i];
    }

    cout << "Vector generado:\n";
    for (int i = 0; i < N; ++i)
        cout << v[i] << " ";
    cout << "\n";
    return 0;
}
