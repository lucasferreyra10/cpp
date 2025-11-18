/*
Id.Programa: G4Ej12_GenerarDatos.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Genera archivos binarios de prueba para G4Ej12:
    - Vehiculos.dat
    - Importes.dat
    - Infracciones.dat
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Vehiculo {
    int modelo;
    int anio;
    char patente[7];
    char titular[41];
    char domicilio[41];
    int codPostal;
};

struct Importe {
    int modelo;
    int anio;
    float importeAnual;
};

struct Infraccion {
    char patente[7];
    int cantidad;
};

void copyStr(char* dest, const char* src, int maxLen) {
    strncpy(dest, src, maxLen);
    dest[maxLen] = '\0';
}

int main() {
    cout << "=== Generando datos para G4Ej12 ===\n\n";

    // ---------------- Vehiculos.dat ----------------
    {
        ofstream f("Vehiculos.dat", ios::binary | ios::trunc);
        if (!f) {
            cerr << "No se pudo crear Vehiculos.dat\n";
            return 1;
        }

        Vehiculo v;

        // Vehículo 1
        v.modelo = 1001;
        v.anio = 2020;
        copyStr(v.patente, "ABC123", 6);
        copyStr(v.titular, "Lopez Juan", 40);
        copyStr(v.domicilio, "Av Siempre Viva 123", 40);
        v.codPostal = 1400;
        f.write(reinterpret_cast<char*>(&v), sizeof(v));

        // Vehículo 2
        v.modelo = 1002;
        v.anio = 2018;
        copyStr(v.patente, "DEF456", 6);
        copyStr(v.titular, "Martinez Carla", 40);
        copyStr(v.domicilio, "Calle Falsa 742", 40);
        v.codPostal = 1750;
        f.write(reinterpret_cast<char*>(&v), sizeof(v));

        // Vehículo 3
        v.modelo = 1003;
        v.anio = 2022;
        copyStr(v.patente, "GHI789", 6);
        copyStr(v.titular, "Fernandez Pablo", 40);
        copyStr(v.domicilio, "Ruta 3 Km 45", 40);
        v.codPostal = 1832;
        f.write(reinterpret_cast<char*>(&v), sizeof(v));

        f.close();
        cout << "Vehiculos.dat generado.\n";
    }

    // ---------------- Importes.dat ----------------
    {
        ofstream f("Importes.dat", ios::binary | ios::trunc);
        if (!f) {
            cerr << "No se pudo crear Importes.dat\n";
            return 1;
        }

        Importe imp;

        imp.modelo = 1001;
        imp.anio = 2020;
        imp.importeAnual = 60000.0f;
        f.write(reinterpret_cast<char*>(&imp), sizeof(imp));

        imp.modelo = 1002;
        imp.anio = 2018;
        imp.importeAnual = 45000.0f;
        f.write(reinterpret_cast<char*>(&imp), sizeof(imp));

        imp.modelo = 1003;
        imp.anio = 2022;
        imp.importeAnual = 80000.0f;
        f.write(reinterpret_cast<char*>(&imp), sizeof(imp));

        f.close();
        cout << "Importes.dat generado.\n";
    }

    // ---------------- Infracciones.dat ----------------
    {
        ofstream f("Infracciones.dat", ios::binary | ios::trunc);
        if (!f) {
            cerr << "No se pudo crear Infracciones.dat\n";
            return 1;
        }

        Infraccion inf;

        copyStr(inf.patente, "ABC123", 6);
        inf.cantidad = 2;
        f.write(reinterpret_cast<char*>(&inf), sizeof(inf));

        copyStr(inf.patente, "DEF456", 6);
        inf.cantidad = 0;
        f.write(reinterpret_cast<char*>(&inf), sizeof(inf));

        copyStr(inf.patente, "GHI789", 6);
        inf.cantidad = 5;
        f.write(reinterpret_cast<char*>(&inf), sizeof(inf));

        f.close();
        cout << "Infracciones.dat generado.\n";
    }

    cout << "\n✅ Archivos generados correctamente.\n";
    cout << "Ahora ejecuta G4Ej12.exe.\n";
    return 0;
}
