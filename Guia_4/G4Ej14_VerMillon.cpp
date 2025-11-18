/*
Id.Programa: G4Ej14_VerMillon.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Visor del archivo Empresas_Millon.dat generado por G4Ej14.cpp
    Muestra las empresas que superan el millon de pesos en ventas anuales.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#pragma pack(push,1)
struct EmpMillon {
    int nroEmp;
    char domicilio[21];
    int codPos;
    double total;
};
#pragma pack(pop)

int main() {
    ifstream f("Empresas_Millon.dat", ios::binary);
    if (!f) {
        cerr << "ERROR: No se pudo abrir Empresas_Millon.dat\n";
        return 1;
    }

    cout << "=== Empresas que superan el millon de pesos en ventas ===\n\n";

    cout << left
         << setw(10) << "Nro.Emp"
         << setw(22) << "Domicilio"
         << setw(8)  << "CodPos"
         << setw(12) << "Imp.Anual"
         << "\n";
    cout << string(10+22+8+12, '-') << "\n";

    EmpMillon e;

    while (f.read(reinterpret_cast<char*>(&e), sizeof(EmpMillon))) {
        cout << left
             << setw(10) << e.nroEmp
             << setw(22) << e.domicilio
             << setw(8)  << e.codPos
             << fixed << setprecision(2)
             << setw(12) << e.total
             << "\n";
    }

    cout << "\nFin del listado.\n";
    return 0;
}