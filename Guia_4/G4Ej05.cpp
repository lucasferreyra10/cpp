/*
Id.Programa: G4Ej05.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025
Comentario.:
    ABML sobre ARTREL.DAT (archivo relativo con claves 1..100).
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>   // ← strncpy
#include <string>    // ← getline, string
#include <cctype>    // ← toupper
using namespace std;

struct ArticuloRel {
    int codigo;
    char nombre[21];
    float precio;
};

const char* ARCHIVO = "ARTREL.DAT";

// --------------------------
bool leerRegistro(fstream &arch, int clave, ArticuloRel &a) {
    arch.seekg(clave * sizeof(ArticuloRel), ios::beg);
    arch.read(reinterpret_cast<char*>(&a), sizeof(a));
    return static_cast<bool>(arch); 
}
// --------------------------
bool grabarRegistro(fstream &arch, int clave, const ArticuloRel &a) {
    arch.seekp(clave * sizeof(ArticuloRel), ios::beg);
    arch.write(reinterpret_cast<const char*>(&a), sizeof(a));
    return static_cast<bool>(arch);
}
// --------------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fstream arch(ARCHIVO, ios::in | ios::out | ios::binary);
    if (!arch) {
        cerr << "No se pudo abrir ARTREL.DAT. Ejecute G4Ej04 primero.\n";
        return 1;
    }

    char op;
    do {
        cout << "\n===== MENU =====\n";
        cout << "A - Alta\n";
        cout << "B - Baja\n";
        cout << "M - Modificacion\n";
        cout << "L - Listar intervalo\n";
        cout << "F - Finalizar\n";
        cout << "Opcion: ";
        cin >> op;

        op = toupper(op);    // ← ahora sí funciona

        if (op == 'F') break;

        int clave;

        if (op != 'L') {
            cout << "Clave (1..100): ";
            cin >> clave;
            if (clave < 1 || clave > 100) {
                cout << "Clave inválida.\n";
                continue;
            }
        }

        ArticuloRel art;

        switch(op) {

        // --------------------- ALTA ---------------------
        case 'A': {
            leerRegistro(arch, clave, art);
            if (art.codigo != 0) {
                cout << "Error: ya existe.\n";
                break;
            }

            art.codigo = clave;

            cout << "Nombre: ";
            cin >> ws;
            string nom;
            getline(cin, nom);               // ← ahora sí funciona
            strncpy(art.nombre, nom.c_str(), 20);  // ← ok
            art.nombre[20] = '\0';

            cout << "Precio: ";
            cin >> art.precio;

            if (art.precio <= 0) {
                cout << "Precio inválido.\n";
                break;
            }

            grabarRegistro(arch, clave, art);
            cout << "Alta realizada.\n";
            break;
        }

        // --------------------- BAJA ---------------------
        case 'B': {
            leerRegistro(arch, clave, art);
            if (art.codigo == 0) {
                cout << "Error: no existe.\n";
                break;
            }

            ArticuloRel vacio{};
            grabarRegistro(arch, clave, vacio);
            cout << "Baja realizada.\n";
            break;
        }

        // ------------------ MODIFICACION ----------------
        case 'M': {
            leerRegistro(arch, clave, art);
            if (art.codigo == 0) {
                cout << "Error: no existe.\n";
                break;
            }

            cout << "Actual: " << art.nombre << " $" << art.precio << "\n";

            cout << "Nuevo nombre: ";
            cin >> ws;
            string nom;
            getline(cin, nom);
            strncpy(art.nombre, nom.c_str(), 20);
            art.nombre[20] = '\0';

            cout << "Nuevo precio: ";
            cin >> art.precio;

            if (art.precio <= 0) {
                cout << "Precio inválido.\n";
                break;
            }

            grabarRegistro(arch, clave, art);
            cout << "Modificación realizada.\n";
            break;
        }

        // --------------------- LISTAR ---------------------
        case 'L': {
            int desde, hasta;
            cout << "Desde: "; cin >> desde;
            cout << "Hasta: "; cin >> hasta;

            if (desde < 1 || hasta > 100 || desde > hasta) {
                cout << "Intervalo inválido.\n";
                break;
            }

            cout << "\nCod   Nombre               Precio\n";
            cout << "-----------------------------------\n";

            for (int i = desde; i <= hasta; i++) {
                leerRegistro(arch, i, art);
                if (art.codigo != 0) {
                    cout << left << setw(5) << art.codigo
                         << setw(20) << art.nombre
                         << "$ " << fixed << setprecision(2) << art.precio << "\n";
                }
            }
            break;
        }

        default:
            cout << "Opción inválida.\n";
        }

        arch.clear(); // limpiar flags

    } while (op != 'F');

    arch.close();
    cout << "Fin.\n";
    return 0;
}