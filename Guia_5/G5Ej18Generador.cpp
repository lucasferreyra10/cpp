/*
Id.Programa: G5Ej18Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Genera archivos:
      - PILOTOS.DAT
      - SERIES.DAT
    para probar el simulador G5Ej18.cpp
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct PilotoRec {
    char nombre[31];
    char lugarNacimiento[31];
    char provincia[21];
    int fechaNacimiento; // formato DDMMAA o AAAAMMDD (a elección)
    int puntaje;
    int carrerasGanadas;
};

struct SeriesRec {
    int nroSerie;
    char piloto[31];
    char marca[21];
    unsigned char nroAuto;
};

void addPilot(ofstream &f, const char *nom, const char *ln, const char *prov, int fecha) {
    PilotoRec p{};
    strcpy(p.nombre, nom);
    strcpy(p.lugarNacimiento, ln);
    strcpy(p.provincia, prov);
    p.fechaNacimiento = fecha;
    p.puntaje = 0;
    p.carrerasGanadas = 0;
    f.write(reinterpret_cast<char*>(&p), sizeof(PilotoRec));
}

void addSeriesRec(ofstream &f, int serie, const char *piloto, const char *marca, int nroAuto) {
    SeriesRec s{};
    s.nroSerie = serie;
    strcpy(s.piloto, piloto);
    strcpy(s.marca, marca);
    s.nroAuto = (unsigned char)nroAuto;
    f.write(reinterpret_cast<char*>(&s), sizeof(SeriesRec));
}

int main() {
    // --- Genera PILOTOS.DAT ---
    {
        ofstream f("PILOTOS.DAT", ios::binary | ios::trunc);
        if (!f) { cout << "ERROR creando PILOTOS.DAT\n"; return 1; }

        // Fechas corregidas: sin ceros iniciales (antes producían octal)
        addPilot(f, "Colapinto Franco", "Pilar", "Buenos Aires", 11603);
        addPilot(f, "Norris Lando", "Bristol", "England", 131199);
        addPilot(f, "Sainz Carlos", "Madrid", "Madrid", 100994);
        addPilot(f, "Gasly Pierre", "Rouen", "Normandy", 70296);
        addPilot(f, "Hamilton Lewis", "Stevenage", "Herts", 70185);
        addPilot(f, "Piastri Oscar", "Melbourne", "Victoria", 60401);
        addPilot(f, "Leclerc Charles", "Montecarlo", "Monaco", 101097);
        addPilot(f, "Verstappen Max", "Hasselt", "Belgium", 30997);

        f.close();
    }

    // --- Genera SERIES.DAT ---
    {
        ofstream f("SERIES.DAT", ios::binary | ios::trunc);
        if (!f) { cout << "ERROR creando SERIES.DAT\n"; return 1; }

        // 3 series de ejemplo, 3 pilotos cada una
        // Serie 1
        addSeriesRec(f, 1, "Colapinto Franco", "Alpine", 1);
        addSeriesRec(f, 1, "Norris Lando", "McLaren", 4);
        addSeriesRec(f, 1, "Gasly Pierre", "Alpine", 10);

        // Serie 2
        addSeriesRec(f, 2, "Hamilton Lewis", "Mercedes", 44);
        addSeriesRec(f, 2, "Leclerc Charles", "Ferrari", 16);
        addSeriesRec(f, 2, "Piastri Oscar", "McLaren", 81);

        // Serie 3
        addSeriesRec(f, 3, "Sainz Carlos", "Ferrari", 55);
        addSeriesRec(f, 3, "Verstappen Max", "RedBull", 33);
        addSeriesRec(f, 3, "Gasly Pierre", "Alpine", 10);
    }

    cout << "Archivos PILOTOS.DAT y SERIES.DAT generados correctamente.\n";
    return 0;
}
