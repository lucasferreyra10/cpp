/*
Id.Programa: G5Ej24Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de datos para el Ej.24 (AEROPUERTOS XXI).
    Crea archivos binarios de prueba:
      - PASAJEROS.DAT  (ordenado por Nro.Vuelo)
      - VUELOS.DAT     (cada registro: nroVuelo, codOrigen, codDestino, horaSalida hhmm, tiempo hhmm)
      - AEROPUERTOS.DAT (100 registros max; aquí usamos pocos; index = código)
      - TARIFAS.DAT    (registros por par origen-dest, contiene 3 tarifas: clase0, clase1, clase2)
    NOTA: Está pensado para generar un conjunto pequeño y testear el programa.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Pasajero {
    int nroVuelo;          // 5 díg.
    char apeNom[21];       // 20 + '\0'
    char dni[9];           // 8 + '\0'
    char nacional[21];     // 20 + '\0'
    int fecNac;            // aaaammdd
    int clase;             // 0,1,2
    char sexo;             // 'F','M'
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

void setStr(char *dst, const char *src, int n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // AEROPUERTOS.DAT
    {
        ofstream f("AEROPUERTOS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear AEROPUERTOS.DAT\n"; return 1; }

        Aeropuerto a;
        // We'll write 5 airports (codes 0..4)
        setStr(a.nombre, "Aero Norte", sizeof(a.nombre)); f.write((char*)&a, sizeof(a));
        setStr(a.nombre, "Aero Sur", sizeof(a.nombre)); f.write((char*)&a, sizeof(a));
        setStr(a.nombre, "Aero Este", sizeof(a.nombre)); f.write((char*)&a, sizeof(a));
        setStr(a.nombre, "Aero Oeste", sizeof(a.nombre)); f.write((char*)&a, sizeof(a));
        setStr(a.nombre, "Aero Central", sizeof(a.nombre)); f.write((char*)&a, sizeof(a));
        f.close();
        cout << "AEROPUERTOS.DAT generado.\n";
    }

    // VUELOS.DAT
    {
        ofstream f("VUELOS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear VUELOS.DAT\n"; return 1; }

        Vuelo v;
        // Create several flights with nroVuelo nonzero
        v.nroVuelo = 10001; v.codOrigen = 0; v.codDestino = 1; v.horaSalida =  600; v.tiempo = 0130; f.write((char*)&v, sizeof(v));
        v.nroVuelo = 10002; v.codOrigen = 0; v.codDestino = 2; v.horaSalida =  730; v.tiempo = 0200; f.write((char*)&v, sizeof(v));
        v.nroVuelo = 20010; v.codOrigen = 1; v.codDestino = 0; v.horaSalida =  945; v.tiempo = 0120; f.write((char*)&v, sizeof(v));
        v.nroVuelo = 30020; v.codOrigen = 2; v.codDestino = 3; v.horaSalida = 1230; v.tiempo = 0130; f.write((char*)&v, sizeof(v));
        v.nroVuelo = 40030; v.codOrigen = 3; v.codDestino = 4; v.horaSalida = 2015; v.tiempo = 0145; f.write((char*)&v, sizeof(v));
        v.nroVuelo = 50040; v.codOrigen = 4; v.codDestino = 0; v.horaSalida = 2350; v.tiempo = 0050; f.write((char*)&v, sizeof(v));
        // also write a record with nroVuelo = 0 to simulate empty slot
        v.nroVuelo = 0; v.codOrigen = 0; v.codDestino = 0; v.horaSalida = 0; v.tiempo = 0; f.write((char*)&v, sizeof(v));

        f.close();
        cout << "VUELOS.DAT generado.\n";
    }

    // PASAJEROS.DAT (ordered by nroVuelo)
    {
        ofstream f("PASAJEROS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear PASAJEROS.DAT\n"; return 1; }

        Pasajero p;
        // passengers for flight 10001
        p.nroVuelo = 10001; setStr(p.apeNom, "Gomez Juan", sizeof(p.apeNom)); setStr(p.dni, "20123456", sizeof(p.dni)); setStr(p.nacional, "Argentina", sizeof(p.nacional)); p.fecNac = 19800115; p.clase = 2; p.sexo = 'M'; f.write((char*)&p, sizeof(p));
        p.nroVuelo = 10001; setStr(p.apeNom, "Perez Ana", sizeof(p.apeNom)); setStr(p.dni, "20123457", sizeof(p.dni)); setStr(p.nacional, "Chile", sizeof(p.nacional)); p.fecNac = 19900220; p.clase = 1; p.sexo = 'F'; f.write((char*)&p, sizeof(p));

        // flight 10002
        p.nroVuelo = 10002; setStr(p.apeNom, "Lopez Carlos", sizeof(p.apeNom)); setStr(p.dni, "20123458", sizeof(p.dni)); setStr(p.nacional, "Brasil", sizeof(p.nacional)); p.fecNac = 19751205; p.clase = 0; p.sexo = 'M'; f.write((char*)&p, sizeof(p));
        p.nroVuelo = 10002; setStr(p.apeNom, "Diaz Laura", sizeof(p.apeNom)); setStr(p.dni, "20123459", sizeof(p.dni)); setStr(p.nacional, "Peru", sizeof(p.nacional)); p.fecNac = 19951230; p.clase = 2; p.sexo = 'F'; f.write((char*)&p, sizeof(p));

        // flight 20010
        p.nroVuelo = 20010; setStr(p.apeNom, "Alvarez Carla", sizeof(p.apeNom)); setStr(p.dni, "20123460", sizeof(p.dni)); setStr(p.nacional, "Uruguay", sizeof(p.nacional)); p.fecNac = 19881111; p.clase = 2; p.sexo = 'F'; f.write((char*)&p, sizeof(p));

        // flight 30020
        p.nroVuelo = 30020; setStr(p.apeNom, "Martinez Jose", sizeof(p.apeNom)); setStr(p.dni, "20123461", sizeof(p.dni)); setStr(p.nacional, "Paraguay", sizeof(p.nacional)); p.fecNac = 19930505; p.clase = 1; p.sexo = 'M'; f.write((char*)&p, sizeof(p));
        p.nroVuelo = 30020; setStr(p.apeNom, "Sosa Maria", sizeof(p.apeNom)); setStr(p.dni, "20123462", sizeof(p.dni)); setStr(p.nacional, "Chile", sizeof(p.nacional)); p.fecNac = 19900606; p.clase = 0; p.sexo = 'F'; f.write((char*)&p, sizeof(p));

        // flight 40030
        p.nroVuelo = 40030; setStr(p.apeNom, "Rojas Lucia", sizeof(p.apeNom)); setStr(p.dni, "20123463", sizeof(p.dni)); setStr(p.nacional, "Argentina", sizeof(p.nacional)); p.fecNac = 19840504; p.clase = 2; p.sexo = 'F'; f.write((char*)&p, sizeof(p));

        // flight 50040
        p.nroVuelo = 50040; setStr(p.apeNom, "Cano Pedro", sizeof(p.apeNom)); setStr(p.dni, "20123464", sizeof(p.dni)); setStr(p.nacional, "Argentina", sizeof(p.nacional)); p.fecNac = 19770101; p.clase = 1; p.sexo = 'M'; f.write((char*)&p, sizeof(p));

        f.close();
        cout << "PASAJEROS.DAT generado.\n";
    }

    // TARIFAS.DAT: for pairs used above (origen,dest)
    {
        ofstream f("TARIFAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear TARIFAS.DAT\n"; return 1; }

        Tarifa t;
        t.origen = 0; t.destino = 1; t.valorClase0 = 1000.0; t.valorClase1 = 700.0; t.valorClase2 = 400.0; f.write((char*)&t, sizeof(t));
        t.origen = 0; t.destino = 2; t.valorClase0 = 1500.0; t.valorClase1 = 1000.0; t.valorClase2 = 600.0; f.write((char*)&t, sizeof(t));
        t.origen = 1; t.destino = 0; t.valorClase0 = 900.0; t.valorClase1 = 600.0; t.valorClase2 = 350.0; f.write((char*)&t, sizeof(t));
        t.origen = 2; t.destino = 3; t.valorClase0 = 1200.0; t.valorClase1 = 800.0; t.valorClase2 = 500.0; f.write((char*)&t, sizeof(t));
        t.origen = 3; t.destino = 4; t.valorClase0 = 1300.0; t.valorClase1 = 900.0; t.valorClase2 = 550.0; f.write((char*)&t, sizeof(t));
        t.origen = 4; t.destino = 0; t.valorClase0 = 1100.0; t.valorClase1 = 750.0; t.valorClase2 = 420.0; f.write((char*)&t, sizeof(t));

        f.close();
        cout << "TARIFAS.DAT generado.\n";
    }

    cout << "Generador G5Ej24 finalizado.\n";
    return 0;
}
