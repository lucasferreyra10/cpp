/*
Id.Programa: G3Ej08.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Simula Bingo (1..90) con dos jugadores. Se generan cartones de 15
    numeros únicos para cada jugador y se sortean bolillas sin reposición
    hasta que un jugador completa su cartón. Informa ganador y secuencia.
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;

vector<int> barajar_1_a_90() {
    vector<int> v(90);
    iota(v.begin(), v.end(), 1);
    unsigned seed = (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count();
    shuffle(v.begin(), v.end(), default_random_engine(seed));
    return v;
}

set<int> generar_carton(const vector<int>& numeros_barajados, int offset) {
    set<int> s;
    for (int i = 0; i < 15; ++i) s.insert(numeros_barajados[offset + i]);
    return s;
}

void mostrar_set(const set<int>& s, const string& nombre) {
    cout << nombre << " { ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it;
        if (next(it) != s.end()) cout << ", ";
    }
    cout << " }" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== BINGO (2 jugadores) ===\n";
    auto base = barajar_1_a_90();
    set<int> carton1 = generar_carton(base, 0);
    set<int> carton2 = generar_carton(base, 15);

    mostrar_set(carton1, "Carton J1:");
    mostrar_set(carton2, "Carton J2:");

    vector<int> bolillero = base; // todo barajado
    set<int> cantados;
    int ganador = 0; // 0 nadie, 1 j1, 2 j2, 3 empate
    vector<int> secuencia;

    for(int b : bolillero){
        secuencia.push_back(b);
        cantados.insert(b);

        bool j1_ok = includes(cantados.begin(), cantados.end(), carton1.begin(), carton1.end());
        bool j2_ok = includes(cantados.begin(), cantados.end(), carton2.begin(), carton2.end());

        if(j1_ok && j2_ok){ ganador = 3; break; }
        if(j1_ok){ ganador = 1; break; }
        if(j2_ok){ ganador = 2; break; }
    }

    cout << "\nSecuencia de bolillas cantadas (" << secuencia.size() << "): ";
    for(size_t i=0;i<secuencia.size();++i){
        cout << secuencia[i] << (i+1<secuencia.size()? ", ":"\n");
    }

    if(ganador==1) cout << "\nGANADOR: Jugador 1 (completo su carton)\n";
    else if(ganador==2) cout << "\nGANADOR: Jugador 2 (completo su carton)\n";
    else if(ganador==3) cout << "\nEMPATE: ambos completaron con la misma bolilla\n";
    else cout << "\nSin ganador\n";

    return 0;
}
