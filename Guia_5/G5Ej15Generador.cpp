/*
Id.Programa: G5Ej15Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Genera archivos de prueba:
      - ARTICULOS.DAT : archivo con articulos sin orden
      - REQUERIMIENTOS.DAT : lista de requerimientos anotada por doña Rosa
    Los archivos binarios respetan las estructuras usadas por G5Ej15.cpp.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Art {
    int codigo;
    char descripcion[31];
    int stockActual;
    int stockMin;
    double precio;
    char unidad[11];
};

struct Req {
    char descripcion[31];
    int cantidad;
};

int main() {
    // ARTICULOS.DAT
    {
        ofstream f("ARTICULOS.DAT", ios::binary);
        if (!f) { cout << "No se pudo crear ARTICULOS.DAT\n"; return 1; }

        Art a;

        a.codigo = 1001; strcpy(a.descripcion, "Leche entera 1L"); a.stockActual = 50; a.stockMin = 10; a.precio = 150.50; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 2002; strcpy(a.descripcion, "Pan integral 500g"); a.stockActual = 20; a.stockMin = 5; a.precio = 80.00; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 3003; strcpy(a.descripcion, "Huevos x12"); a.stockActual = 5; a.stockMin = 10; a.precio = 320.00; strcpy(a.unidad, "pack");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 4004; strcpy(a.descripcion, "Arroz 1kg"); a.stockActual = 100; a.stockMin = 20; a.precio = 220.75; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 5005; strcpy(a.descripcion, "Azucar 1kg"); a.stockActual = 2; a.stockMin = 15; a.precio = 110.00; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 6006; strcpy(a.descripcion, "Aceite 1L"); a.stockActual = 8; a.stockMin = 10; a.precio = 760.00; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 7007; strcpy(a.descripcion, "Queso 1kg"); a.stockActual = 4; a.stockMin = 3; a.precio = 2500.00; strcpy(a.unidad, "kg");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 8008; strcpy(a.descripcion, "Galletitas 200g"); a.stockActual = 40; a.stockMin = 10; a.precio = 140.00; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        a.codigo = 9009; strcpy(a.descripcion, "Fideos 500g"); a.stockActual = 25; a.stockMin = 7; a.precio = 95.50; strcpy(a.unidad, "unit");
        f.write(reinterpret_cast<char*>(&a), sizeof(Art));

        f.close();
        cout << "ARTICULOS.DAT creado.\n";
    }

    // REQUERIMIENTOS.DAT (lista anotada por doña Rosa, en orden de aparición)
    {
        ofstream f("REQUERIMIENTOS.DAT", ios::binary);
        if (!f) { cout << "No se pudo crear REQUERIMIENTOS.DAT\n"; return 1; }

        Req r;

        strcpy(r.descripcion, "Leche"); r.cantidad = 3; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Pan");   r.cantidad = 2; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Huevos");r.cantidad = 2; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Azucar");r.cantidad = 1; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Queso"); r.cantidad = 1; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Leche entera"); r.cantidad = 1; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Aceite"); r.cantidad = 2; f.write(reinterpret_cast<char*>(&r), sizeof(Req));
        strcpy(r.descripcion, "Fideos"); r.cantidad = 3; f.write(reinterpret_cast<char*>(&r), sizeof(Req));

        f.close();
        cout << "REQUERIMIENTOS.DAT creado.\n";
    }

    cout << "Generador finalizado.\n";
    return 0;
}
