/*
Id.Programa: G5Ej16.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Actualiza el Tablero de Vuelos y emite listas de pasajeros.
    Archivos requeridos:
      - EMPRESAS.DAT  (ordenado por codigo, max 20)
      - VUELOS.DAT    (max 800, nro vuelo = nro registro 1-based)
      - PASAJEROS.DAT (ordenado por nro. de vuelo repeticion)
    Funciones:
      - Actualiza la cantidad de pasajeros por vuelo
      - Mantiene vuelos en estructura dinamica (lista enlazada) ordenada por hora
      - Muestra Tablero (max 10 vuelos)
      - Emite Lista de Pasajeros por vuelo (con totales de menores, mujeres, total)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <iomanip>
using namespace std;

struct Empresa {
    char codigo[6];
    char nombre[31];
    char domicilio[21];
    char telefono[15];
    char otros[71];
};

struct Vuelo {
    char codigoEmpresa[6];
    char movimiento;   // 'L' o 'S'
    char lugar[31];
    int hora;          // hhmm
    int cantidadPas;   // actualizar
    int plazas;
    char escalas;      // 'S' o 'N'
};

struct Pasajero {
    int nroVuelo;
    int fecha;         // ddmmaa
    char apeNom[21];
    int edad;
    char nacionalidad[21];
    char sexo;
    char doc[16];
};

// Nodo para lista enlazada de vuelos (dinámica)
struct NodoV {
    int nroVuelo; // 1-based
    Vuelo v;
    NodoV* sig;
};

// Utilities
string horaToStr(int hhmm) {
    int hh = hhmm / 100;
    int mm = hhmm % 100;
    char buf[6];
    sprintf(buf, "%02d:%02d", hh, mm);
    return string(buf);
}

int main() {
    cout << fixed << setprecision(2);

    // --- 1) Cargar EMPRESAS.DAT ---
    vector<Empresa> empresas;
    {
        ifstream f("EMPRESAS.DAT", ios::binary);
            if (!f) {
                cout << "No se pudo abrir EMPRESAS.DAT\n";
                return 1;
            }
        Empresa e;
        while (f.read(reinterpret_cast<char*>(&e), sizeof(Empresa))) {
            empresas.push_back(e);
        }
        f.close();
    }

    // --- 2) Cargar VUELOS.DAT ---
    vector<Vuelo> vuelos;
    {
        ifstream f("VUELOS.DAT", ios::binary);
        if (!f) {
            cout << "No se pudo abrir VUELOS.DAT\n";
            return 1;
        }
        Vuelo vv;
        while (f.read(reinterpret_cast<char*>(&vv), sizeof(Vuelo))) {
            vuelos.push_back(vv);
        }
        f.close();
    }

    int nVuelos = (int)vuelos.size();
    if (nVuelos == 0) {
        cout << "No hay vuelos en VUELOS.DAT\n";
        return 1;
    }
    if (nVuelos > 800) nVuelos = 800;

    // Preparar contenedores de pasajeros por vuelo
    vector< vector<Pasajero> > listaPas(nVuelos+1); // 1-based index

    // --- 3) Leer PASAJEROS.DAT y contar por vuelo ---
    {
        ifstream f("PASAJEROS.DAT", ios::binary);
        if (!f) {
            cout << "No se pudo abrir PASAJEROS.DAT\n";
            return 1;
        }
        Pasajero p;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(Pasajero))) {
            if (p.nroVuelo >= 1 && p.nroVuelo <= nVuelos) {
                listaPas[p.nroVuelo].push_back(p);
            }
        }
        f.close();
    }

    // Actualizar cantidadPas en vuelos
    for (int i = 1; i <= nVuelos; ++i) {
        vuelos[i-1].cantidadPas = (int)listaPas[i].size();
    }

    // --- 4) Reescribir VUELOS.DAT con cantidades actualizadas ---
    {
        fstream f("VUELOS.DAT", ios::binary | ios::out | ios::trunc);
        if (!f) {
            cout << "No se pudo reescribir VUELOS.DAT\n";
            return 1;
        }
        for (size_t i = 0; i < vuelos.size(); ++i) {
            f.write(reinterpret_cast<char*>(&vuelos[i]), sizeof(Vuelo));
        }
        f.close();
    }

    // --- 5) Construir lista enlazada dinámica de vuelos ordenada por hora asc ---
    NodoV* cabeza = nullptr;
    for (int i = 1; i <= nVuelos; ++i) {
        NodoV* nodo = new NodoV;
        nodo->nroVuelo = i;
        nodo->v = vuelos[i-1];
        nodo->sig = nullptr;

        // Insertar ordenado por v.hora
        if (!cabeza || nodo->v.hora < cabeza->v.hora) {
            nodo->sig = cabeza;
            cabeza = nodo;
        } else {
            NodoV* p = cabeza;
            while (p->sig && p->sig->v.hora <= nodo->v.hora) p = p->sig;
            nodo->sig = p->sig;
            p->sig = nodo;
        }
    }

    // --- 6) Mostrar Tablero de Vuelos del dia (fecha sistema) ---
    time_t t = time(nullptr);
    tm *lt = localtime(&t);
    char fechaStr[20];
    sprintf(fechaStr, "%02d-%02d-%02d", lt->tm_mday, lt->tm_mon+1, (lt->tm_year+1900)%100);

    cout << "\nTablero de Vuelos del dia : " << fechaStr << "\n";
    cout << "----------------------------------------------------\n";

    // Mostrar hasta 10 vuelos
    NodoV* p = cabeza;
    int mostrados = 0;
    while (p && mostrados < 10) {
        Vuelo &vv = p->v;
        // encontrar nombre de la empresa
        const char* nombreEmp = "(SIN EMP)";
        for (size_t ie = 0; ie < empresas.size(); ++ie) {
            if (strcmp(empresas[ie].codigo, vv.codigoEmpresa) == 0) {
                nombreEmp = empresas[ie].nombre;
                break;
            }
        }

        cout << "Empresa: " << nombreEmp << "  (Cod: " << vv.codigoEmpresa << ")\n";

        if (vv.movimiento == 'L') {
            cout << "  Llegada  #Vuelo: " << setw(3) << p->nroVuelo << "  Hora: " << horaToStr(vv.hora) 
                 << "  Origen: " << vv.lugar << "\n";
        } else {
            cout << "  Salida   #Vuelo: " << setw(3) << p->nroVuelo << "  Hora: " << horaToStr(vv.hora) 
                 << "  Destino: " << vv.lugar << "\n";
        }

        cout << "  Plazas: " << vv.plazas << "  Pasajeros: " << vv.cantidadPas << "  Escalas: " << (vv.escalas=='S' ? "SI" : "NO") << "\n";
        cout << "----------------------------------------------------\n";

        p = p->sig;
        ++mostrados;
    }

    if (mostrados == 0) cout << "(No hay vuelos programados para mostrar)\n";

    // --- 7) Emitir Lista de Pasajeros del dia para todos los vuelos programados (orden por hora asc) ---
    cout << "\nLista de Pasajeros\n";
    cout << "==================\n";

    // Recorrer lista enlazada y mostrar pasajeros por vuelo
    p = cabeza;
    while (p) {
        int nro = p->nroVuelo;
        Vuelo &vv = p->v;

        cout << "\n# Vuelo : " << nro << "\n";
        cout << "Empresa : " << vv.codigoEmpresa << "    ¿Con escalas?: " << (vv.escalas=='S'? "SI":"NO") << "\n";
        cout << "Hora: " << horaToStr(vv.hora) << "\n";

        cout << left << setw(22) << "Apellido, Nombre" << left << setw(20) << "Nacionalidad" << left << setw(18) << "T.Nro.Doc." << "\n";

        int cntMenores = 0;
        int cntMujeres = 0;
        int cntTotal = 0;

        for (size_t i = 0; i < listaPas[nro].size(); ++i) {
            Pasajero &ps = listaPas[nro][i];
            cout << left << setw(22) << ps.apeNom << left << setw(20) << ps.nacionalidad << left << setw(18) << ps.doc << "\n";
            if (ps.edad < 21) ++cntMenores;
            if (ps.sexo == 'F' || ps.sexo == 'f') ++cntMujeres;
            ++cntTotal;
        }
        cout << "\nCantidad de Menores : " << setw(3) << cntMenores << "\n";
        cout << "Cantidad de Mujeres : " << setw(3) << cntMujeres << "\n";
        cout << "Cantidad Total      : " << setw(3) << cntTotal << "\n";

        p = p->sig;
    }

    // --- 8) liberar memoria lista enlazada ---
    while (cabeza) {
        NodoV* tmp = cabeza;
        cabeza = cabeza->sig;
        delete tmp;
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
