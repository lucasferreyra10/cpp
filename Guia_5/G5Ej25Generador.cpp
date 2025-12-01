/*
Id.Programa: G5Ej25Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de datos para G5Ej25.
    Crea archivos binarios (sin orden):
      - RESERVAS.DAT : reserva por ciudad/dia (max 1 vuelo por ciudad/dia)
      - PEDIDOS.DAT  : pedidos de clientes (sin orden)
    Formatos binarios:
      RESERVA: codCiudad(3 chars + '\0'), dia(int), horaSalida(int 6 díg.), totalPasajes(int), nroVuelo(int), precio(double)
      PEDIDO : codCiudad(3 chars + '\0'), cantidad(int), dia(int), nroDoc(8 chars + '\0')
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Reserva {
    char codCiudad[4];
    int dia;
    int horaSalida; // hhmmss o hhmm (guardamos como int)
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

void setStr(char *dst, const char *src, size_t n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // RESERVAS.DAT
    {
        ofstream f("RESERVAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear RESERVAS.DAT\n"; return 1; }

        Reserva r;

        setStr(r.codCiudad, "NYC", sizeof(r.codCiudad));
        r.dia = 10;
        r.horaSalida = 100000;   // 10:00:00
        r.totalPasajes = 50;
        r.nroVuelo = 1101;
        r.precio = 500.0;
        f.write((char*)&r, sizeof(r));

        setStr(r.codCiudad, "LON", sizeof(r.codCiudad));
        r.dia = 10;
        r.horaSalida = 120000;   // 12:00:00
        r.totalPasajes = 30;
        r.nroVuelo = 2201;
        r.precio = 800.0;
        f.write((char*)&r, sizeof(r));

        setStr(r.codCiudad, "PAR", sizeof(r.codCiudad));
        r.dia = 11;
        r.horaSalida = 90000;    // CORRECCIÓN: sin 0 inicial -> 09:00:00
        r.totalPasajes = 20;
        r.nroVuelo = 3301;
        r.precio = 700.0;
        f.write((char*)&r, sizeof(r));

        setStr(r.codCiudad, "NYC", sizeof(r.codCiudad));
        r.dia = 11;
        r.horaSalida = 110000;   // 11:00:00
        r.totalPasajes = 10;
        r.nroVuelo = 1102;
        r.precio = 520.0;
        f.write((char*)&r, sizeof(r));

        setStr(r.codCiudad, "MAD", sizeof(r.codCiudad));
        r.dia = 10;
        r.horaSalida = 140000;   // 14:00:00
        r.totalPasajes = 5;
        r.nroVuelo = 4401;
        r.precio = 900.0;
        f.write((char*)&r, sizeof(r));

        f.close();
        cout << "RESERVAS.DAT generado.\n";
    }

    // PEDIDOS.DAT (sin orden)
    {
        ofstream f("PEDIDOS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear PEDIDOS.DAT\n"; return 1; }

        Pedido p;
        // varios pedidos para dia 10 y ciudad NYC (algunos aceptables, otros que provoquen rechazo)
        setStr(p.codCiudad, "NYC", sizeof(p.codCiudad)); p.cantidad = 20; p.dia = 10; setStr(p.nroDoc, "12345678", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p));
        setStr(p.codCiudad, "NYC", sizeof(p.codCiudad)); p.cantidad = 40; p.dia = 10; setStr(p.nroDoc, "23456789", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p)); // posiblemente rechazo si se superan asientos
        setStr(p.codCiudad, "LON", sizeof(p.codCiudad)); p.cantidad = 10; p.dia = 10; setStr(p.nroDoc, "34567890", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p));
        setStr(p.codCiudad, "PAR", sizeof(p.codCiudad)); p.cantidad = 5; p.dia = 11; setStr(p.nroDoc, "45678901", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p));
        setStr(p.codCiudad, "NYC", sizeof(p.codCiudad)); p.cantidad = 10; p.dia = 11; setStr(p.nroDoc, "56789012", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p)); // should be ok (there is 10 seats)
        setStr(p.codCiudad, "MAD", sizeof(p.codCiudad)); p.cantidad = 6; p.dia = 10; setStr(p.nroDoc, "67890123", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p)); // maybe reject (only 5 seats)
        setStr(p.codCiudad, "NYC", sizeof(p.codCiudad)); p.cantidad = 1; p.dia = 10; setStr(p.nroDoc, "78901234", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p));
        setStr(p.codCiudad, "RIO", sizeof(p.codCiudad)); p.cantidad = 2; p.dia = 12; setStr(p.nroDoc, "89012345", sizeof(p.nroDoc)); f.write((char*)&p, sizeof(p)); // ciudad sin reserva -> reject

        f.close();
        cout << "PEDIDOS.DAT generado.\n";
    }

    cout << "Generador G5Ej25 finalizado.\n";
    return 0;
}
