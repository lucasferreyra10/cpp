/*
Id.Programa: G5Ej21Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de datos para G5Ej21.
    Crea 2 archivos con infracciones de 1997 (dos zonas):
      - ZONA1.DAT  (ordenado por fecha creciente)
      - ZONA2.DAT  (ordenado por fecha creciente)
    Cada registro contiene:
      - Patente (6 chars)
      - Nro. registro Conductor (8 díg.)
      - Fecha (aammdd) (int)
      - Zona (6 chars)
      - Cód. de infracción (5 chars)
      - Nro. placa policial (6 chars)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Infraccion {
    char patente[7];        // 6 + '\0'
    char nroConductor[9];   // 8 + '\0'
    int fecha;              // aammdd (ej: 970101)
    char zona[7];           // 6 + '\0'
    char codInfr[6];        // 5 + '\0'
    char nroPlaca[7];       // 6 + '\0'
};

void setStr(char *dst, const char *src, size_t n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // Archivo ZONA1.DAT
    {
        ofstream f("ZONA1.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear ZONA1.DAT\n"; return 1; }

        Infraccion r;

        // Patente ABC123 tiene infracciones en TODOS los meses (para test)
        setStr(r.patente, "ABC123", sizeof(r.patente));
        setStr(r.nroConductor, "00000001", sizeof(r.nroConductor));
        setStr(r.zona, "NORTE", sizeof(r.zona));
        setStr(r.codInfr, "10001", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0011", sizeof(r.nroPlaca));
        // fechas de enero a junio (orden creciente)
        r.fecha = 970101; f.write((char*)&r, sizeof(r));
        r.fecha = 970215; f.write((char*)&r, sizeof(r));
        r.fecha = 970303; f.write((char*)&r, sizeof(r));
        r.fecha = 970415; f.write((char*)&r, sizeof(r));
        r.fecha = 970528; f.write((char*)&r, sizeof(r));
        r.fecha = 970630; f.write((char*)&r, sizeof(r));

        // Otra patente DEF456 con algunos meses
        setStr(r.patente, "DEF456", sizeof(r.patente));
        setStr(r.nroConductor, "00000002", sizeof(r.nroConductor));
        setStr(r.zona, "NORTE", sizeof(r.zona));
        setStr(r.codInfr, "20002", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0022", sizeof(r.nroPlaca));
        r.fecha = 970210; f.write((char*)&r, sizeof(r));
        r.fecha = 970615; f.write((char*)&r, sizeof(r));

        // Patente GHI789 appears in zone1 later in year
        setStr(r.patente, "GHI789", sizeof(r.patente));
        setStr(r.nroConductor, "00000003", sizeof(r.nroConductor));
        setStr(r.zona, "NORTE", sizeof(r.zona));
        setStr(r.codInfr, "30003", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0033", sizeof(r.nroPlaca));
        r.fecha = 970730; f.write((char*)&r, sizeof(r));
        r.fecha = 970815; f.write((char*)&r, sizeof(r));

        f.close();
        cout << "ZONA1.DAT generado.\n";
    }

    // Archivo ZONA2.DAT
    {
        ofstream f("ZONA2.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear ZONA2.DAT\n"; return 1; }

        Infraccion r;

        // Continue ABC123 to have months July..December here (so ABC123 has all 12 months)
        setStr(r.patente, "ABC123", sizeof(r.patente));
        setStr(r.nroConductor, "00000001", sizeof(r.nroConductor));
        setStr(r.zona, "SUR", sizeof(r.zona));
        setStr(r.codInfr, "10002", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0044", sizeof(r.nroPlaca));
        // fechas julio..dec (ordered)
        r.fecha = 970701; f.write((char*)&r, sizeof(r));
        r.fecha = 970808; f.write((char*)&r, sizeof(r));
        r.fecha = 970909; f.write((char*)&r, sizeof(r));
        r.fecha = 971010; f.write((char*)&r, sizeof(r));
        r.fecha = 971111; f.write((char*)&r, sizeof(r));
        r.fecha = 971212; f.write((char*)&r, sizeof(r));

        // DEF456 has another entry
        setStr(r.patente, "DEF456", sizeof(r.patente));
        setStr(r.nroConductor, "00000002", sizeof(r.nroConductor));
        setStr(r.zona, "SUR", sizeof(r.zona));
        setStr(r.codInfr, "20003", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0055", sizeof(r.nroPlaca));
        r.fecha = 970322; f.write((char*)&r, sizeof(r));
        r.fecha = 970922; f.write((char*)&r, sizeof(r));

        // New plate JKL012 with several months but not all
        setStr(r.patente, "JKL012", sizeof(r.patente));
        setStr(r.nroConductor, "00000004", sizeof(r.nroConductor));
        setStr(r.zona, "SUR", sizeof(r.zona));
        setStr(r.codInfr, "40004", sizeof(r.codInfr));
        setStr(r.nroPlaca, "PL0066", sizeof(r.nroPlaca));
        r.fecha = 970405; f.write((char*)&r, sizeof(r));
        r.fecha = 970608; f.write((char*)&r, sizeof(r));
        r.fecha = 971011; f.write((char*)&r, sizeof(r));

        f.close();
        cout << "ZONA2.DAT generado.\n";
    }

    cout << "Generador G5Ej21 finalizado.\n";
    return 0;
}