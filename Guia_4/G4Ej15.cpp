/*
Id.Programa: G4Ej15.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Actualiza las deudas de contribuyentes de una Municipalidad y emite:
      1) Listado de control de cobranza por cada pago registrado.
      2) Total recaudado por zona Municipal.

    Archivos utilizados:
      a) DEUDORES.DAT (sin orden)
         - Cod. Contribuyente (5 caracteres)
         - Año de la cuota (1998..2007)
         - Mes de la cuota (1..12)
         - Importe de la cuota (double)
         - Estado ('A' = Adeuda, 'C' = Cancelada)
         - Fecha de cobro (aaaammdd, int)

      b) DATOPERS.DAT (<= 8000 registros, ordenado por contribuyente)
         - Cod. Contribuyente (5 caracteres)
         - Apellido y Nombre (45 caracteres)
         - Domicilio (45 caracteres)
         - Cod. de zona Municipal (4 caracteres)

      c) COBROMES.DAT (ordenado por fecha y luego por contribuyente)
         - Cod. Contribuyente (5 caracteres)
         - Año de la cuota
         - Mes de la cuota
         - Fecha de cobro (aaaammdd, int)

    Tareas:
      1) Actualizar en DEUDORES.DAT las cuotas pagadas según COBROMES.DAT.
         - Si la cuota estaba 'A' pasa a 'C' y se graba la fecha de cobro.
         - Si ya estaba 'C', se informa error (cuota ya pagada).

      2) Imprimir listado de control de cobranza:
         Contrib. Ape. y Nom.                      Año Mes Importe   Situac.
         XXXXX   X(45)                             9999 99 99999.99  P/E

         Situac.:
           P = Pago aceptado
           E = Error (cuota ya cancelada anteriormente)

      3) Imprimir total recaudado por zona Municipal, ordenado por código:
         Cod. Zona   Importe Recaudado

    Restricción:
      - Se dispone de 4 Mbytes de memoria estática.
      - Se carga en memoria DATOPERS.DAT (<= 8000) y un vector de totales por zona.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Deudor {
    char codContrib[6];   // 5 car. + '\0'
    int anio;             // 1998..2007
    int mes;              // 1..12
    double importe;
    char estado;          // 'A' o 'C'
    int fechaCobro;       // aaaammdd
};

struct DatoPers {
    char codContrib[6];   // 5 car. + '\0'
    char apeNom[46];      // 45 car. + '\0'
    char domicilio[46];   // 45 car. + '\0'
    char codZona[5];      // 4 car. + '\0'
};

struct CobroMes {
    char codContrib[6];   // 5 car. + '\0'
    int anio;
    int mes;
    int fechaCobro;       // aaaammdd
};

struct ZonaTotal {
    char codZona[5];      // 4 car. + '\0'
    double total;
};

const int MAX_DATOPERS = 8000;
const int MAX_ZONAS    = 8000;

// Busca contribuyente en vector ordenado de DatoPers (búsqueda binaria).
int buscarDatoPers(DatoPers v[], int n, const char *cod) {
    int izq = 0;
    int der = n - 1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        int cmp = strcmp(v[medio].codContrib, cod);
        if (cmp == 0) {
            return medio;
        } else if (cmp < 0) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    return -1; // no encontrado
}

// Busca índice de zona en vector, si no existe la crea (si hay lugar).
int buscarOCrearZona(ZonaTotal zonas[], int &cantZonas, const char *codZona) {
    // Buscar línea
    for (int i = 0; i < cantZonas; i++) {
        if (strcmp(zonas[i].codZona, codZona) == 0) {
            return i;
        }
    }
    // No está, crear nueva
    if (cantZonas < MAX_ZONAS) {
        strcpy(zonas[cantZonas].codZona, codZona);
        zonas[cantZonas].total = 0.0;
        cantZonas++;
        return cantZonas - 1;
    }
    // Si se llena (muy improbable), no acumula
    return -1;
}

// Ordena el vector de zonas por código (simple burbujeo / inserción)
void ordenarZonasPorCodigo(ZonaTotal zonas[], int cantZonas) {
    for (int i = 0; i < cantZonas - 1; i++) {
        for (int j = i + 1; j < cantZonas; j++) {
            if (strcmp(zonas[j].codZona, zonas[i].codZona) < 0) {
                ZonaTotal aux = zonas[i];
                zonas[i] = zonas[j];
                zonas[j] = aux;
            }
        }
    }
}

int main() {
    // 1) Cargar DATOPERS.DAT en memoria
    DatoPers vecDP[MAX_DATOPERS];
    int cantDP = 0;

    ifstream fDato("DATOPERS.DAT", ios::binary);
    if (!fDato) {
        cout << "No se pudo abrir el archivo DATOPERS.DAT" << endl;
        return 1;
    }

    while (cantDP < MAX_DATOPERS &&
           fDato.read(reinterpret_cast<char*>(&vecDP[cantDP]), sizeof(DatoPers))) {
        cantDP++;
    }
    fDato.close();

    // 2) Abrir DEUDORES.DAT para lectura/escritura
    fstream fDeu("DEUDORES.DAT", ios::binary | ios::in | ios::out);
    if (!fDeu) {
        cout << "No se pudo abrir el archivo DEUDORES.DAT" << endl;
        return 1;
    }

    // 3) Abrir COBROMES.DAT para leer pagos
    ifstream fCob("COBROMES.DAT", ios::binary);
    if (!fCob) {
        cout << "No se pudo abrir el archivo COBROMES.DAT" << endl;
        return 1;
    }

    // Vector de totales por zona
    ZonaTotal zonas[MAX_ZONAS];
    int cantZonas = 0;

    // Encabezado del listado de control de cobranza
    cout << "Listado de control de cobranza" << endl;
    cout << left << setw(8)  << "Contrib."
         << left << setw(47) << "Ape. y Nom."
         << right << setw(6) << "Anio"
         << setw(5)         << "Mes"
         << setw(12)        << "Importe"
         << setw(9)         << "Situac."
         << endl;

    CobroMes cob;

    while (fCob.read(reinterpret_cast<char*>(&cob), sizeof(CobroMes))) {

        // Buscar datos personales del contribuyente
        int posDP = buscarDatoPers(vecDP, cantDP, cob.codContrib);
        const char *apeNom = (posDP >= 0) ? vecDP[posDP].apeNom : "DESCONOCIDO";
        const char *codZona = (posDP >= 0) ? vecDP[posDP].codZona : "";

        // Buscar la cuota en DEUDORES.DAT
        fDeu.clear();
        fDeu.seekg(0, ios::beg);

        Deudor deu;
        bool encontrado = false;
        streampos posRegistro;

        while (fDeu.read(reinterpret_cast<char*>(&deu), sizeof(Deudor))) {
            if (strcmp(deu.codContrib, cob.codContrib) == 0 &&
                deu.anio == cob.anio &&
                deu.mes  == cob.mes) {
                encontrado = true;
                posRegistro = fDeu.tellg() - static_cast<streamoff>(sizeof(Deudor));
                break;
            }
        }

        char situacion = 'E';
        double importeListado = 0.0;

        if (encontrado) {
            importeListado = deu.importe;

            if (deu.estado == 'A') {
                // Pago aceptado
                situacion = 'P';
                deu.estado = 'C';
                deu.fechaCobro = cob.fechaCobro;

                // Actualizar registro en DEUDORES.DAT
                fDeu.clear();
                fDeu.seekp(posRegistro, ios::beg);
                fDeu.write(reinterpret_cast<char*>(&deu), sizeof(Deudor));
                fDeu.flush();

                // Acumular en la zona correspondiente
                if (posDP >= 0) {
                    int idxZona = buscarOCrearZona(zonas, cantZonas, codZona);
                    if (idxZona >= 0) {
                        zonas[idxZona].total += deu.importe;
                    }
                }
            } else {
                // Error: cuota ya cancelada anteriormente
                situacion = 'E';
            }
        } else {
            // No se encontró la cuota: también se considera error
            situacion = 'E';
            importeListado = 0.0;
        }

        // Imprimir línea del control de cobranza
        cout << left << setw(8)  << cob.codContrib
             << left << setw(47) << apeNom
             << right << setw(6) << cob.anio
             << setw(5)         << cob.mes
             << setw(12)        << fixed << setprecision(2) << importeListado
             << setw(9)         << situacion
             << endl;
    }

    fCob.close();
    fDeu.close();

    // Ordenar zonas por código
    ordenarZonasPorCodigo(zonas, cantZonas);

    // Listado de recaudación por zona
    cout << endl;
    cout << "Total recaudado por zona Municipal" << endl;
    cout << left << setw(10) << "Cod. Zona"
         << right << setw(15) << "Importe Recaudado" << endl;

    cout << fixed << setprecision(2);
    for (int i = 0; i < cantZonas; i++) {
        cout << left << setw(10) << zonas[i].codZona
             << right << setw(15) << zonas[i].total
             << endl;
    }

    return 0;
}
