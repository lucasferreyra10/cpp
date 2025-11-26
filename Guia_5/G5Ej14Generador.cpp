/*
Id.Programa: G5Ej14Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Genera los archivos:
      - DJ.DAT (declaración jurada)
      - BIENES.DAT (cabeceras + bienes)
      - IMPUESTOS.DAT (rangos de impuestos)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct DJ {
    char nombre[30];
    char direccion[30];
    char localidad[20];
    char cp[5];
    char telefono[15];
    char documento[12];
    float totalBienes;  // inicialmente cero
};

struct Bien {
    char documento[12];
    char tipoBien[20];
    float importe;
    char descripcion[50];
};

struct Impuesto {
    float monto;
    int porcentaje;
};

int main() {
    // === Archivo DJ.DAT ===
    {
        ofstream f("DJ.DAT", ios::binary);
        DJ d;

        strcpy(d.nombre, "Gomez Juan");
        strcpy(d.direccion, "Calle 123");
        strcpy(d.localidad, "Moron");
        strcpy(d.cp, "1708");
        strcpy(d.telefono, "4444-1111");
        strcpy(d.documento, "DNI1234");
        d.totalBienes = 0;
        f.write((char*)&d, sizeof(d));

        strcpy(d.nombre, "Lopez Ana");
        strcpy(d.direccion, "San Martin 55");
        strcpy(d.localidad, "Castelar");
        strcpy(d.cp, "1712");
        strcpy(d.telefono, "4444-2222");
        strcpy(d.documento, "DNI5678");
        d.totalBienes = 0;
        f.write((char*)&d, sizeof(d));

        f.close();
    }

    // === Archivo BIENES.DAT ===
    {
        ofstream f("BIENES.DAT", ios::binary);
        Bien b;

        // Cabecera + bienes para DNI1234
        strcpy(b.documento, "DNI1234");
        strcpy(b.tipoBien, "*");
        b.importe = 0;
        strcpy(b.descripcion, "Cabecera");
        f.write((char*)&b, sizeof(b));

        strcpy(b.tipoBien, "Auto");
        b.importe = 1500000;
        strcpy(b.descripcion, "Ford Focus 2018");
        f.write((char*)&b, sizeof(b));

        strcpy(b.tipoBien, "Casa");
        b.importe = 32000000;
        strcpy(b.descripcion, "Casa en Castelar");
        f.write((char*)&b, sizeof(b));

        // Cabecera + bienes para DNI5678
        strcpy(b.documento, "DNI5678");
        strcpy(b.tipoBien, "*");
        b.importe = 0;
        strcpy(b.descripcion, "Cabecera");
        f.write((char*)&b, sizeof(b));

        strcpy(b.tipoBien, "Moto");
        b.importe = 900000;
        strcpy(b.descripcion, "Honda 250");
        f.write((char*)&b, sizeof(b));

        f.close();
    }

    // === Archivo IMPUESTOS.DAT ===
    {
        ofstream f("IMPUESTOS.DAT", ios::binary);
        Impuesto imp;

        imp.monto = 1000000; imp.porcentaje = 5;  f.write((char*)&imp, sizeof(imp));
        imp.monto = 10000000; imp.porcentaje = 10; f.write((char*)&imp, sizeof(imp));
        imp.monto = 30000000; imp.porcentaje = 15; f.write((char*)&imp, sizeof(imp));

        f.close();
    }

    cout << "Archivos generados: DJ.DAT, BIENES.DAT, IMPUESTOS.DAT\n";
    return 0;
}
