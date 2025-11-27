/*
Id.Programa: G5Ej16Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de archivos de prueba para G5Ej16:
      - EMPRESAS.DAT   (ordenado por codigo)
      - VUELOS.DAT     (cada registro corresponde a un nro. de vuelo = nroRegistro)
      - PASAJEROS.DAT  (ordenado por nro. de vuelo con repeticion)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Empresa
{
    char codigo[6]; // 5 + '\0'
    char nombre[31];
    char domicilio[21];
    char telefono[15];
    char otros[71];
};

struct Vuelo
{
    char codigoEmpresa[6];
    char movimiento; // 'L' o 'S'
    char lugar[31];  // Origen / Destino
    int hora;        // hhmm
    int cantidadPas; // inicialmente 0
    int plazas;      // 3 díg.
    char escalas;    // 'S' o 'N'
};

struct Pasajero
{
    int nroVuelo; // 1-based (coincide con registro en VUELOS.DAT)
    int fecha;    // ddmmaa
    char apeNom[21];
    int edad;
    char nacionalidad[21];
    char sexo; // 'F' o 'M'
    char doc[16];
};

int main()
{
    // === EMPRESAS.DAT ===
    {
        ofstream f("EMPRESAS.DAT", ios::binary);
        Empresa e;

        strcpy(e.codigo, "AA001");
        strcpy(e.nombre, "Aerolineas Uno");
        strcpy(e.domicilio, "Av. 1 100");
        strcpy(e.telefono, "011-1111");
        strcpy(e.otros, "Empresa Nacional");
        f.write((char *)&e, sizeof(Empresa));

        strcpy(e.codigo, "BB002");
        strcpy(e.nombre, "BairesFly");
        strcpy(e.domicilio, "Calle 2 200");
        strcpy(e.telefono, "011-2222");
        strcpy(e.otros, "Privada");
        f.write((char *)&e, sizeof(Empresa));

        strcpy(e.codigo, "CC003");
        strcpy(e.nombre, "Continental");
        strcpy(e.domicilio, "Ruta 3 300");
        strcpy(e.telefono, "011-3333");
        strcpy(e.otros, "Charter");
        f.write((char *)&e, sizeof(Empresa));

        f.close();
        cout << "EMPRESAS.DAT generado.\n";
    }

    // === VUELOS.DAT ===
    // We'll write several flights; their nroVuelo = record index starting at 1
    {
        ofstream f("VUELOS.DAT", ios::binary);

        Vuelo v;

        // Vuelo 1
        strcpy(v.codigoEmpresa, "AA001");
        v.movimiento = 'L';
        strcpy(v.lugar, "Madrid");
        v.hora = 815;
        v.cantidadPas = 0;
        v.plazas = 180;
        v.escalas = 'S';
        f.write((char *)&v, sizeof(Vuelo));

        // Vuelo 2
        strcpy(v.codigoEmpresa, "BB002");
        v.movimiento = 'S';
        strcpy(v.lugar, "Sao Paulo");
        v.hora = 930;
        v.cantidadPas = 0;
        v.plazas = 150;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));

        // 3
        strcpy(v.codigoEmpresa, "AA001");
        v.movimiento = 'L';
        strcpy(v.lugar, "Lima");
        v.hora = 1015;
        v.cantidadPas = 0;
        v.plazas = 200;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));
        // 4
        strcpy(v.codigoEmpresa, "CC003");
        v.movimiento = 'S';
        strcpy(v.lugar, "Montevideo");
        v.hora = 1230;
        v.cantidadPas = 0;
        v.plazas = 120;
        v.escalas = 'S';
        f.write((char *)&v, sizeof(Vuelo));
        // 5
        strcpy(v.codigoEmpresa, "BB002");
        v.movimiento = 'L';
        strcpy(v.lugar, "Bogota");
        v.hora = 1430;
        v.cantidadPas = 0;
        v.plazas = 160;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));
        // 6
        strcpy(v.codigoEmpresa, "AA001");
        v.movimiento = 'S';
        strcpy(v.lugar, "Santiago");
        v.hora = 1630;
        v.cantidadPas = 0;
        v.plazas = 190;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));
        // 7
        strcpy(v.codigoEmpresa, "CC003");
        v.movimiento = 'L';
        strcpy(v.lugar, "Asuncion");
        v.hora = 1815;
        v.cantidadPas = 0;
        v.plazas = 100;
        v.escalas = 'S';
        f.write((char *)&v, sizeof(Vuelo));
        // 8
        strcpy(v.codigoEmpresa, "BB002");
        v.movimiento = 'S';
        strcpy(v.lugar, "Rio");
        v.hora = 2030;
        v.cantidadPas = 0;
        v.plazas = 170;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));
        // 9
        strcpy(v.codigoEmpresa, "AA001");
        v.movimiento = 'L';
        strcpy(v.lugar, "Cordoba");
        v.hora = 2130;
        v.cantidadPas = 0;
        v.plazas = 160;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));
        // 10
        strcpy(v.codigoEmpresa, "CC003");
        v.movimiento = 'S';
        strcpy(v.lugar, "Salta");
        v.hora = 2350;
        v.cantidadPas = 0;
        v.plazas = 90;
        v.escalas = 'N';
        f.write((char *)&v, sizeof(Vuelo));

        f.close();
        cout << "VUELOS.DAT generado (" << 10 << " vuelos).\n";
    }

    // === PASAJEROS.DAT ===
    {
        ofstream f("PASAJEROS.DAT", ios::binary);
        Pasajero p;

        // passengers for flight 1
        p.nroVuelo = 1;
        p.fecha = 121125;
        strcpy(p.apeNom, "Gomez Juan");
        p.edad = 34;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'M';
        strcpy(p.doc, "DNI1234");
        f.write((char *)&p, sizeof(Pasajero));
        p.nroVuelo = 1;
        p.fecha = 121125;
        strcpy(p.apeNom, "Perez Ana");
        p.edad = 19;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'F';
        strcpy(p.doc, "DNI5678");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 2
        p.nroVuelo = 2;
        p.fecha = 121125;
        strcpy(p.apeNom, "Lopez Carlos");
        p.edad = 45;
        strcpy(p.nacionalidad, "Chile");
        p.sexo = 'M';
        strcpy(p.doc, "CI1111");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 3 (several)
        p.nroVuelo = 3;
        p.fecha = 121125;
        strcpy(p.apeNom, "Diaz Laura");
        p.edad = 28;
        strcpy(p.nacionalidad, "Peru");
        p.sexo = 'F';
        strcpy(p.doc, "P12345");
        f.write((char *)&p, sizeof(Pasajero));
        p.nroVuelo = 3;
        p.fecha = 121125;
        strcpy(p.apeNom, "Martinez Jose");
        p.edad = 17;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'M';
        strcpy(p.doc, "DNI9999");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 4
        p.nroVuelo = 4;
        p.fecha = 121125;
        strcpy(p.apeNom, "Sosa Maria");
        p.edad = 52;
        strcpy(p.nacionalidad, "Uruguay");
        p.sexo = 'F';
        strcpy(p.doc, "U4567");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 5 has none (to test zero passengers)
        // flight 6
        p.nroVuelo = 6;
        p.fecha = 121125;
        strcpy(p.apeNom, "Rojas Lucia");
        p.edad = 20;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'F';
        strcpy(p.doc, "DNI2222");
        f.write((char *)&p, sizeof(Pasajero));
        p.nroVuelo = 6;
        p.fecha = 121125;
        strcpy(p.apeNom, "Vega Mario");
        p.edad = 65;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'M';
        strcpy(p.doc, "DNI3333");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 7
        p.nroVuelo = 7;
        p.fecha = 121125;
        strcpy(p.apeNom, "Alvarez Carla");
        p.edad = 30;
        strcpy(p.nacionalidad, "Paraguay");
        p.sexo = 'F';
        strcpy(p.doc, "P8888");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 8
        p.nroVuelo = 8;
        p.fecha = 121125;
        strcpy(p.apeNom, "Fernandez Raul");
        p.edad = 40;
        strcpy(p.nacionalidad, "Brasil");
        p.sexo = 'M';
        strcpy(p.doc, "B7777");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 9
        p.nroVuelo = 9;
        p.fecha = 121125;
        strcpy(p.apeNom, "Morales Ana");
        p.edad = 15;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'F';
        strcpy(p.doc, "DNI4444");
        f.write((char *)&p, sizeof(Pasajero));
        // flight 10
        p.nroVuelo = 10;
        p.fecha = 121125;
        strcpy(p.apeNom, "Cano Pedro");
        p.edad = 29;
        strcpy(p.nacionalidad, "Argentina");
        p.sexo = 'M';
        strcpy(p.doc, "DNI5555");
        f.write((char *)&p, sizeof(Pasajero));

        f.close();
        cout << "PASAJEROS.DAT generado.\n";
    }

    cout << "Generador finalizado.\n";
    return 0;
}
