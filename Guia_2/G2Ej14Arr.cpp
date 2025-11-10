
/*
Id.Programa: G2Ej14Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Tabla de posiciones AFA. Leer partidos y calcular tabla.
             a) Orden desc por puntos
             b) Orden desc por puntos y diferencia de goles
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

struct Team {
    string nombre;
    int PJ=0, PG=0, PE=0, PP=0, GF=0, GC=0, PTS=0;
    int DG() const { return GF - GC; }
};

int main() {
    string leyenda;
    cout << "Ingrese leyenda del campeonato (Apertura/Clausura): ";
    getline(cin, leyenda);

    int R;
    cout << "Cantidad de partidos: ";
    cin >> R;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Team> equipos;
    auto getIndex = [&](const string& name)->int{
        for (int i=0;i<(int)equipos.size();++i) if (equipos[i].nombre==name) return i;
        equipos.push_back(Team{}); equipos.back().nombre=name; return (int)equipos.size()-1;
    };

    for (int i=0;i<R;++i) {
        string loc, vis;
        int gl, gv;
        cout << "Partido #" << (i+1) << " (Local goles Visitante goles):\n";
        cout << " Local: "; getline(cin, loc);
        cout << " Goles Local: "; cin >> gl; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Visitante: "; getline(cin, vis);
        cout << " Goles Visitante: "; cin >> gv; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int il = getIndex(loc), iv = getIndex(vis);
        equipos[il].PJ++; equipos[iv].PJ++;
        equipos[il].GF += gl; equipos[il].GC += gv;
        equipos[iv].GF += gv; equipos[iv].GC += gl;
        if (gl > gv) { equipos[il].PG++; equipos[iv].PP++; equipos[il].PTS += 3; }
        else if (gl < gv) { equipos[iv].PG++; equipos[il].PP++; equipos[iv].PTS += 3; }
        else { equipos[il].PE++; equipos[iv].PE++; equipos[il].PTS += 1; equipos[iv].PTS += 1; }
    }

    auto imprimir = [&](vector<Team> t, const string& titulo){
        sort(t.begin(), t.end(), [](const Team& a, const Team& b){
            if (a.PTS != b.PTS) return a.PTS > b.PTS;
            if (a.DG() != b.DG()) return a.DG() > b.DG();
            if (a.GF != b.GF) return a.GF > b.GF;
            return a.nombre < b.nombre;
        });
        cout << "\nCampeonato " << leyenda << " de la A.F.A.\n";
        cout << left << setw(20) << "Equipos" << right << setw(4) << "PJ" << setw(4) << "PG"
             << setw(4) << "PE" << setw(4) << "PP" << setw(4) << "GF" << setw(4) << "GC" << setw(5) << "PTS" << "\n";
        for (auto &e : t) {
            cout << left << setw(20) << e.nombre
                 << right << setw(4) << e.PJ << setw(4) << e.PG << setw(4) << e.PE << setw(4) << e.PP
                 << setw(4) << e.GF << setw(4) << e.GC << setw(5) << e.PTS << "\n";
        }
    };

    // b) es el mismo orden (PTS y DG). a) solo PTS: imprimimos dos veces para cumplir
    imprimir(equipos, "Por puntos");
    imprimir(equipos, "Por puntos y DG");
    return 0;
}
