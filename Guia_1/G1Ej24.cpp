/*
Id.Programa: G1Ej24.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: Ventas agrupadas por codigo de vendedor. Para cada vendedor:
             - Emitir cada item (cantidad, descripcion, precio, importe)
             - Emitir total vendido por ese vendedor
             Al final:
             - Importe total vendido por todos los vendedores
             - Vendedor que mas vendio en importe
             Valor centinela: codigo de vendedor = 0 para finalizar el proceso.
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    int codVendedor;                // 3 digitos
    long long cantidad;             // 4 digitos
    string descripcion;             // hasta 20 chars
    double precioUnit;              // 5 digitos, 2 decimales

    double totalGeneral = 0.0;
    int mejorVendedor = -1;
    double mejorImporte = -1.0;

    cout << fixed << setprecision(2);
    cout << "Carga de ventas (codigo vendedor 0 para terminar)" << endl;

    while (true) {
        cout << "\nCodigo de vendedor (0 = fin): ";
        if (!(cin >> codVendedor)) return 0; // fin por EOF
        if (codVendedor == 0) break;

        // corte de control por vendedor
        double totalVendedor = 0.0;

        cout << "Cargando ventas para vendedor " << codVendedor << endl;

        // bucle de items del mismo vendedor
        while (true) {
            cout << "Cantidad vendida (entero, 0 = fin de este vendedor): ";
            cin >> cantidad;
            if (cantidad == 0) break;

            cin.ignore(); // limpiar salto de linea antes de getline

            cout << "Descripcion del articulo (max 20 chars): ";
            getline(cin, descripcion);

            cout << "Precio unitario (xx.xx): ";
            cin >> precioUnit;

            double importe = cantidad * precioUnit;

            // emitir item
            cout << "Item -> Cant: " << cantidad
                 << " | Desc: " << descripcion
                 << " | Precio: $" << precioUnit
                 << " | Importe: $" << importe << endl;

            totalVendedor += importe;
        }

        // emitir total del vendedor
        cout << "Total vendido por vendedor " << codVendedor
             << ": $" << totalVendedor << endl;

        totalGeneral += totalVendedor;

        // actualizar maximo vendedor
        if (totalVendedor > mejorImporte) {
            mejorImporte = totalVendedor;
            mejorVendedor = codVendedor;
        }
    }

    // fin de proceso
    cout << "\n---- RESUMEN FINAL ----" << endl;
    cout << "Importe total vendido (todos los vendedores): $" << totalGeneral << endl;

    if (mejorVendedor != -1)
        cout << "Vendedor que mas vendio: " << mejorVendedor
             << " con $" << mejorImporte << endl;
    else
        cout << "No se registraron ventas." << endl;

    return 0;
}