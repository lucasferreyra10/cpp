/*
Id.Programa: G5Ej22Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de archivos de prueba para el Ej.22.
    Genera:
      - ASISTENCIAS.DAT  (asistencias regulares por materia)
      - NOTAS.DAT        (notas de parciales)
      - TRABPRAC.DAT     (trabajos prácticos previamente aprobados)
    Formatos (binario):
      ASISTENCIA: legajo(6), codMateria(4)
      NOTA: nroCurso(int2), codMateria(4), legajo(6), nota1(int), nota2(int), fechaFirma(int ddmmaa)
      TRABPRAC: legajo(6), codMateria(4), fechaFirma(int ddmmaa), nroCurso(int2)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Asistencia {
    char legajo[7];      // 6 + '\0'
    char codMateria[5];  // 4 + '\0'
};

struct Nota {
    short nroCurso;      // 2 díg.
    char codMateria[5];
    char legajo[7];
    int nota1;
    int nota2;
    int fechaFirma;      // ddmmaa, 0 si no firmó
};

struct TrabPrac {
    char legajo[7];
    char codMateria[5];
    int fechaFirma;      // ddmmaa
    short nroCurso;
};

void setStr(char *dst, const char *src, size_t n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // ASISTENCIAS.DAT
    {
        ofstream f("ASISTENCIAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear ASISTENCIAS.DAT\n"; return 1; }

        Asistencia a;

        // alumnos con regularidad para M101 and M102
        setStr(a.legajo, "000001", sizeof(a.legajo));
        setStr(a.codMateria, "M101", sizeof(a.codMateria)); f.write((char*)&a, sizeof(a));
        setStr(a.legajo, "000001", sizeof(a.legajo));
        setStr(a.codMateria, "M102", sizeof(a.codMateria)); f.write((char*)&a, sizeof(a));

        setStr(a.legajo, "000002", sizeof(a.legajo));
        setStr(a.codMateria, "M101", sizeof(a.codMateria)); f.write((char*)&a, sizeof(a));

        setStr(a.legajo, "000003", sizeof(a.legajo));
        setStr(a.codMateria, "M103", sizeof(a.codMateria)); f.write((char*)&a, sizeof(a));

        // alumno 4 no tiene regularidad (to test)
        setStr(a.legajo, "000004", sizeof(a.legajo));
        setStr(a.codMateria, "M101", sizeof(a.codMateria)); // not present -> we'll not add to test missing
        // intentionally not writing for 000004 to simulate no regularidad

        f.close();
        cout << "ASISTENCIAS.DAT generado.\n";
    }

    // NOTAS.DAT (incluye casos correctos y errores)
    {
        ofstream f("NOTAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear NOTAS.DAT\n"; return 1; }

        Nota n;

        // 1) Correcto: legajo 000001 materia M101, aprobó parciales, fecha ok
        n.nroCurso = 1; setStr(n.codMateria, "M101", sizeof(n.codMateria)); setStr(n.legajo, "000001", sizeof(n.legajo));
        n.nota1 = 7; n.nota2 = 8; n.fechaFirma = 150721; f.write((char*)&n, sizeof(n));

        // 2) Error: desaprobó primer parcial (nota1 < 6)
        n.nroCurso = 1; setStr(n.codMateria, "M101", sizeof(n.codMateria)); setStr(n.legajo, "000002", sizeof(n.legajo));
        n.nota1 = 4; n.nota2 = 9; n.fechaFirma = 160721; f.write((char*)&n, sizeof(n));

        // 3) Error: sin fecha de firma (fechaFirma == 0)
        n.nroCurso = 2; setStr(n.codMateria, "M103", sizeof(n.codMateria)); setStr(n.legajo, "000003", sizeof(n.legajo));
        n.nota1 = 8; n.nota2 = 7; n.fechaFirma = 0; f.write((char*)&n, sizeof(n));

        // 4) Error: sin regularidad (legajo 000004 no figura en ASISTENCIAS para M101)
        n.nroCurso = 1; setStr(n.codMateria, "M101", sizeof(n.codMateria)); setStr(n.legajo, "000004", sizeof(n.legajo));
        n.nota1 = 9; n.nota2 = 9; n.fechaFirma = 170721; f.write((char*)&n, sizeof(n));

        // 5) Correcto: already in TRABPRAC (to test duplicates handling)
        n.nroCurso = 1; setStr(n.codMateria, "M102", sizeof(n.codMateria)); setStr(n.legajo, "000001", sizeof(n.legajo));
        n.nota1 = 8; n.nota2 = 6; n.fechaFirma = 140721; f.write((char*)&n, sizeof(n));

        f.close();
        cout << "NOTAS.DAT generado.\n";
    }

    // TRABPRAC.DAT (previos aprobados)
    {
        ofstream f("TRABPRAC.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear TRABPRAC.DAT\n"; return 1; }

        TrabPrac t;
        setStr(t.legajo, "000001", sizeof(t.legajo));
        setStr(t.codMateria, "M102", sizeof(t.codMateria));
        t.fechaFirma = 010721;
        t.nroCurso = 1;
        f.write((char*)&t, sizeof(t));

        f.close();
        cout << "TRABPRAC.DAT generado.\n";
    }

    cout << "Generador G5Ej22 finalizado.\n";
    return 0;
}
