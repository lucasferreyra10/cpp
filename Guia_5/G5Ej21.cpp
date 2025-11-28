/*
Id.Programa: G5Ej21.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    - Fusiona ZONA1.DAT y ZONA2.DAT en CAPITOT.DAT ordenado por:
         1) Patente (ascendente, alfabético)
         2) Fecha (descendente)
    - Imprime listado de vehículos que tuvieron infracciones en los 12 meses (1997),
      mostrando cantidad por mes y total.
    Formato de registro (en ambos archivos y en CAPITOT.DAT):
      - Patente (6 chars)
      - Nro. registro Conductor (8 chars)
      - Fecha (aammdd) int
      - Zona (6 chars)
      - Cod. infraccion (5 chars)
      - Nro. placa policial (6 chars)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Infraccion {
    char patente[7];
    char nroConductor[9];
    int fecha;       // aammdd
    char zona[7];
    char codInfr[6];
    char nroPlaca[7];
};

int extraerMes(int fecha) {
    // fecha formato aammdd -> (fecha / 100) % 100
    return (fecha / 100) % 100;
}

int main() {
    cout << fixed << setprecision(0);

    // 1) Leer ambos archivos
    vector<Infraccion> all;

    auto leerArchivo = [&](const char* nombre) {
        ifstream f(nombre, ios::binary);
        if (!f) {
            cerr << "No se pudo abrir " << nombre << "\n";
            return;
        }
        Infraccion r;
        while (f.read(reinterpret_cast<char*>(&r), sizeof(Infraccion))) {
            all.push_back(r);
        }
        f.close();
        cout << nombre << " leido.\n";
    };

    leerArchivo("ZONA1.DAT");
    leerArchivo("ZONA2.DAT");

    if (all.empty()) {
        cerr << "No hay registros leidos.\n";
        return 1;
    }

    // 2) Ordenar por patente asc, fecha desc
    sort(all.begin(), all.end(), [](const Infraccion &a, const Infraccion &b) {
        int cmp = strcmp(a.patente, b.patente);
        if (cmp != 0) return cmp < 0;
        return a.fecha > b.fecha; // fecha descendente
    });

    // 3) Grabar CAPITOT.DAT
    {
        ofstream f("CAPITOT.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear CAPITOT.DAT\n"; return 1; }
        for (auto &r : all) f.write(reinterpret_cast<char*>(&r), sizeof(Infraccion));
        f.close();
        cout << "CAPITOT.DAT generado con " << all.size() << " registros.\n";
    }

    // 4) Calcular infracciones por mes por patente
    // Map patente -> array[13] (index 1..12). index 0 unused, last element total at index 0 or compute later.
    map<string, array<int,13>> counts;

    for (auto &r : all) {
        string pat = string(r.patente);
        int mes = extraerMes(r.fecha);
        if (mes >= 1 && mes <= 12) {
            counts[pat][mes] += 1;
        }
    }

    // 5) Imprimir los que tienen infracciones en todos los meses (1..12)
    cout << "\nTotal de Infracciones por mes\n";
    cout << left << setw(10) << "COD/PATENTE";
    for (int m = 1; m <= 12; ++m) {
        cout << right << setw(6) << ("M" + to_string(m));
    }
    cout << right << setw(8) << "Total\n";

    for (auto &p : counts) {
        bool todos = true;
        int total = 0;
        for (int m = 1; m <= 12; ++m) {
            if (p.second[m] <= 0) { todos = false; }
            total += p.second[m];
        }
        if (todos) {
            cout << left << setw(10) << p.first;
            for (int m = 1; m <= 12; ++m) cout << right << setw(6) << p.second[m];
            cout << right << setw(8) << total << "\n";
        }
    }

    cout << "\nProceso terminado.\n";
    return 0;
}
