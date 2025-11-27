/*
Id.Programa: G5Ej17Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de datos para el ejercicio G5Ej17 (Supermercado - Rubros y Artículos).

    Archivos generados (binarios):
      - ARTICULOS.DAT   : Artículo (sin orden)
          Código Artículo (7 chars + '\0')
          Descripción (30 chars + '\0')
          Stock Actual (int)
          Stock Mínimo (int)
          Código de Rubro (5 chars + '\0')
          Unidad de Medida (10 chars + '\0')
          Precio Unitario (double)

      - RUBROS.DAT      : Rubros (ordenado por Código de Rubro)
          Código Rubro (5 chars + '\0')
          Descripción (30 chars + '\0')
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Articulo {
    char codigo[8];       // 7 + '\0'
    char descripcion[31]; // 30 + '\0'
    int stockActual;
    int stockMin;
    char codigoRubro[6];  // 5 + '\0'
    char unidad[11];      // 10 + '\0'
    double precio;
};

struct Rubro {
    char codigo[6];       // 5 + '\0'
    char descripcion[31]; // 30 + '\0'
};

void setStr(char *dest, const char *src, size_t size) {
    strncpy(dest, src, size-1);
    dest[size-1] = '\0';
}

int main() {
    // --- Generar RUBROS.DAT (ordenado por codigo) ---
    {
        ofstream fr("RUBROS.DAT", ios::binary);
        if (!fr) {
            cerr << "Error: no se pudo crear RUBROS.DAT\n";
            return 1;
        }

        Rubro r;

        setStr(r.codigo, "R0001", sizeof(r.codigo));
        setStr(r.descripcion, "Alimentos frescos", sizeof(r.descripcion));
        fr.write(reinterpret_cast<char*>(&r), sizeof(Rubro));

        setStr(r.codigo, "R0002", sizeof(r.codigo));
        setStr(r.descripcion, "Abarrotes y secos", sizeof(r.descripcion));
        fr.write(reinterpret_cast<char*>(&r), sizeof(Rubro));

        setStr(r.codigo, "R0003", sizeof(r.codigo));
        setStr(r.descripcion, "Limpieza y hogar", sizeof(r.descripcion));
        fr.write(reinterpret_cast<char*>(&r), sizeof(Rubro));

        setStr(r.codigo, "R0004", sizeof(r.codigo));
        setStr(r.descripcion, "Bebidas", sizeof(r.descripcion));
        fr.write(reinterpret_cast<char*>(&r), sizeof(Rubro));

        setStr(r.codigo, "R0005", sizeof(r.codigo));
        setStr(r.descripcion, "Lácteos y congelados", sizeof(r.descripcion));
        fr.write(reinterpret_cast<char*>(&r), sizeof(Rubro));

        fr.close();
        cout << "RUBROS.DAT generado (ordenado por codigo)." << endl;
    }

    // --- Generar ARTICULOS.DAT (sin orden) ---
    {
        ofstream fa("ARTICULOS.DAT", ios::binary);
        if (!fa) {
            cerr << "Error: no se pudo crear ARTICULOS.DAT\n";
            return 1;
        }

        Articulo a;

        // Nota: escribimos EN DESORDEN a proposito
        setStr(a.codigo, "0001001", sizeof(a.codigo));
        setStr(a.descripcion, "Arroz 1kg", sizeof(a.descripcion));
        a.stockActual = 120;
        a.stockMin = 20;
        setStr(a.codigoRubro, "R0002", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 220.75;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0002005", sizeof(a.codigo));
        setStr(a.descripcion, "Lechuga x unidad", sizeof(a.descripcion));
        a.stockActual = 40;
        a.stockMin = 10;
        setStr(a.codigoRubro, "R0001", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 85.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0003007", sizeof(a.codigo));
        setStr(a.descripcion, "Detergente 1L", sizeof(a.descripcion));
        a.stockActual = 15;
        a.stockMin = 10;
        setStr(a.codigoRubro, "R0003", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 410.50;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0004002", sizeof(a.codigo));
        setStr(a.descripcion, "Coca-Cola 2.25L", sizeof(a.descripcion));
        a.stockActual = 60;
        a.stockMin = 15;
        setStr(a.codigoRubro, "R0004", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 325.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0005009", sizeof(a.codigo));
        setStr(a.descripcion, "Queso Barra 1kg", sizeof(a.descripcion));
        a.stockActual = 8;
        a.stockMin = 5;
        setStr(a.codigoRubro, "R0005", sizeof(a.codigoRubro));
        setStr(a.unidad, "kg", sizeof(a.unidad));
        a.precio = 2500.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0006003", sizeof(a.codigo));
        setStr(a.descripcion, "Fideos 500g", sizeof(a.descripcion));
        a.stockActual = 30;
        a.stockMin = 8;
        setStr(a.codigoRubro, "R0002", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 95.50;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0007008", sizeof(a.codigo));
        setStr(a.descripcion, "Leche entera 1L", sizeof(a.descripcion));
        a.stockActual = 55;
        a.stockMin = 12;
        setStr(a.codigoRubro, "R0005", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 150.50;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0008006", sizeof(a.codigo));
        setStr(a.descripcion, "Aceite 1L", sizeof(a.descripcion));
        a.stockActual = 9;
        a.stockMin = 10;
        setStr(a.codigoRubro, "R0002", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 760.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0009004", sizeof(a.codigo));
        setStr(a.descripcion, "Pan integral 500g", sizeof(a.descripcion));
        a.stockActual = 22;
        a.stockMin = 5;
        setStr(a.codigoRubro, "R0002", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 80.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0010000", sizeof(a.codigo));
        setStr(a.descripcion, "Lavandina 1L", sizeof(a.descripcion));
        a.stockActual = 6;
        a.stockMin = 10;
        setStr(a.codigoRubro, "R0003", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 120.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        // algunos más para dar variedad
        setStr(a.codigo, "0011002", sizeof(a.codigo));
        setStr(a.descripcion, "Yerba 1kg", sizeof(a.descripcion));
        a.stockActual = 35;
        a.stockMin = 10;
        setStr(a.codigoRubro, "R0002", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 650.00;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        setStr(a.codigo, "0012007", sizeof(a.codigo));
        setStr(a.descripcion, "Jabon en polvo 3kg", sizeof(a.descripcion));
        a.stockActual = 4;
        a.stockMin = 6;
        setStr(a.codigoRubro, "R0003", sizeof(a.codigoRubro));
        setStr(a.unidad, "unit", sizeof(a.unidad));
        a.precio = 980.25;
        fa.write(reinterpret_cast<char*>(&a), sizeof(Articulo));

        fa.close();
        cout << "ARTICULOS.DAT generado (sin orden)." << endl;
    }

    cout << "Generador G5Ej17 finalizado." << endl;
    return 0;
}
