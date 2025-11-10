
/*
Id.Programa: G2Ej13Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Bonificacion a camioneros. Se leen viajes (legajo, codPcia 1..24, roturas).
             Listado ordenado por total de roturas. Bonificacion si roturas < 20 y viajes >= 4.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Camionero {
    string legajo;   // 5 car
    int viajes = 0;
    long roturas = 0;
};

int findIndex(vector<Camionero>& v, const string& leg) {
    for (int i = 0; i < (int)v.size(); ++i) if (v[i].legajo == leg) return i;
    return -1;
}

int main() {
    int R;
    cout << "Cantidad de registros de viajes: ";
    cin >> R;
    vector<Camionero> V; V.reserve(100);

    for (int i = 0; i < R; ++i) {
        string leg; int pcia; long rot;
        cout << "Viaje #" << (i+1) << " legajo codPcia roturas: ";
        cin >> leg >> pcia >> rot;
        int idx = findIndex(V, leg);
        if (idx == -1) { V.push_back({leg, 0, 0}); idx = (int)V.size()-1; }
        V[idx].viajes += 1;
        V[idx].roturas += rot;
    }

    sort(V.begin(), V.end(), [](const Camionero& a, const Camionero& b){
        if (a.roturas != b.roturas) return a.roturas < b.roturas;
        return a.legajo < b.legajo;
    });

    cout << "\nListado de Camioneros ordenado por Cant. unid. rotas\n";
    cout << "Nro.Leg  Cant.Viajes  Cant.Unid.Rotas  Bonificacion\n";
    for (auto &c : V) {
        bool bono = (c.viajes >= 4 && c.roturas < 20);
        cout << c.legajo << "  " << c.viajes << "  " << c.roturas << "  " << (bono ? "SI" : "NO") << "\n";
    }
    return 0;
}
