/*
Id.Programa: G5Ej26.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de archivos binarios de prueba VENTAS.DAT y CLIENTES.DAT
    para el ejercicio G5Ej26.cpp
    Formatos binarios generados:
      VENTA   : nroCliente[8], fecha(int MMDD), vendedor[7], importe(double)
      CLIENTE : nroCliente[8], domicilio[41], apellidoNombre[31], cuit[12]
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct VentaGen {
    char nroCliente[8]; // 7 + '\0'
    int fecha; // MMDD
    char vendedor[7]; // 6 + '\0'
    double importe;
};

struct ClienteGen {
    char nroCliente[8];
    char domicilio[41];
    char apellidoNombre[31];
    char cuit[12];
};

void setStr(char* dst, const char* src, size_t n){ strncpy(dst, src, n-1); dst[n-1]='\0'; }

int main(){
    // Generar CLIENTES.DAT
    {
        ofstream f("CLIENTES.DAT", ios::binary|ios::trunc);
        if(!f){ cerr<<"No puedo crear CLIENTES.DAT\n"; return 1; }
        ClienteGen c;
        setStr(c.nroCliente, "0000001", sizeof(c.nroCliente)); setStr(c.domicilio, "Calle A 123", sizeof(c.domicilio)); setStr(c.apellidoNombre, "Gomez Juan", sizeof(c.apellidoNombre)); setStr(c.cuit, "20123456789", sizeof(c.cuit)); f.write((char*)&c, sizeof(c));
        setStr(c.nroCliente, "0000002", sizeof(c.nroCliente)); setStr(c.domicilio, "Calle B 45", sizeof(c.domicilio)); setStr(c.apellidoNombre, "Perez Ana", sizeof(c.apellidoNombre)); setStr(c.cuit, "20123456780", sizeof(c.cuit)); f.write((char*)&c, sizeof(c));
        setStr(c.nroCliente, "0000003", sizeof(c.nroCliente)); setStr(c.domicilio, "Av. Central 10", sizeof(c.domicilio)); setStr(c.apellidoNombre, "Lopez Carlos", sizeof(c.apellidoNombre)); setStr(c.cuit, "20123456781", sizeof(c.cuit)); f.write((char*)&c, sizeof(c));
        setStr(c.nroCliente, "0000004", sizeof(c.nroCliente)); setStr(c.domicilio, "Ruta 5 km 2", sizeof(c.domicilio)); setStr(c.apellidoNombre, "Martinez Lucia", sizeof(c.apellidoNombre)); setStr(c.cuit, "20123456782", sizeof(c.cuit)); f.write((char*)&c, sizeof(c));
        f.close();
        cout<<"CLIENTES.DAT generado.\n";
    }

    // Generar VENTAS.DAT (ordenado por fecha MMDD asc)
    {
        ofstream f("VENTAS.DAT", ios::binary|ios::trunc);
        if(!f){ cerr<<"No puedo crear VENTAS.DAT\n"; return 1; }
        VentaGen v;
        // Enero (01)
        setStr(v.nroCliente, "0000001", sizeof(v.nroCliente)); v.fecha = 101; setStr(v.vendedor, "VEND01", sizeof(v.vendedor)); v.importe = 1000.0; f.write((char*)&v, sizeof(v));
        setStr(v.nroCliente, "0000002", sizeof(v.nroCliente)); v.fecha = 102; setStr(v.vendedor, "VEND02", sizeof(v.vendedor)); v.importe = 800.0; f.write((char*)&v, sizeof(v));
        setStr(v.nroCliente, "0000001", sizeof(v.nroCliente)); v.fecha = 110; setStr(v.vendedor, "VEND02", sizeof(v.vendedor)); v.importe = 500.0; f.write((char*)&v, sizeof(v));
        // Febrero (02)
        setStr(v.nroCliente, "0000003", sizeof(v.nroCliente)); v.fecha = 201; setStr(v.vendedor, "VEND01", sizeof(v.vendedor)); v.importe = 1200.0; f.write((char*)&v, sizeof(v));
        setStr(v.nroCliente, "0000002", sizeof(v.nroCliente)); v.fecha = 215; setStr(v.vendedor, "VEND03", sizeof(v.vendedor)); v.importe = 700.0; f.write((char*)&v, sizeof(v));
        // Marzo (03) - create more to test averages
        setStr(v.nroCliente, "0000004", sizeof(v.nroCliente)); v.fecha = 301; setStr(v.vendedor, "VEND02", sizeof(v.vendedor)); v.importe = 2000.0; f.write((char*)&v, sizeof(v));
        setStr(v.nroCliente, "0000001", sizeof(v.nroCliente)); v.fecha = 305; setStr(v.vendedor, "VEND01", sizeof(v.vendedor)); v.importe = 1500.0; f.write((char*)&v, sizeof(v));
        setStr(v.nroCliente, "0000003", sizeof(v.nroCliente)); v.fecha = 312; setStr(v.vendedor, "VEND03", sizeof(v.vendedor)); v.importe = 300.0; f.write((char*)&v, sizeof(v));

        // Abril (04)
        setStr(v.nroCliente, "0000002", sizeof(v.nroCliente)); v.fecha = 401; setStr(v.vendedor, "VEND01", sizeof(v.vendedor)); v.importe = 600.0; f.write((char*)&v, sizeof(v));

        f.close();
        cout<<"VENTAS.DAT generado.\n";
    }

    cout<<"Generador G5Ej26 finalizado.\n";
    return 0;
}