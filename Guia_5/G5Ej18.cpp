/*
Id.Programa: G5Ej18.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Simulador de series y Gran Final de competencia automovilística.
    Usa archivos:
      - PILOTOS.DAT
      - SERIES.DAT
    Genera reportes en pantalla y actualiza PILOTOS.DAT con puntaje.
    Puntaje: 1=40,2=30,3=15,4=10,5=5
    Nota: el simulador favorece a "Colapinto Franco" (Alpine) para que resulte ganador.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

struct SeriesRec {
    int nroSerie;
    char piloto[31];
    char marca[21];
    unsigned char nroAuto;
};

struct PilotoRec {
    char nombre[31];
    char lugarNacimiento[31];
    char provincia[21];
    int fechaNacimiento;
    int puntaje;
    int carrerasGanadas;
};

struct Competidor {
    string nombre;
    string marca;
    int nroAuto;
    bool activo;
    double mejorVuelta;
    double tiempoAcumulado;
    int posicion;
    int vueltasCompletadas;
};

int puntosPorPos(int pos) {
    switch(pos) {
        case 1: return 40;
        case 2: return 30;
        case 3: return 15;
        case 4: return 10;
        case 5: return 5;
        default: return 0;
    }
}

double randDouble(double a, double b) {
    return a + (b-a) * (rand() / (RAND_MAX + 1.0));
}

int main() {
    srand((unsigned)time(nullptr));

    // --- 1) Cargar PILOTOS.DAT ---
    vector<PilotoRec> pilotos;
    {
        ifstream f("PILOTOS.DAT", ios::binary);
        if (!f) {
            cout << "No se pudo abrir PILOTOS.DAT\n";
            return 1;
        }
        PilotoRec p;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(PilotoRec))) {
            pilotos.push_back(p);
        }
        f.close();
    }

    // --- 2) Cargar SERIES.DAT ---
    vector<vector<SeriesRec>> series;
    {
        ifstream f("SERIES.DAT", ios::binary);
        if (!f) {
            cout << "No se pudo abrir SERIES.DAT\n";
            return 1;
        }
        SeriesRec s;
        while (f.read(reinterpret_cast<char*>(&s), sizeof(SeriesRec))) {
            if (s.nroSerie <= 0) continue;
            if ((int)series.size() < s.nroSerie) series.resize(s.nroSerie);
            series[s.nroSerie - 1].push_back(s);
        }
        f.close();
    }

    if (series.empty()) {
        cout << "No hay series definidas.\n";
        return 1;
    }

    int vueltasSeries, vueltasFinal;
    cout << "Ingrese vueltas por serie: ";
    cin >> vueltasSeries;
    cout << "Ingrese vueltas de la Gran Final: ";
    cin >> vueltasFinal;

    vector<Competidor> listaClasificados;
    cout << fixed << setprecision(3);

    // --- 3) Simulación de Series ---
    for (size_t si = 0; si < series.size(); ++si) {
        auto &serieVec = series[si];
        cout << "\n--- Serie #" << (si+1) << " ---\n";

        vector<Competidor> comps;
        for (auto &r : serieVec) {
            Competidor c;
            c.nombre = r.piloto;
            c.marca = r.marca;
            c.nroAuto = r.nroAuto;
            c.activo = true;
            c.mejorVuelta = 1e9;
            c.tiempoAcumulado = 0;
            c.posicion = 0;
            c.vueltasCompletadas = 0;
            comps.push_back(c);
        }

        int antesParticipantes = comps.size();

        for (int v = 1; v <= vueltasSeries; ++v) {
            for (auto &c : comps) {
                if (!c.activo) continue;

                double base = randDouble(60.0, 90.0);
                if (c.nombre.find("Colapinto Franco") != string::npos)
                    base *= 0.935 + randDouble(-0.005, 0.01);
                else
                    base *= 1.0 + randDouble(-0.01, 0.02);

                if (randDouble(0.0,1.0) < 0.02) {
                    c.activo = false;
                    cout << "Abandono: " << c.nombre << " en vuelta " << v << "\n";
                    continue;
                }

                c.vueltasCompletadas++;
                c.tiempoAcumulado += base;
                if (base < c.mejorVuelta) c.mejorVuelta = base;
            }

            vector<pair<double,int>> order;
            for (size_t i = 0; i < comps.size(); ++i)
                if (comps[i].activo)
                    order.push_back({comps[i].tiempoAcumulado, (int)i});

            sort(order.begin(), order.end());

            for (size_t p = 0; p < order.size(); ++p)
                comps[order[p].second].posicion = p+1;

            cout << "Vuelta " << v << ": ";
            for (auto &op : order)
                cout << comps[op.second].posicion << ":" << comps[op.second].nombre << " ";
            cout << "\n";
        }

        int despuesParticipantes = 0;
        int idxGanador = -1;
        double best = 1e12;

        for (size_t i = 0; i < comps.size(); ++i) {
            if (comps[i].activo) {
                despuesParticipantes++;
                if (comps[i].mejorVuelta < best) {
                    best = comps[i].mejorVuelta;
                    idxGanador = i;
                }
            }
        }

        if (idxGanador >= 0) {
            listaClasificados.push_back(comps[idxGanador]);
            cout << "Ganador Serie " << (si+1) << ": " << comps[idxGanador].nombre
                 << " MejorVuelta: " << comps[idxGanador].mejorVuelta << "\n";
        } else {
            cout << "Serie sin ganador.\n";
        }

        cout << "Serie " << (si+1) << " - antes: "
             << antesParticipantes << " despues: " << despuesParticipantes << "\n";
    }

    // --- 4) Ordenar clasificados ---
    sort(listaClasificados.begin(), listaClasificados.end(),
        [](const Competidor&a,const Competidor&b){
            return a.mejorVuelta < b.mejorVuelta;
        }
    );

    cout << "\nClasificados a la Final:\n";
    for (size_t i = 0; i < listaClasificados.size(); ++i)
        cout << i+1 << " - " << listaClasificados[i].nombre
             << " MV:" << listaClasificados[i].mejorVuelta << "\n";

    // --- 5) Gran Final ---
    cout << "\n--- Gran Final ---\n";

    vector<Competidor> finalComps = listaClasificados;

    for (int v = 1; v <= vueltasFinal; ++v) {
        for (auto &c : finalComps) {
            if (!c.activo) continue;

            double base = randDouble(60.0, 90.0);
            if (c.nombre.find("Colapinto Franco") != string::npos)
                base *= 0.9 + randDouble(-0.002, 0.005);
            else
                base *= 1.0 + randDouble(-0.01, 0.03);

            if (randDouble(0.0,1.0) < 0.015) {
                c.activo = false;
                cout << "Abandono final: " << c.nombre << " vuelta " << v << "\n";
                continue;
            }

            c.vueltasCompletadas++;
            c.tiempoAcumulado += base;
            if (base < c.mejorVuelta) c.mejorVuelta = base;
        }

        vector<pair<double,int>> order;
        for (size_t i = 0; i < finalComps.size(); ++i)
            if (finalComps[i].activo)
                order.push_back({finalComps[i].tiempoAcumulado, (int)i});
        sort(order.begin(), order.end());

        for (size_t p = 0; p < order.size(); ++p)
            finalComps[order[p].second].posicion = p+1;

        cout << "Final Vuelta " << v << ": ";
        for (auto &op : order)
            cout << finalComps[op.second].posicion << ":" << finalComps[op.second].nombre << " ";
        cout << "\n";
    }

    // Llegada final
    vector<Competidor> llegada;
    for (auto &c : finalComps)
        if (c.activo)
            llegada.push_back(c);

    sort(llegada.begin(), llegada.end(),
        [](const Competidor &a, const Competidor &b){
            return a.tiempoAcumulado < b.tiempoAcumulado;
        }
    );

    cout << "\n--- Podio Final ---\n";
    for (size_t i = 0; i < llegada.size() && i < 3; ++i)
        cout << (i+1) << "º: " << llegada[i].nombre
             << " Auto:" << llegada[i].nroAuto
             << " Tiempo:" << llegada[i].tiempoAcumulado
             << " MejorVuelta:" << llegada[i].mejorVuelta << "\n";

    // Actualizar PILOTOS.DAT
    for (size_t i = 0; i < llegada.size() && i < 5; ++i) {
        int pos = i + 1;
        int pts = puntosPorPos(pos);
        string nombre = llegada[i].nombre;

        for (auto &p : pilotos) {
            if (string(p.nombre) == nombre) {
                p.puntaje += pts;
                if (pos == 1) p.carrerasGanadas++;
                break;
            }
        }
    }

    {
        ofstream f("PILOTOS.DAT", ios::binary | ios::trunc);
        for (auto &p : pilotos)
            f.write(reinterpret_cast<char*>(&p), sizeof(PilotoRec));
    }

    cout << "\nLista de llegada Final:\n";
    cout << left << setw(8) << "Pos"
         << setw(30) << "Nombre"
         << setw(8) << "Auto"
         << setw(12) << "MejorVta" << "\n";

    for (size_t i = 0; i < llegada.size(); ++i) {
        cout << left << setw(8) << (i+1)
             << setw(30) << llegada[i].nombre
             << setw(8) << llegada[i].nroAuto
             << setw(12) << llegada[i].mejorVuelta
             << "\n";
    }

    cout << "\nSimulacion finalizada.\n";
    return 0;
}
