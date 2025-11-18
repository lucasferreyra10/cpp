/*
Id.Programa: G4Ej14.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    D.G.I. - Muestreo de ventas de empresas.

    Archivos:
      a) Empresas.dat:
         Nro.Empresa (1..300000), Domicilio(cad20), RazonSocial(cad30),
         Cod.Pos.(4 dig.), Localidad(cad30).
         Relacion 1 a 1 entre Nro.Empresa y direccion en disco
         => registro nro N se ubica en (N-1)*sizeof(Empresa).

      b) Ventas.dat (ordenado por Nro.Empresa y mes):
         Nro.Empresa, NroMes(1..12), Importe(real).

    Se pide:
      1) Imprimir las 100 empresas con mayor importe anual de ventas
         en orden decreciente de importe:
         Nro.Empresa Domicilio Localidad Cod.Pos. Importe anual

      2) Para las empresas con importe anual > 1.000.000,
         generar un archivo ordenado por codigo postal con:
         Nro.Empresa, Domicilio, Importe venta anual.
         (No habrá mas de 5000 empresas.)
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// -------------------- Constantes --------------------

const int MAX_EMPRESAS   = 300000;
const double CORTE_MILLON = 1000000.0;

// -------------------- Estructuras --------------------

// Empaquetamos para que coincida EXACTO con lo que genera G4Ej14_GenerarDatos
#pragma pack(push,1)
struct Empresa {
    int  nroEmp;
    char domicilio[21];   // 20 + '\0'
    char razon[31];       // 30 + '\0'
    int  codPos;
    char localidad[31];   // 30 + '\0'
};

struct EmpMillon {
    int  nroEmp;
    char domicilio[21];   // 20 + '\0'
    int  codPos;
    double total;
};
#pragma pack(pop)

struct Venta {
    int   nroEmp;
    int   mes;
    float importe;
};

struct EmpTotal {
    int    nroEmp;
    double total;
};

// -------------------- main --------------------

int main() {
    // ---------- 1) Leer Ventas.dat y acumular totales por empresa ----------

    ifstream fVentas("Ventas.dat", ios::binary);
    if (!fVentas) {
        cerr << "ERROR: No se pudo abrir Ventas.dat\n";
        return 1;
    }

    static double totales[MAX_EMPRESAS + 1];
    static bool   tieneVentas[MAX_EMPRESAS + 1];

    for (int i = 0; i <= MAX_EMPRESAS; ++i) {
        totales[i] = 0.0;
        tieneVentas[i] = false;
    }

    Venta v;
    while (fVentas.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
        if (v.nroEmp >= 1 && v.nroEmp <= MAX_EMPRESAS) {
            totales[v.nroEmp] += v.importe;
            tieneVentas[v.nroEmp] = true;
        } else {
            cerr << "ADVERTENCIA: Nro.Empresa fuera de rango en Ventas.dat: "
                 << v.nroEmp << "\n";
        }
    }

    fVentas.close();

    // ---------- 2) Construir vector de empresas con total > 0 ----------

    vector<EmpTotal> lista;
    lista.reserve(5000);

    for (int i = 1; i <= MAX_EMPRESAS; ++i) {
        if (tieneVentas[i] && totales[i] > 0.0) {
            EmpTotal et;
            et.nroEmp = i;
            et.total  = totales[i];
            lista.push_back(et);
        }
    }

    if (lista.empty()) {
        cerr << "No hay empresas con ventas registradas.\n";
        return 0;
    }

    // ---------- 3) Ordenar por total anual (decreciente) ----------

    sort(lista.begin(), lista.end(),
         [](const EmpTotal& a, const EmpTotal& b) {
             return a.total > b.total; // mayor a menor
         });

    // ---------- 4) Abrir Empresas.dat para acceso directo ----------

    fstream fEmp("Empresas.dat", ios::in | ios::binary);
    if (!fEmp) {
        cerr << "ERROR: No se pudo abrir Empresas.dat\n";
        return 1;
    }

    // ---------- 5) Imprimir TOP 100 empresas por importe anual ----------

    cout << "=== Top 100 Empresas por importe anual de ventas ===\n\n";
    cout << left
         << setw(10) << "Nro.Emp"
         << setw(22) << "Domicilio"
         << setw(22) << "Localidad"
         << setw(8)  << "CodPos"
         << setw(12) << "Imp.Anual"
         << "\n";
    cout << string(10+22+22+8+12, '-') << "\n";

    int limite = static_cast<int>(lista.size());
    if (limite > 100) limite = 100;

    Empresa e;
    cout << fixed << setprecision(2);

    for (int i = 0; i < limite; ++i) {
        int nro = lista[i].nroEmp;

        streamoff pos = static_cast<streamoff>(nro - 1) * sizeof(Empresa);
        fEmp.seekg(pos, ios::beg);
        if (!fEmp.read(reinterpret_cast<char*>(&e), sizeof(Empresa))) {
            cerr << "ADVERTENCIA: No se pudo leer Empresa nro " << nro << "\n";
            continue;
        }

        cout << left
             << setw(10) << nro
             << setw(22) << e.domicilio
             << setw(22) << e.localidad
             << setw(8)  << e.codPos
             << setw(12) << lista[i].total
             << "\n";
    }

    // ---------- 6) Empresas con ventas > 1.000.000  ----------

    vector<EmpMillon> vecMillon;
    vecMillon.reserve(5000);

    for (const auto& et : lista) {
        if (et.total > CORTE_MILLON) {
            int nro = et.nroEmp;
            streamoff pos = static_cast<streamoff>(nro - 1) * sizeof(Empresa);
            fEmp.seekg(pos, ios::beg);
            if (!fEmp.read(reinterpret_cast<char*>(&e), sizeof(Empresa))) {
                cerr << "ADVERTENCIA: No se pudo leer Empresa nro " << nro << " para millon.\n";
                continue;
            }

            EmpMillon em;
            em.nroEmp = nro;
            strncpy(em.domicilio, e.domicilio, 20);
            em.domicilio[20] = '\0';
            em.codPos = e.codPos;
            em.total  = et.total;
            vecMillon.push_back(em);
        }
    }

    fEmp.close();

    if (!vecMillon.empty()) {
        // Ordenar por codigo postal y luego por nroEmp
        sort(vecMillon.begin(), vecMillon.end(),
             [](const EmpMillon& a, const EmpMillon& b) {
                 if (a.codPos != b.codPos) return a.codPos < b.codPos;
                 return a.nroEmp < b.nroEmp;
             });

        ofstream fMill("Empresas_Millon.dat", ios::binary | ios::trunc);
        if (!fMill) {
            cerr << "ERROR: No se pudo crear Empresas_Millon.dat\n";
            return 1;
        }

        for (const auto& em : vecMillon) {
            fMill.write(reinterpret_cast<const char*>(&em), sizeof(EmpMillon));
        }

        fMill.close();

        cout << "\nSe genero Empresas_Millon.dat con "
             << vecMillon.size()
             << " empresas que superan el millon.\n";
    } else {
        cout << "\nNo hay empresas que superen el millon de pesos.\n";
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
