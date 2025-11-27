/*
Id.Programa: G5Ej19.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Asigna divisiones a solicitantes según VACANTES.DAT y SOLICITUDES.DAT.
    - Actualiza VACANTES.DAT (inscriptos).
    - Genera ASIGNACIONES.DAT (registro de solicitud + division asignada).
    - Emite listado por Especialidad y Turno en orden cronológico (orden de solicitudes).
    Notas:
      - Turnos: 'M' -> divisiones 1..40, 'T' -> 41..60, 'N' -> 61..99
      - Si no hay vacante se asigna division = 0.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

struct Vacante {
    int especialidad;
    int division;
    int vacantes;
    int inscriptos;
};

struct Solicitud {
    char legajo[7];
    char apellidoNombre[31];
    int especialidad;
    char turno;
};

struct Asignacion {
    // copia de la solicitud
    char legajo[7];
    char apellidoNombre[31];
    int especialidad;
    char turno;
    int divisionAsignada; // 0 si no encontro vacante
};

// Turno -> rango
void rangoTurno(char turno, int &desde, int &hasta) {
    if (turno == 'M') { desde = 1; hasta = 40; }
    else if (turno == 'T') { desde = 41; hasta = 60; }
    else { desde = 61; hasta = 99; }
}

int main() {
    cout << fixed << setprecision(0);

    // 1) Leer VACANTES.DAT en memoria (tabla)
    vector<Vacante> vacantes;
    {
        ifstream f("VACANTES.DAT", ios::binary);
        if (!f) { cout << "No se pudo abrir VACANTES.DAT\n"; return 1; }
        Vacante v;
        while (f.read(reinterpret_cast<char*>(&v), sizeof(Vacante))) {
            vacantes.push_back(v);
        }
        f.close();
    }

    if (vacantes.empty()) {
        cout << "VACANTES.DAT vacio o faltante.\n";
        return 1;
    }

    // 2) Leer SOLICITUDES.DAT, procesar en orden y generar ASIGNACIONES.DAT
    vector<Asignacion> todasAsignaciones;
    {
        ifstream fsol("SOLICITUDES.DAT", ios::binary);
        if (!fsol) { cout << "No se pudo abrir SOLICITUDES.DAT\n"; return 1; }

        ofstream fasig("ASIGNACIONES.DAT", ios::binary | ios::trunc);
        if (!fasig) { cout << "No se pudo crear ASIGNACIONES.DAT\n"; return 1; }

        Solicitud s;
        while (fsol.read(reinterpret_cast<char*>(&s), sizeof(Solicitud))) {
            Asignacion a;
            strncpy(a.legajo, s.legajo, sizeof(a.legajo)); a.legajo[6] = '\0';
            strncpy(a.apellidoNombre, s.apellidoNombre, sizeof(a.apellidoNombre)); a.apellidoNombre[30] = '\0';
            a.especialidad = s.especialidad;
            a.turno = s.turno;
            a.divisionAsignada = 0; // por defecto

            // buscar vacante disponible dentro del rango de turnos para la especialidad
            int desde, hasta;
            rangoTurno(s.turno, desde, hasta);

            // buscaremos la primer division (menor numero) que coincida con la especialidad y tenga lugar
            int encontradoIndex = -1;
            int menorDivision = 1000;
            for (size_t i = 0; i < vacantes.size(); ++i) {
                if (vacantes[i].especialidad != s.especialidad) continue;
                if (vacantes[i].division < desde || vacantes[i].division > hasta) continue;
                if (vacantes[i].inscriptos < vacantes[i].vacantes) {
                    // preferimos la division de menor numero
                    if (vacantes[i].division < menorDivision) {
                        menorDivision = vacantes[i].division;
                        encontradoIndex = (int)i;
                    }
                }
            }

            if (encontradoIndex >= 0) {
                vacantes[encontradoIndex].inscriptos++;
                a.divisionAsignada = vacantes[encontradoIndex].division;
            } else {
                a.divisionAsignada = 0; // sin vacante
            }

            // grabar registro de asignacion en archivo y en memoria (para listados)
            fasig.write(reinterpret_cast<char*>(&a), sizeof(Asignacion));
            todasAsignaciones.push_back(a);
        }

        fasig.close();
        fsol.close();
        cout << "ASIGNACIONES.DAT generado con " << todasAsignaciones.size() << " registros.\n";
    }

    // 3) Reescribir VACANTES.DAT con inscriptos actualizados
    {
        ofstream f("VACANTES.DAT", ios::binary | ios::trunc);
        if (!f) { cout << "No se pudo reescribir VACANTES.DAT\n"; return 1; }
        for (auto &v : vacantes) f.write(reinterpret_cast<const char*>(&v), sizeof(Vacante));
        f.close();
        cout << "VACANTES.DAT actualizado.\n";
    }

    // 4) Hacer listado por Especialidad y Turno (M,T,N), orden cronológico (orden original)
    cout << "\nListado por Rubro (Especialidad) y Turno (orden cronológico):\n\n";

    // Averiguamos especialidades existentes (tomamos min/max)
    int minEsp = 999, maxEsp = 0;
    for (auto &v : vacantes) {
        if (v.especialidad < minEsp) minEsp = v.especialidad;
        if (v.especialidad > maxEsp) maxEsp = v.especialidad;
    }
    if (minEsp == 999) { cout << "No hay especialidades.\n"; return 1; }

    const char turnos[3] = {'M','T','N'};
    for (int esp = minEsp; esp <= maxEsp; ++esp) {
        // comprobar si existe la especialidad en vacantes (si no, saltar)
        bool existe = false;
        for (auto &v : vacantes) if (v.especialidad == esp) { existe = true; break; }
        if (!existe) continue;

        for (int it = 0; it < 3; ++it) {
            char turno = turnos[it];
            cout << "Especialidad : " << esp << "   Turno : " << turno << "\n";
            cout << left << setw(6) << "Orden" << setw(8) << "Legajo" << setw(35) << "Apellido, Nombre" << setw(8) << "Div." << "\n";

            int orden = 1;
            for (size_t i = 0; i < todasAsignaciones.size(); ++i) {
                auto &a = todasAsignaciones[i];
                if (a.especialidad == esp && a.turno == turno) {
                    cout << left << setw(6) << orden
                         << setw(8) << a.legajo
                         << setw(35) << a.apellidoNombre
                         << setw(8) << a.divisionAsignada
                         << "\n";
                    orden++;
                }
            }
            cout << "\n";
        }
    }

    cout << "Listado finalizado.\n";
    return 0;
}
