/*
Id.Programa: G5Ej24.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    - Emite listado de SALIDAS por Cód.Aerop. (asc) y Nro.Vuelo (desc).
    - Graba LLEGADAS.DAT con registros: CodOrig, CodDest, NroVuelo, HoraLlegada(hhmm),
      CantHombres, CantMujeres, ImporteClase0, ImporteClase1, ImporteClase2.
    - Usa archivos binarios:
        PASAJEROS.DAT, VUELOS.DAT, AEROPUERTOS.DAT, TARIFAS.DAT
    Notas:
    - Se asume que TARIFAS.DAT tiene entradas (origen,dest) únicas con 3 valores.
    - PASAJEROS.DAT está ordenado por Nro.Vuelo (facilita agrupación).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;

struct Pasajero {
    int nroVuelo;
    char apeNom[21];
    char dni[9];
    char nacional[21];
    int fecNac;
    int clase;
    char sexo;
};

struct Vuelo {
    int nroVuelo;
    int codOrigen;
    int codDestino;
    int horaSalida; // hhmm
    int tiempo;     // hhmm duration
};

struct Aeropuerto {
    char nombre[21];
};

struct Tarifa {
    int origen;
    int destino;
    double valorClase0;
    double valorClase1;
    double valorClase2;
};

struct LlegadaRec {
    int codOrigen;
    int codDestino;
    int nroVuelo;
    int horaLlegada; // hhmm
    int cantHombres;
    int cantMujeres;
    double impClase0;
    double impClase1;
    double impClase2;
};

int tiempoAMinutos(int hhmm) {
    int hh = hhmm / 100;
    int mm = hhmm % 100;
    return hh * 60 + mm;
}

int minutosAHHMM(int minutos) {
    minutos = minutos % (24*60);
    if (minutos < 0) minutos += 24*60;
    int hh = minutos / 60;
    int mm = minutos % 60;
    return hh * 100 + mm;
}

int main() {
    cout << fixed << setprecision(2);

    // 1) Leer AEROPUERTOS
    vector<string> aeropuertos;
    {
        ifstream f("AEROPUERTOS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir AEROPUERTOS.DAT\n"; return 1; }
        Aeropuerto a;
        while (f.read(reinterpret_cast<char*>(&a), sizeof(a))) {
            aeropuertos.push_back(string(a.nombre));
        }
        f.close();
    }

    // 2) Leer VUELOS
    vector<Vuelo> vuelos;
    {
        ifstream f("VUELOS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir VUELOS.DAT\n"; return 1; }
        Vuelo v;
        while (f.read(reinterpret_cast<char*>(&v), sizeof(v))) {
            // only keep flights with nroVuelo != 0
            if (v.nroVuelo != 0) vuelos.push_back(v);
        }
        f.close();
    }

    // 3) Leer PASAJEROS y agrupar por nroVuelo
    unordered_map<int, vector<Pasajero>> paxPorVuelo;
    {
        ifstream f("PASAJEROS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir PASAJEROS.DAT\n"; return 1; }
        Pasajero p;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            paxPorVuelo[p.nroVuelo].push_back(p);
        }
        f.close();
    }

    // 4) Leer TARIFAS en map key=(origen<<16)|destino
    unordered_map<int, Tarifa> tarifas;
    {
        ifstream f("TARIFAS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir TARIFAS.DAT\n"; return 1; }
        Tarifa t;
        while (f.read(reinterpret_cast<char*>(&t), sizeof(t))) {
            int key = (t.origen << 16) | (t.destino & 0xFFFF);
            tarifas[key] = t;
        }
        f.close();
    }

    // 5) Index vuelos por origen -> vector<Vuelo>
    map<int, vector<Vuelo>> vuelosPorOrigen;
    for (auto &v : vuelos) {
        vuelosPorOrigen[v.codOrigen].push_back(v);
    }

    // Sort flights per origin by nroVuelo descending
    for (auto &par : vuelosPorOrigen) {
        auto &vec = par.second;
        sort(vec.begin(), vec.end(), [](const Vuelo &a, const Vuelo &b){
            return a.nroVuelo > b.nroVuelo;
        });
    }

    // 6) Imprimir listado de SALIDAS
    cout << "\nSALIDAS DE VUELOS\n";
    for (auto &par : vuelosPorOrigen) {
        int codAero = par.first;
        string nombreAero = (codAero >= 0 && codAero < (int)aeropuertos.size()) ? aeropuertos[codAero] : string("AEROP_DESCONOCIDO");
        cout << "\nCÓD.AEROP.: " << codAero << "  AEROP.: " << nombreAero << " (Origen)\n";
        // cada vuelo
        for (auto &v : par.second) {
            string destName = (v.codDestino >= 0 && v.codDestino < (int)aeropuertos.size()) ? aeropuertos[v.codDestino] : string("AEROP_DESCONOCIDO");
            // header for flight
            cout << "** CÓD.AEROP.: " << v.codDestino << "  AEROP.: " << destName << " (Destino)\n";
            cout << "** NRO.DE VUELO: " << v.nroVuelo << "  HORA: ";
            int hhmm = v.horaSalida;
            int hh = hhmm / 100; int mm = hhmm % 100;
            cout << setw(2) << setfill('0') << hh << ":" << setw(2) << setfill('0') << mm << setfill(' ') << "\n";
            // listar pasajeros (orden APELLIDO, NOMBRE)
            auto &vecPax = paxPorVuelo[v.nroVuelo];
            // sort copy by apeNom
            vector<Pasajero> sortedPax = vecPax;
            sort(sortedPax.begin(), sortedPax.end(), [](const Pasajero &a, const Pasajero &b){
                return strcmp(a.apeNom, b.apeNom) < 0;
            });
            cout << left << setw(30) << "ORDEN APELLIDO, NOMBRE" << setw(12) << "Nro.Doc." << setw(12) << "Fec.Nac." << "\n";
            for (auto &p : sortedPax) {
                // format date aaaammdd -> dd/mm/aaaa
                int f = p.fecNac;
                int a = f / 10000;
                int m = (f / 100) % 100;
                int d = f % 100;
                char fechaBuf[16];
                snprintf(fechaBuf, sizeof(fechaBuf), "%02d/%02d/%04d", d, m, a);
                cout << left << setw(30) << p.apeNom << setw(12) << p.dni << setw(12) << fechaBuf << "\n";
            }
            if (sortedPax.empty()) cout << "   (Sin pasajeros registrados)\n";
            cout << "\n";
        }
    }

    // 7) Generar LLEGADAS.DAT
    {
        ofstream f("LLEGADAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear LLEGADAS.DAT\n"; return 1; }

        for (auto &v : vuelos) {
            LlegadaRec rec;
            rec.codOrigen = v.codOrigen;
            rec.codDestino = v.codDestino;
            rec.nroVuelo = v.nroVuelo;

            int salidaMin = tiempoAMinutos(v.horaSalida);
            int durMin = tiempoAMinutos(v.tiempo);
            int llegadaMin = salidaMin + durMin;
            rec.horaLlegada = minutosAHHMM(llegadaMin);

            rec.cantHombres = 0;
            rec.cantMujeres = 0;
            rec.impClase0 = rec.impClase1 = rec.impClase2 = 0.0;

            auto it = paxPorVuelo.find(v.nroVuelo);
            if (it != paxPorVuelo.end()) {
                for (auto &p : it->second) {
                    if (p.sexo == 'M') rec.cantHombres++;
                    else if (p.sexo == 'F') rec.cantMujeres++;
                    // buscar tarifa
                    int key = (v.codOrigen << 16) | (v.codDestino & 0xFFFF);
                    auto tfIt = tarifas.find(key);
                    double tarifa0 = 0.0, tarifa1 = 0.0, tarifa2 = 0.0;
                    if (tfIt != tarifas.end()) {
                        tarifa0 = tfIt->second.valorClase0;
                        tarifa1 = tfIt->second.valorClase1;
                        tarifa2 = tfIt->second.valorClase2;
                    } else {
                        // si no hay tarifa, dejamos 0 y podriamos avisar
                    }
                    if (p.clase == 0) rec.impClase0 += tarifa0;
                    else if (p.clase == 1) rec.impClase1 += tarifa1;
                    else if (p.clase == 2) rec.impClase2 += tarifa2;
                }
            }
            // grabar
            f.write(reinterpret_cast<char*>(&rec), sizeof(rec));
        }
        f.close();
        cout << "LLEGADAS.DAT generado.\n";
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
