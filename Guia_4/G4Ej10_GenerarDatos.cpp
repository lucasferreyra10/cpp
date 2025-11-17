/*
Id.Programa: G4Ej10_GenerarDatos.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025
Comentario.:
    Genera automaticamente:
    - DEUDA.DAT
    - INDICES.DAT
    - CONTRIBUYENTES.DAT

    Para probar G4Ej10.cpp
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// -------- Estructuras (idénticas a las usadas en G4Ej10) --------

struct RegDeuda {
    int  nroCbte;
    char apeNom[31];
    int  mes;
    int  anio;
    float importeOrig;
    char estado;      // 'A' adeuda, 'P' pagada
};

struct RegIndice {
    int  anio;
    int  mes;
    float coef;
};

struct RegContribuyente {
    int nroCbte;
};

void copyStr(char* dest, const char* src, int max) {
    strncpy(dest, src, max);
    dest[max] = '\0';
}

int main() {
    cout << "=== Generando archivos para G4Ej10 ===\n\n";

    // ---------------- DEUDA.DAT ----------------
    {
        ofstream f("DEUDA.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "Error al crear DEUDA.DAT\n"; return 1; }

        RegDeuda r;

        // --- Contribuyente 1 ---
        // Cabecera
        r.nroCbte = 10000001;
        copyStr(r.apeNom, "Lopez Juan", 30);
        r.mes = 0; r.anio = 0;
        r.importeOrig = 0;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // Cuota enero 2024
        r.mes = 1; r.anio = 2024;
        r.importeOrig = 15000;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // Cuota febrero 2024
        r.mes = 2; r.anio = 2024;
        r.importeOrig = 15000;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // --- Contribuyente 2 ---
        // Cabecera
        r.nroCbte = 10000002;
        copyStr(r.apeNom, "Martinez Carla", 30);
        r.mes = 0; r.anio = 0;
        r.importeOrig = 0;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // Cuota noviembre 2023
        r.mes = 11; r.anio = 2023;
        r.importeOrig = 20000;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // Cuota diciembre 2023
        r.mes = 12; r.anio = 2023;
        r.importeOrig = 20000;
        r.estado = 'P';   // ya pagada, no debería figurar
        f.write((char*)&r, sizeof(r));

        // --- Contribuyente 3 ---
        // Cabecera
        r.nroCbte = 10000003;
        copyStr(r.apeNom, "Fernandez Pablo", 30);
        r.mes = 0; r.anio = 0;
        r.importeOrig = 0;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        // Cuota enero 2022
        r.mes = 1; r.anio = 2022;
        r.importeOrig = 10000;
        r.estado = 'A';
        f.write((char*)&r, sizeof(r));

        f.close();
        cout << "DEUDA.DAT generado.\n";
    }

    // ---------------- INDICES.DAT ----------------
    {
        ofstream f("INDICES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "Error al crear INDICES.DAT\n"; return 1; }

        RegIndice idx;

        // Índices simplificados por mes
        // CUOTA → Se actualiza al MES 8 DEL 2025 (mes de proceso)
        // Meses más viejos tienen coef mayor
        float coef2022 = 2.20f;
        float coef2023 = 1.50f;
        float coef2024 = 1.15f;

        // Año 2022
        for (int m = 1; m <= 12; m++) {
            idx.anio = 2022; idx.mes = m; idx.coef = coef2022;
            f.write((char*)&idx, sizeof(idx));
        }

        // Año 2023
        for (int m = 1; m <= 12; m++) {
            idx.anio = 2023; idx.mes = m; idx.coef = coef2023;
            f.write((char*)&idx, sizeof(idx));
        }

        // Año 2024
        for (int m = 1; m <= 12; m++) {
            idx.anio = 2024; idx.mes = m; idx.coef = coef2024;
            f.write((char*)&idx, sizeof(idx));
        }

        f.close();
        cout << "INDICES.DAT generado.\n";
    }

    // ---------------- CONTRIBUYENTES.DAT ----------------
    {
        ofstream f("CONTRIBUYENTES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "Error al crear CONTRIBUYENTES.DAT\n"; return 1; }

        RegContribuyente c;

        // Solo 1 y 3 vinieron hoy a pedir actualización
        c.nroCbte = 10000001; f.write((char*)&c, sizeof(c));
        c.nroCbte = 10000003; f.write((char*)&c, sizeof(c));

        f.close();
        cout << "CONTRIBUYENTES.DAT generado.\n";
    }

    cout << "\n❇️ Archivos generados correctamente.\n";
    cout << "Ahora ejecuta G4Ej10.exe.\n";

    return 0;
}
