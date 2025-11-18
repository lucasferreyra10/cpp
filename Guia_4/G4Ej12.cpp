/*
Id.Programa: G4Ej12.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Ejercicio 12 – Patentes del parque automotor provincial.

    Archivos:
      Vehículos.dat  → Ordenado por código postal + patente
      Importes.dat   → Ordenado por modelo + año
      Infracciones.dat → Ordenado por patente

    El programa:
      1) Pide la cantidad de cuotas (1–12)
      2) Pide fechas de vencimiento (ddmmaaaa)
      3) Imprime para cada vehículo (ordenado por patente): 
           patente, titular, domicilio, CP, infracciones,
           cuotas, importe, fecha de vencimiento.
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// --------------------- ESTRUCTURAS ---------------------

struct Vehiculo {
    int modelo;            // 4 díg.
    int anio;              // 4 díg.
    char patente[7];       // str6 + '\0'
    char titular[41];      // cad40
    char domicilio[41];    // cad40
    int codPostal;         // 4 díg.
};

struct Importe {
    int modelo;            // 4 díg.
    int anio;              // 4 díg.
    float importeAnual;
};

struct Infraccion {
    char patente[7];
    int cantidad;          // 0–999
};

struct Cuota {
    int dia;
    int mes;
    int anio;
};

// ---------------------------------
// Buscar vehículo por patente
// ---------------------------------

bool buscarVehiculo(const char patenteBuscada[7], Vehiculo &out) {
    ifstream fv("Vehiculos.dat", ios::binary);
    if (!fv) {
        cerr << "ERROR: No se pudo abrir Vehiculos.dat\n";
        return false;
    }

    Vehiculo v;
    while (fv.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo))) {
        if (strcmp(v.patente, patenteBuscada) == 0) {
            out = v;
            return true;
        }
    }

    return false;
}

// ---------------------------------
// Buscar importe por modelo + año
// ---------------------------------

bool buscarImporte(int modelo, int anio, float &imp) {
    ifstream fi("Importes.dat", ios::binary);
    if (!fi) {
        cerr << "ERROR: No se pudo abrir Importes.dat\n";
        return false;
    }

    Importe r;
    while (fi.read(reinterpret_cast<char*>(&r), sizeof(Importe))) {
        if (r.modelo == modelo && r.anio == anio) {
            imp = r.importeAnual;
            return true;
        }
    }

    return false;
}

// -------------------- MAIN --------------------

int main() {

    // ❗ Se quitaron las optimizaciones que atrasaban la impresión:
    //
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // --------- 1. Leer cantidad de cuotas ---------
    int cantCuotas;
    cout << "Ingrese cantidad de cuotas (1..12): ";
    cin >> cantCuotas;

    if (cantCuotas < 1 || cantCuotas > 12) {
        cerr << "Cantidad de cuotas invalida.\n";
        return 1;
    }

    // --------- 2. Leer vencimientos ---------
    Cuota venc[12];
    for (int i = 0; i < cantCuotas; i++) {
        cout << "Ingrese vencimiento de cuota " << (i+1) << " (ddmmaaaa): ";
        int fecha;
        cin >> fecha;

        venc[i].dia = fecha / 1000000;
        venc[i].mes = (fecha / 10000) % 100;
        venc[i].anio = fecha % 10000;
    }

    // --------- 3. Procesar Infracciones.dat ---------
    ifstream finf("Infracciones.dat", ios::binary);
    if (!finf) {
        cerr << "ERROR: No se pudo abrir Infracciones.dat\n";
        return 1;
    }

    Infraccion inf;
    Vehiculo veh;
    float importeAnual;

    cout << fixed << setprecision(2);

    while (finf.read(reinterpret_cast<char*>(&inf), sizeof(Infraccion))) {

        // Buscar vehículo
        if (!buscarVehiculo(inf.patente, veh)) {
            cerr << "ADVERTENCIA: Patente " << inf.patente << " no existe en Vehiculos.dat\n";
            continue;
        }

        // Buscar importe anual
        if (!buscarImporte(veh.modelo, veh.anio, importeAnual)) {
            cerr << "ADVERTENCIA: No hay importe para modelo "
                 << veh.modelo << " año " << veh.anio << "\n";
            continue;
        }

        // Calcular importe por cuota
        float impCuota = importeAnual / cantCuotas;

        // -------------------- IMPRIMIR --------------------
        cout << "\nPATENTE : " << inf.patente
             << "   TITULAR : " << veh.titular << "\n";
        cout << "COD.POS.: " << veh.codPostal
             << "   DOMICILIO : " << veh.domicilio
             << "   CANT.INFR.: " << inf.cantidad << "\n\n";

        cout << " CUOTA  IMPORTE   FEC.VTO\n";

        for (int i = 0; i < cantCuotas; i++) {
            cout << " " << setw(2) << setfill('0') << (i+1) << setfill(' ') 
                 << "    " << setw(8) << impCuota
                 << "   " << setw(2) << setfill('0') << venc[i].dia << "/"
                 << setw(2) << venc[i].mes << "/"
                 << setw(4) << venc[i].anio << setfill(' ') << "\n";
        }

        cout << "----------------------------------------------------------\n";
    }

    cout << "\nPROCESO FINALIZADO.\n";

    return 0;
}
