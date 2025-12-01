/*
Id.Programa: G5Ej25.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Procesa RESERVAS.DAT y PEDIDOS.DAT (ambos sin orden).
    - Imprime el listado de rechazos del DIA DE MAXIMO RECHAZO (ordenado por codCiudad).
    - Genera VENTAS.DAT con pedidos aceptados (registro = PEDIDO + campo importe),
      ordenado por dia asc, codCiudad asc.
    Formatos binarios esperados:
      RESERVA: codCiudad[4], dia(int), horaSalida(int), totalPasajes(int), nroVuelo(int), precio(double)
      PEDIDO : codCiudad[4], cantidad(int), dia(int), nroDoc[9]
      VENTA  : codCiudad[4], cantidad(int), dia(int), nroDoc[9], importe(double)
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

struct Reserva {
    char codCiudad[4];
    int dia;
    int horaSalida;
    int totalPasajes;
    int nroVuelo;
    double precio;
};

struct Pedido {
    char codCiudad[4];
    int cantidad;
    int dia;
    char nroDoc[9];
};

struct Venta {
    char codCiudad[4];
    int cantidad;
    int dia;
    char nroDoc[9];
    double importe;
};

struct Rechazo {
    char codCiudad[4];
    int cantidad;
    int dia;
    char nroDoc[9];
};

string keyReserva(const char *cod, int dia) {
    string k = string(cod) + "#" + to_string(dia);
    return k;
}

int main() {
    // 1) Cargar RESERVAS.DAT en tabla (clave codCiudad#dia)
    unordered_map<string, pair<int,double>> tabla; // key -> (asientosDisponibles, precio)
    {
        ifstream f("RESERVAS.DAT", ios::binary);
        if (!f) {
            cerr << "No se pudo abrir RESERVAS.DAT\n";
            return 1;
        }
        Reserva r;
        while (f.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            string k = keyReserva(r.codCiudad, r.dia);
            tabla[k] = make_pair(r.totalPasajes, r.precio);
        }
        f.close();
    }

    // 2) Procesar PEDIDOS.DAT
    vector<Venta> ventas;
    vector<Rechazo> rechazos;
    map<int,int> rechazosPorDia; // dia -> count

    {
        ifstream f("PEDIDOS.DAT", ios::binary);
        if (!f) {
            cerr << "No se pudo abrir PEDIDOS.DAT\n";
            return 1;
        }
        Pedido p;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            string k = keyReserva(p.codCiudad, p.dia);
            auto it = tabla.find(k);
            if (it == tabla.end()) {
                // no existe reserva: rechazo
                Rechazo R;
                strncpy(R.codCiudad, p.codCiudad, sizeof(R.codCiudad)); R.codCiudad[3] = '\0';
                R.cantidad = p.cantidad; R.dia = p.dia;
                strncpy(R.nroDoc, p.nroDoc, sizeof(R.nroDoc)); R.nroDoc[8] = '\0';
                rechazos.push_back(R);
                rechazosPorDia[p.dia]++;
            } else {
                int disponibles = it->second.first;
                double precio = it->second.second;
                if (disponibles >= p.cantidad) {
                    // aceptar
                    Venta v;
                    strncpy(v.codCiudad, p.codCiudad, sizeof(v.codCiudad)); v.codCiudad[3] = '\0';
                    v.cantidad = p.cantidad; v.dia = p.dia;
                    strncpy(v.nroDoc, p.nroDoc, sizeof(v.nroDoc)); v.nroDoc[8] = '\0';
                    v.importe = p.cantidad * precio;
                    ventas.push_back(v);
                    // decrementar disponibilidad
                    it->second.first = disponibles - p.cantidad;
                } else {
                    // rechazo por falta de cupo
                    Rechazo R;
                    strncpy(R.codCiudad, p.codCiudad, sizeof(R.codCiudad)); R.codCiudad[3] = '\0';
                    R.cantidad = p.cantidad; R.dia = p.dia;
                    strncpy(R.nroDoc, p.nroDoc, sizeof(R.nroDoc)); R.nroDoc[8] = '\0';
                    rechazos.push_back(R);
                    rechazosPorDia[p.dia]++;
                }
            }
        }
        f.close();
    }

    // 3) determinar dia con maximo rechazos
    int diaMaxRechazo = -1;
    int maxR = -1;
    for (auto &par : rechazosPorDia) {
        if (par.second > maxR) {
            maxR = par.second;
            diaMaxRechazo = par.first;
        }
    }

    // 4) imprimir listado de rechazos para diaMaxRechazo ordenado por codCiudad
    if (diaMaxRechazo == -1) {
        cout << "No hubo rechazos.\n";
    } else {
        cout << "\nDIA DE MAXIMO RECHAZO " << diaMaxRechazo << "\n";
        cout << "NRO.DOCUMENTO  COD.CIUDAD  CANT.SOLICITADA\n";
        // filtrar y ordenar
        vector<Rechazo> filt;
        for (auto &r : rechazos) if (r.dia == diaMaxRechazo) filt.push_back(r);
        sort(filt.begin(), filt.end(), [](const Rechazo &a, const Rechazo &b){
            int cmp = strcmp(a.codCiudad, b.codCiudad);
            if (cmp != 0) return cmp < 0;
            return strcmp(a.nroDoc, b.nroDoc) < 0;
        });
        for (auto &r : filt) {
            cout << r.nroDoc << "   " << r.codCiudad << "    " << r.cantidad << "\n";
        }
    }

    // 5) grabar VENTAS.DAT ordenado por dia asc, codCiudad asc
    sort(ventas.begin(), ventas.end(), [](const Venta &a, const Venta &b){
        if (a.dia != b.dia) return a.dia < b.dia;
        return strcmp(a.codCiudad, b.codCiudad) < 0;
    });

    {
        ofstream f("VENTAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear VENTAS.DAT\n"; return 1; }
        for (auto &v : ventas) f.write(reinterpret_cast<char*>(&v), sizeof(v));
        f.close();
    }

    cout << "\nProceso finalizado. Ventas grabadas: " << ventas.size() << ". Rechazos totales: " << rechazos.size() << ".\n";
    return 0;
}