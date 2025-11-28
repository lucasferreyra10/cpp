/*
Id.Programa: G5Ej23Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de archivos de prueba para el ejercicio 23 (MoviTel).
    Crea:
      - COMUNICACIONES.DAT  (ordenado por Cliente, como indica el enunciado)
         registro: nroCliente(9 chars), pulsos (int), dia (1..31)
      - CLIENTES.DAT        (ordenado por cliente)
         registro: nroCliente(9 chars), razonSocial(35), domicilio(50), categoria(int)
      - CATEGORIAS.DAT      (sin orden)
         registro: codigo(int), importeAbono (double), importePulso (double), pulsosSinCargo (int)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Comunic {
    char nroCliente[10]; // 9 + '\0'
    int pulsos;
    int dia;
};

struct Cliente {
    char nroCliente[10];
    char razon[36];
    char domicilio[51];
    int categoria;
};

struct Categoria {
    int codigo;
    double importeAbono;
    double importePulso;
    int pulsosSinCargo;
};

void setStr(char* dst, const char* src, size_t n) {
    strncpy(dst, src, n-1);
    dst[n-1] = '\0';
}

int main() {
    // CATEGORIAS.DAT
    {
        ofstream f("CATEGORIAS.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear CATEGORIAS.DAT\n"; return 1; }
        Categoria c;

        c.codigo = 1; c.importeAbono = 200.00; c.importePulso = 2.0; c.pulsosSinCargo = 20; f.write((char*)&c, sizeof(c));
        c.codigo = 2; c.importeAbono = 350.00; c.importePulso = 1.5; c.pulsosSinCargo = 50; f.write((char*)&c, sizeof(c));
        c.codigo = 3; c.importeAbono = 500.00; c.importePulso = 1.0; c.pulsosSinCargo = 100; f.write((char*)&c, sizeof(c));

        f.close();
        cout << "CATEGORIAS.DAT creado.\n";
    }

    // CLIENTES.DAT (ordenado por cliente)
    {
        ofstream f("CLIENTES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear CLIENTES.DAT\n"; return 1; }
        Cliente cl;

        setStr(cl.nroCliente, "000000001", sizeof(cl.nroCliente));
        setStr(cl.razon, "Empresa Alfa SA", sizeof(cl.razon));
        setStr(cl.domicilio, "Av. Siempre Viva 123", sizeof(cl.domicilio));
        cl.categoria = 1; f.write((char*)&cl, sizeof(cl));

        setStr(cl.nroCliente, "000000002", sizeof(cl.nroCliente));
        setStr(cl.razon, "Comercial Beta SRL", sizeof(cl.razon));
        setStr(cl.domicilio, "Calle Falsa 742", sizeof(cl.domicilio));
        cl.categoria = 2; f.write((char*)&cl, sizeof(cl));

        setStr(cl.nroCliente, "000000003", sizeof(cl.nroCliente));
        setStr(cl.razon, "Servicios Gamma", sizeof(cl.razon));
        setStr(cl.domicilio, "Pza. Central 10", sizeof(cl.domicilio));
        cl.categoria = 2; f.write((char*)&cl, sizeof(cl));

        setStr(cl.nroCliente, "000000010", sizeof(cl.nroCliente));
        setStr(cl.razon, "Industrias Delta", sizeof(cl.razon));
        setStr(cl.domicilio, "Ruta 5 km 30", sizeof(cl.domicilio));
        cl.categoria = 3; f.write((char*)&cl, sizeof(cl));

        f.close();
        cout << "CLIENTES.DAT creado.\n";
    }

    // COMUNICACIONES.DAT (ordenado por cliente, puede tener varios registros por cliente y por dia)
    {
        ofstream f("COMUNICACIONES.DAT", ios::binary | ios::trunc);
        if (!f) { cerr << "No se pudo crear COMUNICACIONES.DAT\n"; return 1; }
        Comunic s;

        // Cliente 000000001: varios dias
        setStr(s.nroCliente, "000000001", sizeof(s.nroCliente)); s.pulsos = 10; s.dia = 1; f.write((char*)&s, sizeof(s));
        setStr(s.nroCliente, "000000001", sizeof(s.nroCliente)); s.pulsos = 30; s.dia = 2; f.write((char*)&s, sizeof(s));
        setStr(s.nroCliente, "000000001", sizeof(s.nroCliente)); s.pulsos = 60; s.dia = 15; f.write((char*)&s, sizeof(s)); // peak >50

        // Cliente 000000002
        setStr(s.nroCliente, "000000002", sizeof(s.nroCliente)); s.pulsos = 25; s.dia = 3; f.write((char*)&s, sizeof(s));
        setStr(s.nroCliente, "000000002", sizeof(s.nroCliente)); s.pulsos = 40; s.dia = 10; f.write((char*)&s, sizeof(s));

        // Cliente 000000003
        setStr(s.nroCliente, "000000003", sizeof(s.nroCliente)); s.pulsos = 51; s.dia = 5; f.write((char*)&s, sizeof(s)); // peak >50
        setStr(s.nroCliente, "000000003", sizeof(s.nroCliente)); s.pulsos = 10; s.dia = 6; f.write((char*)&s, sizeof(s));

        // Cliente 000000010 (categoria 3, many small)
        setStr(s.nroCliente, "000000010", sizeof(s.nroCliente)); s.pulsos = 200; s.dia = 20; f.write((char*)&s, sizeof(s)); // big
        setStr(s.nroCliente, "000000010", sizeof(s.nroCliente)); s.pulsos = 5; s.dia = 21; f.write((char*)&s, sizeof(s));

        f.close();
        cout << "COMUNICACIONES.DAT creado.\n";
    }

    cout << "Generador G5Ej23 finalizado.\n";
    return 0;
}
