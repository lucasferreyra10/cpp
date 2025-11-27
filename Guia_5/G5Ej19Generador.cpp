/*
Id.Programa: G5Ej19Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de archivos de prueba para el Ej.19:
      - VACANTES.DAT   (ordenado por Especialidad y División)
      - SOLICITUDES.DAT (orden cronológico)
    Estructuras fijas (binario).
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Vacante {
    int especialidad;   // 1..9
    int division;       // 1..99
    int vacantes;       // <=99
    int inscriptos;     // <=99 (inicial 0)
};

struct Solicitud {
    char legajo[7];     // 6 dígitos + '\0'
    char apellidoNombre[31];
    int especialidad;
    char turno;         // 'M','T','N'
};

// helper
void setStr(char *dst, const char *src, size_t n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // Generar VACANTES.DAT
    {
        ofstream f("VACANTES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear VACANTES.DAT\n"; return 1; }

        // Para el ejemplo creamos especialidades 1..4 con al menos una division por turno
        // Las divisiones elegidas: Matutino (1,2), Tarde (41), Noche (61)
        Vacante v;

        // Espec 1
        v.especialidad = 1; v.division = 1; v.vacantes = 30; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 1; v.division = 41; v.vacantes = 25; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 1; v.division = 61; v.vacantes = 20; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));

        // Espec 2
        v.especialidad = 2; v.division = 2; v.vacantes = 28; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 2; v.division = 42; v.vacantes = 18; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 2; v.division = 62; v.vacantes = 15; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));

        // Espec 3
        v.especialidad = 3; v.division = 3; v.vacantes = 20; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 3; v.division = 43; v.vacantes = 20; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 3; v.division = 63; v.vacantes = 20; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));

        // Espec 4
        v.especialidad = 4; v.division = 4; v.vacantes = 25; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 4; v.division = 44; v.vacantes = 25; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));
        v.especialidad = 4; v.division = 64; v.vacantes = 10; v.inscriptos = 0; f.write((char*)&v, sizeof(Vacante));

        f.close();
        cout << "VACANTES.DAT generado.\n";
    }

    // Generar SOLICITUDES.DAT (orden cronológico)
    {
        ofstream f("SOLICITUDES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear SOLICITUDES.DAT\n"; return 1; }

        Solicitud s;
        setStr(s.legajo, "000001", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Perez, Juan", sizeof(s.apellidoNombre));
        s.especialidad = 1; s.turno = 'M'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000002", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Gomez, Maria", sizeof(s.apellidoNombre));
        s.especialidad = 1; s.turno = 'T'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000003", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Lopez, Ana", sizeof(s.apellidoNombre));
        s.especialidad = 1; s.turno = 'M'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000004", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Martinez, Carlos", sizeof(s.apellidoNombre));
        s.especialidad = 2; s.turno = 'N'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000005", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Diaz, Lucia", sizeof(s.apellidoNombre));
        s.especialidad = 2; s.turno = 'T'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000006", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Fernandez, Pedro", sizeof(s.apellidoNombre));
        s.especialidad = 3; s.turno = 'M'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000007", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Ruiz, Carla", sizeof(s.apellidoNombre));
        s.especialidad = 1; s.turno = 'M'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000008", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Vargas, Diego", sizeof(s.apellidoNombre));
        s.especialidad = 4; s.turno = 'N'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000009", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Sanchez, Lola", sizeof(s.apellidoNombre));
        s.especialidad = 3; s.turno = 'T'; f.write((char*)&s, sizeof(Solicitud));

        // algunos más para testear asignaciones y faltas de vacantes
        setStr(s.legajo, "000010", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Molina, Raul", sizeof(s.apellidoNombre));
        s.especialidad = 1; s.turno = 'M'; f.write((char*)&s, sizeof(Solicitud));

        setStr(s.legajo, "000011", sizeof(s.legajo));
        setStr(s.apellidoNombre, "Quispe, Ana", sizeof(s.apellidoNombre));
        s.especialidad = 2; s.turno = 'T'; f.write((char*)&s, sizeof(Solicitud));

        f.close();
        cout << "SOLICITUDES.DAT generado.\n";
    }

    cout << "Generador G5Ej19 finalizado.\n";
    return 0;
}
