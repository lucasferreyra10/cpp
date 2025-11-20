/*
Id.Programa: G4Ej16.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Control estadístico de infracciones de colectivos.

    Archivos utilizados:
      a) PATENTES.DAT (ordenado por Patente)
         - Patente del colectivo (XXX999)  -> char[6]
         - Número de línea (3 dígitos)     -> int

      b) INFRACCIONES.DAT (infracciones de un mes, sin orden)
         - Día de la infracción (1..31)    -> int
         - Patente del colectivo           -> char[6]
         - Código de infracción (1..99)    -> int

      c) IMPORTES.DAT (99 registros, uno por cada código 1..99)
         - Código de infracción (1..99)    -> int
         - Importe de la infracción        -> double
         - Estado ('H'=Habilitado, 'I'=Inhabilitado)

    Se pide:
      1) Grabar en ERRORES.DAT los registros de INFRACCIONES.DAT
         que tengan:
            - Patente inexistente en PATENTES.DAT
            - Código de infracción inválido o inhabilitado

      2) Imprimir un listado de colectivos con más de 10 infracciones:
            Listado de Infracciones de colectivos con más de 10 infracciones
            Patente Infracciones
            XXX999   999

         (solo si tienen > 10 infracciones válidas).

      3) Para cada línea que haya tenido colectivos con infracción válida,
         imprimir el siguiente listado, ordenado por número de línea:

            Linea 999
             Dia Importe
             99  9999.99

         Donde Importe es la suma total de las infracciones de esa línea
         en ese día (considerando únicamente códigos habilitados).

    Implementación:
      - Se carga PATENTES.DAT en memoria (hasta MAX_PATENTES).
      - Se carga IMPORTES.DAT en dos vectores: importe[1..99] y habilitado[1..99].
      - Se recorre INFRACCIONES.DAT:
          * Se valida patente (búsqueda binaria en PATENTES.DAT).
          * Se valida código y que esté habilitado.
          * Si hay error, se graba el registro en ERRORES.DAT.
          * Si es válido:
              - Se incrementa el contador de infracciones de la patente.
              - Se acumula el importe por línea y día.

      - Luego se emiten:
          * Listado de patentes con > 10 infracciones.
          * Listado de importes diarios por línea.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct RegPatente {
    char patente[7];   // "XXX999" + '\0'
    int linea;         // 3 dígitos
};

struct RegInfraccion {
    int dia;           // 1..31
    char patente[7];   // "XXX999" + '\0'
    int codInfr;       // 1..99
};

struct RegImporte {
    int codigo;        // 1..99
    double importe;
    char estado;       // 'H' o 'I'
};

const int MAX_PATENTES = 10000;
const int MAX_LINEAS   = 1000;  // líneas 0..999
const int MAX_DIAS     = 31;
const int MAX_CODIGO   = 99;

// Búsqueda binaria de patente en vector ordenado por patente
int buscarPatente(RegPatente v[], int n, const char *pat) {
    int izq = 0;
    int der = n - 1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        int cmp = strcmp(v[medio].patente, pat);
        if (cmp == 0) return medio;
        if (cmp < 0)  izq = medio + 1;
        else          der = medio - 1;
    }
    return -1;
}

int main() {
    // 1) Cargar PATENTES.DAT (ordenado por patente)
    RegPatente vecPat[MAX_PATENTES];
    int cantPat = 0;

    ifstream fPat("PATENTES.DAT", ios::binary);
    if (!fPat) {
        cout << "No se pudo abrir PATENTES.DAT" << endl;
        return 1;
    }

    while (cantPat < MAX_PATENTES &&
           fPat.read(reinterpret_cast<char*>(&vecPat[cantPat]), sizeof(RegPatente))) {
        cantPat++;
    }
    fPat.close();

    // 2) Cargar IMPORTES.DAT (códigos 1..99)
    double importe[ MAX_CODIGO + 1 ];
    bool habilitado[ MAX_CODIGO + 1 ];

    for (int i = 0; i <= MAX_CODIGO; i++) {
        importe[i] = 0.0;
        habilitado[i] = false;
    }

    ifstream fImp("IMPORTES.DAT", ios::binary);
    if (!fImp) {
        cout << "No se pudo abrir IMPORTES.DAT" << endl;
        return 1;
    }

    RegImporte regImp;
    while (fImp.read(reinterpret_cast<char*>(&regImp), sizeof(RegImporte))) {
        if (regImp.codigo >= 1 && regImp.codigo <= MAX_CODIGO) {
            importe[regImp.codigo]    = regImp.importe;
            habilitado[regImp.codigo] = (regImp.estado == 'H');
        }
    }
    fImp.close();

    // 3) Preparar estructuras para estadísticas
    //    - Contador de infracciones por patente (paralelo a vecPat)
    int cantInfrPat[MAX_PATENTES];
    for (int i = 0; i < cantPat; i++) {
        cantInfrPat[i] = 0;
    }

    //    - Acumulador de importes por línea y día
    double acumLineaDia[MAX_LINEAS][MAX_DIAS + 1];
    bool lineaConInfraccion[MAX_LINEAS];

    for (int l = 0; l < MAX_LINEAS; l++) {
        lineaConInfraccion[l] = false;
        for (int d = 0; d <= MAX_DIAS; d++) {
            acumLineaDia[l][d] = 0.0;
        }
    }

    // 4) Procesar INFRACCIONES.DAT y grabar errores en ERRORES.DAT
    ifstream fInf("INFRACCIONES.DAT", ios::binary);
    if (!fInf) {
        cout << "No se pudo abrir INFRACCIONES.DAT" << endl;
        return 1;
    }

    ofstream fErr("ERRORES.DAT", ios::binary);
    if (!fErr) {
        cout << "No se pudo crear ERRORES.DAT" << endl;
        return 1;
    }

    RegInfraccion regInf;

    while (fInf.read(reinterpret_cast<char*>(&regInf), sizeof(RegInfraccion))) {
        bool error = false;

        // Validar día
        if (regInf.dia < 1 || regInf.dia > 31) {
            error = true;
        }

        // Validar patente
        int posPat = buscarPatente(vecPat, cantPat, regInf.patente);
        if (posPat == -1) {
            error = true;
        }

        // Validar código
        if (regInf.codInfr < 1 || regInf.codInfr > MAX_CODIGO) {
            error = true;
        } else if (!habilitado[regInf.codInfr]) {
            // Código inválido/inactivo
            error = true;
        }

        if (error) {
            // Grabar registro con error en ERRORES.DAT (misma imagen que INFRACCIONES.DAT)
            fErr.write(reinterpret_cast<char*>(&regInf), sizeof(RegInfraccion));
        } else {
            // Registro válido: actualizar estadísticas
            cantInfrPat[posPat]++;

            int linea = vecPat[posPat].linea;
            if (linea >= 0 && linea < MAX_LINEAS && regInf.dia >= 1 && regInf.dia <= MAX_DIAS) {
                double imp = importe[regInf.codInfr];
                acumLineaDia[linea][regInf.dia] += imp;
                lineaConInfraccion[linea] = true;
            }
        }
    }

    fInf.close();
    fErr.close();

    // 5) Listado de colectivos con más de 10 infracciones
    cout << "Listado de Infracciones de colectivos con mas de 10 infracciones" << endl;
    cout << left << setw(10) << "Patente"
         << right << setw(12) << "Infracciones" << endl;

    for (int i = 0; i < cantPat; i++) {
        if (cantInfrPat[i] > 10) {
            cout << left << setw(10) << vecPat[i].patente
                 << right << setw(12) << cantInfrPat[i] << endl;
        }
    }

    cout << endl;

    // 6) Listado de importes diarios por línea
    cout << fixed << setprecision(2);

    for (int linea = 0; linea < MAX_LINEAS; linea++) {
        if (lineaConInfraccion[linea]) {
            cout << "Linea " << linea << endl;
            cout << " Dia  Importe" << endl;

            for (int d = 1; d <= MAX_DIAS; d++) {
                if (acumLineaDia[linea][d] > 0.0) {
                    cout << setw(3) << d << "  "
                         << setw(10) << acumLineaDia[linea][d] << endl;
                }
            }

            cout << endl;
        }
    }

    return 0;
}