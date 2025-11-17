/*
Id.Programa: G4Ej08_GenerarDatos.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025
Comentario.:
    Genera los archivos de datos necesarios para probar G4Ej08.cpp:
    - ARTICULOS.DAT   (archivo relativo 0..100, 0 no se usa)
    - CLIENTES.DAT    (ordenado por codCli)
    - PEDIDOS.DAT     (ordenado por codCli, luego codArt)
    - VENDEDORES.DAT  (desordenado)
    - FACTURAS.DAT    (con algunas facturas ya emitidas)
    - NROSINIC.DAT    (incluye tipoDoc "FAC" con ultimo nro usado)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// ----- Estructuras (mismas que en G4Ej08.cpp) -----

struct Articulo {
    int  codArt;                // 1..100
    char marca[21];
    char desc[21];
    float precio;
    int stockActual;
    int stockMinimo;
    int puntoReposicion;
    char unidadMedida[11];
    char estado;                // 'A'=activo, 'I'=inactivo
};

struct Cliente {
    int  codCli;
    char nombre[21];
    char direccion[21];
    char localidad[21];
    int  codPostal;
    char codProv;
    char cuit[16];
    char formaPago[21];
    int  codVendedor;
    float saldo;
};

struct Pedido {
    int codCli;
    int codArt;
    int cantidad;
};

struct Vendedor {
    int  codVend;
    char nombre[21];
    int  porcComision;
    float importeAcumulado;
};

struct Factura {
    int  nroFactura;
    int  fecha;         // ddmmaa
    int  codCli;
    float importe;
    char estado;        // 'A' adeuda, 'P' pagada
};

struct NroInicial {
    char tipoDoc[6];    // ej: "FAC"
    int  nroDoc;
};

// Helper para limpiar y copiar cadenas a char[]
void copyStr(char* dest, const char* src, size_t maxLen) {
    strncpy(dest, src, maxLen);
    dest[maxLen] = '\0';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Generador de datos para G4Ej08 ===\n";

    // ---------------- ARTICULOS.DAT ----------------
    {
        ofstream fa("ARTICULOS.DAT", ios::binary | ios::trunc);
        if (!fa) {
            cerr << "Error creando ARTICULOS.DAT\n";
            return 1;
        }

        Articulo a;

        // Registro 0 (no se usa)
        a.codArt = 0;
        copyStr(a.marca, "", 20);
        copyStr(a.desc, "", 20);
        a.precio = 0.0f;
        a.stockActual = 0;
        a.stockMinimo = 0;
        a.puntoReposicion = 0;
        copyStr(a.unidadMedida, "", 10);
        a.estado = 'I';
        fa.write(reinterpret_cast<char*>(&a), sizeof(a));

        // Inicializamos todos como inactivos
        for (int i = 1; i <= 100; ++i) {
            a.codArt = 0;
            copyStr(a.marca, "", 20);
            copyStr(a.desc, "", 20);
            a.precio = 0.0f;
            a.stockActual = 0;
            a.stockMinimo = 0;
            a.puntoReposicion = 0;
            copyStr(a.unidadMedida, "", 10);
            a.estado = 'I';
            fa.write(reinterpret_cast<char*>(&a), sizeof(a));
        }

        // Ahora reescribimos algunos artículos "reales" en su posición
        // Articulo 1: Nafta Super
        a.codArt = 1;
        copyStr(a.marca, "YPF", 20);
        copyStr(a.desc, "Nafta Super", 20);
        a.precio = 950.0f;
        a.stockActual = 10000;  // litros
        a.stockMinimo = 2000;
        a.puntoReposicion = 5000;
        copyStr(a.unidadMedida, "litros", 10);
        a.estado = 'A';
        fa.seekp(1 * sizeof(Articulo), ios::beg);
        fa.write(reinterpret_cast<char*>(&a), sizeof(a));

        // Articulo 2: Nafta Premium
        a.codArt = 2;
        copyStr(a.marca, "Shell", 20);
        copyStr(a.desc, "Nafta Premium", 20);
        a.precio = 1100.0f;
        a.stockActual = 8000;
        a.stockMinimo = 1500;
        a.puntoReposicion = 4000;
        copyStr(a.unidadMedida, "litros", 10);
        a.estado = 'A';
        fa.seekp(2 * sizeof(Articulo), ios::beg);
        fa.write(reinterpret_cast<char*>(&a), sizeof(a));

        // Articulo 3: Aceite 10W40
        a.codArt = 3;
        copyStr(a.marca, "Total", 20);
        copyStr(a.desc, "Aceite 10W40", 20);
        a.precio = 6000.0f;
        a.stockActual = 150;
        a.stockMinimo = 30;
        a.puntoReposicion = 80;
        copyStr(a.unidadMedida, "unidades", 10);
        a.estado = 'A';
        fa.seekp(3 * sizeof(Articulo), ios::beg);
        fa.write(reinterpret_cast<char*>(&a), sizeof(a));

        // Articulo 4: Filtro de aceite
        a.codArt = 4;
        copyStr(a.marca, "Bosch", 20);
        copyStr(a.desc, "Filtro aceite", 20);
        a.precio = 4500.0f;
        a.stockActual = 90;
        a.stockMinimo = 20;
        a.puntoReposicion = 50;
        copyStr(a.unidadMedida, "unidades", 10);
        a.estado = 'A';
        fa.seekp(4 * sizeof(Articulo), ios::beg);
        fa.write(reinterpret_cast<char*>(&a), sizeof(a));

        fa.close();
        cout << "ARTICULOS.DAT generado.\n";
    }

    // ---------------- CLIENTES.DAT ----------------
    {
        ofstream fc("CLIENTES.DAT", ios::binary | ios::trunc);
        if (!fc) {
            cerr << "Error creando CLIENTES.DAT\n";
            return 1;
        }

        Cliente c;

        // Cliente 1
        c.codCli = 10000001;
        copyStr(c.nombre, "Estacion Centro", 20);
        copyStr(c.direccion, "Av. Siempre Viva 123", 20);
        copyStr(c.localidad, "Buenos Aires", 20);
        c.codPostal = 1400;
        c.codProv = 'B';
        copyStr(c.cuit, "30-12345678-9", 15);
        copyStr(c.formaPago, "Cuenta Corriente", 20);
        c.codVendedor = 1;
        c.saldo = 0.0f;
        fc.write(reinterpret_cast<char*>(&c), sizeof(c));

        // Cliente 2
        c.codCli = 10000002;
        copyStr(c.nombre, "YPF Ruta 3", 20);
        copyStr(c.direccion, "Ruta 3 KM 45", 20);
        copyStr(c.localidad, "La Matanza", 20);
        c.codPostal = 1750;
        c.codProv = 'B';
        copyStr(c.cuit, "30-87654321-0", 15);
        copyStr(c.formaPago, "Contado", 20);
        c.codVendedor = 2;
        c.saldo = 150000.0f; // saldo preexistente
        fc.write(reinterpret_cast<char*>(&c), sizeof(c));

        // Cliente 3
        c.codCli = 10000003;
        copyStr(c.nombre, "Shell Lomas", 20);
        copyStr(c.direccion, "Av. Pavon 2500", 20);
        copyStr(c.localidad, "Lomas", 20);
        c.codPostal = 1832;
        c.codProv = 'B';
        copyStr(c.cuit, "30-11223344-5", 15);
        copyStr(c.formaPago, "Cuenta Corriente", 20);
        c.codVendedor = 1;
        c.saldo = 50000.0f;
        fc.write(reinterpret_cast<char*>(&c), sizeof(c));

        fc.close();
        cout << "CLIENTES.DAT generado.\n";
    }

    // ---------------- PEDIDOS.DAT ----------------
    {
        ofstream fp("PEDIDOS.DAT", ios::binary | ios::trunc);
        if (!fp) {
            cerr << "Error creando PEDIDOS.DAT\n";
            return 1;
        }

        Pedido p;

        // Ordenado por codCli y luego por codArt

        // Cliente 10000001
        p.codCli = 10000001; p.codArt = 1; p.cantidad = 2000; // 2000 litros Nafta Super
        fp.write(reinterpret_cast<char*>(&p), sizeof(p));
        p.codCli = 10000001; p.codArt = 3; p.cantidad = 10;   // 10 bidones aceite
        fp.write(reinterpret_cast<char*>(&p), sizeof(p));

        // Cliente 10000002
        p.codCli = 10000002; p.codArt = 2; p.cantidad = 3000; // Premium
        fp.write(reinterpret_cast<char*>(&p), sizeof(p));
        p.codCli = 10000002; p.codArt = 4; p.cantidad = 5;    // filtros
        fp.write(reinterpret_cast<char*>(&p), sizeof(p));

        // Cliente 10000003
        p.codCli = 10000003; p.codArt = 1; p.cantidad = 1500;
        fp.write(reinterpret_cast<char*>(&p), sizeof(p));

        fp.close();
        cout << "PEDIDOS.DAT generado.\n";
    }

    // ---------------- VENDEDORES.DAT ----------------
    {
        ofstream fv("VENDEDORES.DAT", ios::binary | ios::trunc);
        if (!fv) {
            cerr << "Error creando VENDEDORES.DAT\n";
            return 1;
        }

        Vendedor v;

        // Desordenado a propósito
        v.codVend = 2;
        copyStr(v.nombre, "Carlos Gomez", 20);
        v.porcComision = 7;
        v.importeAcumulado = 200000.0f;
        fv.write(reinterpret_cast<char*>(&v), sizeof(v));

        v.codVend = 1;
        copyStr(v.nombre, "Ana Perez", 20);
        v.porcComision = 5;
        v.importeAcumulado = 150000.0f;
        fv.write(reinterpret_cast<char*>(&v), sizeof(v));

        v.codVend = 3;
        copyStr(v.nombre, "Juan Lopez", 20);
        v.porcComision = 6;
        v.importeAcumulado = 50000.0f;
        fv.write(reinterpret_cast<char*>(&v), sizeof(v));

        fv.close();
        cout << "VENDEDORES.DAT generado.\n";
    }

    // ---------------- FACTURAS.DAT ----------------
    {
        ofstream ff("FACTURAS.DAT", ios::binary | ios::trunc);
        if (!ff) {
            cerr << "Error creando FACTURAS.DAT\n";
            return 1;
        }

        Factura f;

        // Factura vieja 1500
        f.nroFactura = 1500;
        f.fecha = 100825; // 10/08/25
        f.codCli = 10000001;
        f.importe = 250000.0f;
        f.estado = 'P';   // pagada
        ff.write(reinterpret_cast<char*>(&f), sizeof(f));

        // Factura vieja 1501
        f.nroFactura = 1501;
        f.fecha = 120825; // 12/08/25
        f.codCli = 10000002;
        f.importe = 180000.0f;
        f.estado = 'A';   // adeuda
        ff.write(reinterpret_cast<char*>(&f), sizeof(f));

        ff.close();
        cout << "FACTURAS.DAT generado.\n";
    }

    // ---------------- NROSINIC.DAT ----------------
    {
        ofstream fn("NROSINIC.DAT", ios::binary | ios::trunc);
        if (!fn) {
            cerr << "Error creando NROSINIC.DAT\n";
            return 1;
        }

        NroInicial n;

        // Otro tipo de doc de ejemplo
        copyStr(n.tipoDoc, "REM", 5);
        n.nroDoc = 5000;
        fn.write(reinterpret_cast<char*>(&n), sizeof(n));

        // Tipo FAC: ultimo usado 1501
        copyStr(n.tipoDoc, "FAC", 5);
        n.nroDoc = 1501;
        fn.write(reinterpret_cast<char*>(&n), sizeof(n));

        // Otro tipo
        copyStr(n.tipoDoc, "NC", 5);
        n.nroDoc = 200;
        fn.write(reinterpret_cast<char*>(&n), sizeof(n));

        fn.close();
        cout << "NROSINIC.DAT generado.\n";
    }

    cout << "\n✅ Todos los archivos se generaron correctamente.\n";
    return 0;
}
