/*
Id.Programa: G5Ej20.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

struct Deudor {
    char codContrib[6];
    int anio;
    int mes;
    float importe;
    char estado; // 'A' adeuda, 'C' cancelada
    int fechaCobro;
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
    int fechaCobro;
};

int main() {
    fstream fDeu("DEUDORES.DAT", ios::binary | ios::in | ios::out);
    ifstream fDat("DATOSPERSONALES.DAT", ios::binary);
    ifstream fCob("COBROMES.DAT", ios::binary);

    if (!fDeu || !fDat || !fCob) {
        cout << "Error abriendo archivos." << endl;
        return 1;
    }

    // Cargar datos personales en un map (clave = codContrib)
    map<string, DatosPersonales> datos;
    DatosPersonales dp;
    while (fDat.read((char*)&dp, sizeof(dp))) {
        datos[string(dp.codContrib)] = dp;
    }

    cout << "Listado de Control de Cobranza\n";
    cout << "Contrib. Apellido,Nombre Año Mes Importe Situac.\n";

    // Recaudación por zona
    map<string, float> recaudacion;

    CobroMes cm;
    while (fCob.read((char*)&cm, sizeof(cm))) {

        bool encontrado = false;
        bool yaCancelado = false;

        fDeu.clear();
        fDeu.seekg(0);

        Deudor d;
        streampos pos;

        while (true) {
            pos = fDeu.tellg();
            if (!fDeu.read((char*)&d, sizeof(d)))
                break;

            if (string(d.codContrib) == string(cm.codContrib)
                && d.anio == cm.anio
                && d.mes == cm.mes) {

                encontrado = true;
                if (d.estado == 'C') yaCancelado = true;
                else {
                    d.estado = 'C';
                    d.fechaCobro = cm.fechaCobro;

                    fDeu.seekp(pos);
                    fDeu.write((char*)&d, sizeof(d));

                    string zona = datos[string(d.codContrib)].zona;
                    recaudacion[zona] += d.importe;
                }
                break;
            }
        }

        DatosPersonales &p = datos[string(cm.codContrib)];

        cout << cm.codContrib << " "
             << p.nombre << " "
             << cm.anio << " "
             << cm.mes << " ";

        if (!encontrado) {
            cout << "----- E\n";
        } else if (yaCancelado) {
            cout << d.importe << " E\n";
        } else {
            cout << d.importe << " P\n";
        }
    }

    cout << "\n\nTotal recaudado por zona:\n";
    cout << "Zona   Importe\n";

    for (auto &par : recaudacion) {
        cout << par.first << "   " << par.second << "\n";
    }

    return 0;
}
