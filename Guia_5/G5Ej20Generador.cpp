#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Deudor {
    char codContrib[6];
    int anio;
    int mes;
    float importe;
    char estado; // 'A' adeuda, 'C' cancelada
    int fechaCobro; // aammdd
};

struct DatosPersonales {
    char codContrib[6];
    char nombre[46];
    char domicilio[46];
    char zona[5];
};

struct CobroMes {
    char codContrib[6];
    int anio;
    int mes;
    int fechaCobro; // aammdd
};

void setStr(char *dest, const char *src, int size) {
    strncpy(dest, src, size);
    dest[size-1] = '\0';
}

int main() {
    ofstream f1("DEUDORES.DAT", ios::binary);
    ofstream f2("DATOSPERSONALES.DAT", ios::binary);
    ofstream f3("COBROMES.DAT", ios::binary);

    if (!f1 || !f2 || !f3) {
        cout << "Error creando archivos." << endl;
        return 1;
    }

    // ---------------------
    // DATOS PERSONALES
    // ---------------------
    DatosPersonales dp;

    setStr(dp.codContrib, "00001", 6);
    setStr(dp.nombre, "Juan Perez", 46);
    setStr(dp.domicilio, "Calle 123", 46);
    setStr(dp.zona, "A001", 5);
    f2.write((char*)&dp, sizeof(dp));

    setStr(dp.codContrib, "00002", 6);
    setStr(dp.nombre, "Maria Lopez", 46);
    setStr(dp.domicilio, "Mitre 555", 46);
    setStr(dp.zona, "A002", 5);
    f2.write((char*)&dp, sizeof(dp));

    // ---------------------
    // DEUDORES
    // ---------------------
    Deudor d;

    setStr(d.codContrib, "00001", 6);
    d.anio = 96; d.mes = 3; d.importe = 1500; d.estado='A'; d.fechaCobro=0;
    f1.write((char*)&d, sizeof(d));

    d.anio = 96; d.mes = 4; d.importe = 1500; d.estado='A'; d.fechaCobro=0;
    f1.write((char*)&d, sizeof(d));

    setStr(d.codContrib, "00002", 6);
    d.anio = 95; d.mes = 11; d.importe=1800; d.estado='A'; d.fechaCobro=0;
    f1.write((char*)&d, sizeof(d));

    // ---------------------
    // COBRO MES
    // ---------------------
    CobroMes c;

    setStr(c.codContrib, "00001", 6);
    c.anio = 96; c.mes = 3; c.fechaCobro = 250225;
    f3.write((char*)&c, sizeof(c));

    setStr(c.codContrib, "00002", 6);
    c.anio = 95; c.mes = 11; c.fechaCobro = 250226;
    f3.write((char*)&c, sizeof(c));

    return 0;
}
