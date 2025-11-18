/*
Id.Programa: G4Ej14_GenerarDatos.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Genera archivos de prueba para G4Ej14:
    - Empresas.dat
    - Ventas.dat

    Empresas.dat:
      Nro.Empresa (1..300000), Domicilio(20), RazonSocial(30),
      Cod.Pos., Localidad(30).
      Relacion 1 a 1 entre nroEmpresa y direccion:
        registro (nroEmp) se guarda en posicion (nroEmp-1).

    Ventas.dat:
      Nro.Empresa, NroMes (1..12), Importe (real).
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#pragma pack(push,1)
struct Empresa {
    int nroEmp;
    char domicilio[21];   // 20 + '\0'
    char razon[31];       // 30 + '\0'
    int codPos;
    char localidad[31];   // 30 + '\0'
};
#pragma pack(pop)

struct Venta {
    int nroEmp;
    int mes;
    float importe;
};

void copyStr(char* dest, const char* src, int maxLen) {
    strncpy(dest, src, maxLen);
    dest[maxLen] = '\0';
}

int main() {
    cout << "=== Generando datos para G4Ej14 ===\n\n";

    // ---------------- Empresas.dat ----------------
    {
        ofstream f("Empresas.dat", ios::binary | ios::trunc);
        if (!f) {
            cerr << "ERROR: No se pudo crear Empresas.dat\n";
            return 1;
        }

        Empresa e;

        // Vamos a crear 10 empresas (1..10)
        // (no necesitamos llegar a 300000 para probar)

        // Empresa 1
        e.nroEmp = 1;
        copyStr(e.domicilio, "Av. Siempre Viva 123", 20);
        copyStr(e.razon, "Estaciones Lopez SRL", 30);
        e.codPos = 1400;
        copyStr(e.localidad, "CABA", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 2
        e.nroEmp = 2;
        copyStr(e.domicilio, "Ruta 3 Km 45", 20);
        copyStr(e.razon, "Transporte Sur SA", 30);
        e.codPos = 1832;
        copyStr(e.localidad, "Lomas de Zamora", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 3
        e.nroEmp = 3;
        copyStr(e.domicilio, "Mitre 500", 20);
        copyStr(e.razon, "Supermercado El Ahorro", 30);
        e.codPos = 1754;
        copyStr(e.localidad, "Lanus", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 4
        e.nroEmp = 4;
        copyStr(e.domicilio, "San Martin 250", 20);
        copyStr(e.razon, "Textiles La Moda", 30);
        e.codPos = 1870;
        copyStr(e.localidad, "Avellaneda", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 5
        e.nroEmp = 5;
        copyStr(e.domicilio, "Belgrano 999", 20);
        copyStr(e.razon, "Panaderia La Espiga", 30);
        e.codPos = 1602;
        copyStr(e.localidad, "Vicente Lopez", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 6
        e.nroEmp = 6;
        copyStr(e.domicilio, "Colon 345", 20);
        copyStr(e.razon, "Servicios Informaticos SA", 30);
        e.codPos = 7600;
        copyStr(e.localidad, "Mar del Plata", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 7
        e.nroEmp = 7;
        copyStr(e.domicilio, "Rivadavia 1000", 20);
        copyStr(e.razon, "Ferreteria El Tornillo", 30);
        e.codPos = 1708;
        copyStr(e.localidad, "Moron", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 8
        e.nroEmp = 8;
        copyStr(e.domicilio, "Hipolito Yrigoyen 3500", 20);
        copyStr(e.razon, "Autos del Sur SA", 30);
        e.codPos = 1876;
        copyStr(e.localidad, "Quilmes", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 9
        e.nroEmp = 9;
        copyStr(e.domicilio, "9 de Julio 50", 20);
        copyStr(e.razon, "Hotel Central", 30);
        e.codPos = 2000;
        copyStr(e.localidad, "Rosario", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        // Empresa 10
        e.nroEmp = 10;
        copyStr(e.domicilio, "Sarmiento 222", 20);
        copyStr(e.razon, "Farmacia Salud", 30);
        e.codPos = 5500;
        copyStr(e.localidad, "Mendoza", 30);
        f.write(reinterpret_cast<char*>(&e), sizeof(e));

        f.close();
        cout << "Empresas.dat generado con 10 empresas.\n";
    }

    // ---------------- Ventas.dat ----------------
    {
        ofstream f("Ventas.dat", ios::binary | ios::trunc);
        if (!f) {
            cerr << "ERROR: No se pudo crear Ventas.dat\n";
            return 1;
        }

        Venta v;

        // Empresa 1: total aprox 500.000
        v.nroEmp = 1;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 40000.0f; // 12 * 40.000 = 480.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 2: total aprox 1.500.000
        v.nroEmp = 2;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 125000.0f; // 12 * 125.000 = 1.500.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 3: total aprox 2.200.000
        v.nroEmp = 3;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 183333.0f; // ~2.200.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 4: 200.000
        v.nroEmp = 4;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 16666.0f; // ~199.992
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 5: 50.000
        v.nroEmp = 5;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 4166.0f; // ~49.992
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 6: 900.000 (no llega al millon)
        v.nroEmp = 6;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 75000.0f; // 900.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 7: 1.050.000 (apenas pasa el millon)
        v.nroEmp = 7;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 87500.0f; // 1.050.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 8: 300.000
        v.nroEmp = 8;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 25000.0f; // 300.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 9: 1.200.000
        v.nroEmp = 9;
        for (int mes = 1; mes <= 12; mes++) {
            v.mes = mes;
            v.importe = 100000.0f; // 1.200.000
            f.write(reinterpret_cast<char*>(&v), sizeof(v));
        }

        // Empresa 10: sin ventas (no escribimos nada)

        f.close();
        cout << "Ventas.dat generado con ventas para empresas 1..9.\n";
    }

    cout << "\n✅ Archivos Empresas.dat y Ventas.dat generados correctamente.\n";
    cout << "Ahora ejecuta G4Ej14.exe para probar el ejercicio.\n";

    return 0;
}
