/*
Id.Programa: G4Ej08_VerClientes.cpp
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream f("CLIENTES_ACT.DAT", ios::binary);
    if (!f) {
        cerr << "No se pudo abrir CLIENTES_ACT.DAT\n";
        return 1;
    }

    Cliente c;
    cout << left << setw(10) << "CodCli"
         << setw(22) << "Nombre"
         << setw(12) << "Vendedor"
         << "Saldo\n";
    cout << "---------------------------------------------\n";

    while (f.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        cout << left << setw(10) << c.codCli
             << setw(22) << c.nombre
             << setw(12) << c.codVendedor
             << fixed << setprecision(2) << c.saldo << "\n";
    }

    f.close();
    return 0;
}