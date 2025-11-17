/*
Id.Programa: G4Ej06.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Proceso con técnica de Corte de Control.
    Archivo: Examenes.Dat (binario, ordenado por Universidad y Facultad).

    Campos:
      - Codigo de Universidad: str5
      - Codigo de Facultad   : str5
      - Nro. Legajo          : int (7 dígitos)
      - Apellido Nombre      : cad30
      - Nota                 : int (2 dígitos)

    Se emite:
      Listado de exámenes a alumnos APROBADOS (nota >= 4) por
      Universidad y Facultad, con:

      * Por Facultad:
          *Universidad: X(5)
          **Facultad: X(5)
          Nro.Legajo  Nota
            9(7)      99
          **Cantidad de inscriptos: 9(4)
          **Cantidad de aprobados: 9(4)

      * Por Universidad:
          *Cantidad de inscriptos: 9(5)
          *Cantidad de aprobados: 9(5)

      * Total general:
          Cantidad de inscriptos: 9(6)
          Cantidad de aprobados: 9(6)

    Observacion: Se aprueba con nota >= 4.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Examen {
    char codUniv[6];   // str5 + '\0'
    char codFac[6];    // str5 + '\0'
    int  legajo;       // 7 dígitos
    char apeNom[31];   // Apellido y nombre (30) + '\0'
    int  nota;         // 2 dígitos (0..99)
};

// Función de lectura con "look ahead"
bool leerExamen(ifstream& arch, Examen& ex) {
    return static_cast<bool>(
        arch.read(reinterpret_cast<char*>(&ex), sizeof(ex))
    );
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream arch("Examenes.Dat", ios::binary);
    if (!arch) {
        cerr << "❌ No se pudo abrir el archivo Examenes.Dat\n";
        return 1;
    }

    cout << "Listado Examenes a alumnos aprobados en Universidades-Facultades\n";

    Examen reg;
    bool hayDatos = leerExamen(arch, reg);

    if (!hayDatos) {
        cout << "\n(No hay registros en el archivo).\n";
        return 0;
    }

    // Totales generales
    long totInscGral = 0;
    long totAprobGral = 0;

    while (hayDatos) {
        // Corte por Universidad
        char univActual[6];
        strcpy(univActual, reg.codUniv);

        long inscUniv = 0;
        long aprobUniv = 0;

        cout << "\n*Universidad: " << univActual << "\n";

        while (hayDatos && strcmp(reg.codUniv, univActual) == 0) {
            // Corte por Facultad dentro de Universidad
            char facActual[6];
            strcpy(facActual, reg.codFac);

            long inscFac = 0;
            long aprobFac = 0;

            cout << "\n**Facultad: " << facActual << "\n";
            cout << "Nro.Legajo  Nota\n";

            // Procesar todos los registros de ESTA facultad de ESTA universidad
            while (hayDatos &&
                   strcmp(reg.codUniv, univActual) == 0 &&
                   strcmp(reg.codFac, facActual) == 0) {

                // Cada registro cuenta como inscripto
                inscFac++;
                inscUniv++;
                totInscGral++;

                // Aprobado si nota >= 4
                if (reg.nota >= 4) {
                    aprobFac++;
                    aprobUniv++;
                    totAprobGral++;

                    // Mostrar sólo aprobados
                    cout << setw(9) << reg.legajo
                         << "  " << setw(2) << reg.nota << "\n";
                }

                // Avanzar al siguiente registro
                hayDatos = leerExamen(arch, reg);
            }

            // Fin de facultad
            cout << "**Cantidad de inscriptos: " << setw(4) << inscFac << "\n";
            cout << "**Cantidad de aprobados: " << setw(4) << aprobFac << "\n";
        }

        // Fin de universidad
        cout << "\n*Cantidad de inscriptos: " << setw(5) << inscUniv << "\n";
        cout << "*Cantidad de aprobados: " << setw(5) << aprobUniv << "\n";
    }

    // Totales generales
    cout << "\nCantidad de inscriptos: " << setw(6) << totInscGral << "\n";
    cout << "Cantidad de aprobados: " << setw(6) << totAprobGral << "\n";

    arch.close();
    return 0;
}
