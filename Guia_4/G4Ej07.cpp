/*
Id.Programa: G4Ej07.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Proceso de actualización de un archivo MAESTRO.DAT mediante
    un archivo de NOVEDADES.DAT utilizando la técnica de APAREO.

    Ambos archivos:
      - Están ordenados por la misma clave.
      - No tienen repetición de claves dentro de cada archivo.

    NOVEDADES.DAT tiene los mismos campos que el maestro, más:
      - Código de movimiento: 'A' (Alta), 'B' (Baja), 'M' (Modificación).

    Se genera:
      - MAESTRO_ACT.DAT (maestro actualizado).
      - ERRORES.TXT: lista de inconsistencias:
          - Alta existente (A con clave ya presente en maestro)
          - Baja inexistente (B con clave NO presente)
          - Modificación inexistente (M con clave NO presente)
        Incluye: clave, tipo de error, y posición (N° de registro) en NOVEDADES.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct RegMaestro {
    int  clave;        // valor clave
    char nombre[31];   // ejemplo de dato asociado
    float saldo;       // otro dato (puede ser lo que pida el enunciado)
};

struct RegNovedad {
    int  clave;
    char nombre[31];
    float saldo;
    char mov;          // 'A', 'B', 'M'
};

// Lecturas con control de EOF
bool leerMaestro(ifstream &fm, RegMaestro &m) {
    return static_cast<bool>(
        fm.read(reinterpret_cast<char*>(&m), sizeof(m))
    );
}

bool leerNovedad(ifstream &fn, RegNovedad &n) {
    return static_cast<bool>(
        fn.read(reinterpret_cast<char*>(&n), sizeof(n))
    );
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fm("MAESTRO.DAT", ios::binary);
    if (!fm) {
        cerr << "❌ No se pudo abrir MAESTRO.DAT\n";
        return 1;
    }

    ifstream fn("NOVEDADES.DAT", ios::binary);
    if (!fn) {
        cerr << "❌ No se pudo abrir NOVEDADES.DAT\n";
        return 1;
    }

    ofstream fa("MAESTRO_ACT.DAT", ios::binary | ios::trunc);
    if (!fa) {
        cerr << "❌ No se pudo crear MAESTRO_ACT.DAT\n";
        return 1;
    }

    ofstream ferr("ERRORES.TXT");
    if (!ferr) {
        cerr << "❌ No se pudo crear ERRORES.TXT\n";
        return 1;
    }

    RegMaestro m;
    RegNovedad n;
    bool hayM = leerMaestro(fm, m);
    bool hayN = leerNovedad(fn, n);

    long posNovedad = 0;   // contador de registros leídos en Novedades

    // Como ya leímos el primero antes del bucle, posNovedad debe empezar en 1
    if (hayN) posNovedad = 1;

    ferr << "LISTADO DE ERRORES DE ACTUALIZACION\n\n";

    // APAREO
    while (hayM || hayN) {

        if (hayM && hayN) {
            if (m.clave < n.clave) {
                // Maestro sin novedad: se copia tal cual
                fa.write(reinterpret_cast<char*>(&m), sizeof(m));
                hayM = leerMaestro(fm, m);
            } else if (n.clave < m.clave) {
                // Novedad con clave menor a maestro
                // Solo puede ser Alta válida; B o M son errores (no existe en Maestro)
                if (n.mov == 'A') {
                    RegMaestro nuevo;
                    nuevo.clave = n.clave;
                    strcpy(nuevo.nombre, n.nombre);
                    nuevo.saldo = n.saldo;
                    fa.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
                } else if (n.mov == 'B') {
                    ferr << "Error: Baja inexistente. "
                         << "Clave = " << n.clave
                         << ", Pos Novedad = " << posNovedad << "\n";
                } else if (n.mov == 'M') {
                    ferr << "Error: Modificacion inexistente. "
                         << "Clave = " << n.clave
                         << ", Pos Novedad = " << posNovedad << "\n";
                }

                hayN = leerNovedad(fn, n);
                if (hayN) posNovedad++;
            } else {
                // m.clave == n.clave → mismo registro en maestro y novedades
                if (n.mov == 'A') {
                    // Alta existente: error
                    ferr << "Error: Alta existente. "
                         << "Clave = " << n.clave
                         << ", Pos Novedad = " << posNovedad << "\n";
                    // Se mantiene el maestro tal como estaba
                    fa.write(reinterpret_cast<char*>(&m), sizeof(m));
                } else if (n.mov == 'B') {
                    // Baja → no se copia el registro maestro (se elimina)
                    // (simplemente no lo escribimos)
                } else if (n.mov == 'M') {
                    // Modificacion → se actualizan campos con los de la novedad
                    RegMaestro modificado;
                    modificado.clave = m.clave;       // la clave no cambia
                    strcpy(modificado.nombre, n.nombre);
                    modificado.saldo = n.saldo;
                    fa.write(reinterpret_cast<char*>(&modificado), sizeof(modificado));
                }

                // Avanzar ambos
                hayM = leerMaestro(fm, m);
                hayN = leerNovedad(fn, n);
                if (hayN) posNovedad++;
            }
        } else if (hayM && !hayN) {
            // Solo quedan registros del maestro original → copiar todos
            fa.write(reinterpret_cast<char*>(&m), sizeof(m));
            hayM = leerMaestro(fm, m);
        } else if (!hayM && hayN) {
            // Solo quedan novedades → pueden ser Altas válidas o errores si B/M
            if (n.mov == 'A') {
                RegMaestro nuevo;
                nuevo.clave = n.clave;
                strcpy(nuevo.nombre, n.nombre);
                nuevo.saldo = n.saldo;
                fa.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            } else if (n.mov == 'B') {
                ferr << "Error: Baja inexistente. "
                     << "Clave = " << n.clave
                     << ", Pos Novedad = " << posNovedad << "\n";
            } else if (n.mov == 'M') {
                ferr << "Error: Modificacion inexistente. "
                     << "Clave = " << n.clave
                     << ", Pos Novedad = " << posNovedad << "\n";
            }

            hayN = leerNovedad(fn, n);
            if (hayN) posNovedad++;
        }
    }

    fm.close();
    fn.close();
    fa.close();
    ferr.close();

    cout << "✅ Actualizacion finalizada.\n";
    cout << "  Archivo maestro actualizado: MAESTRO_ACT.DAT\n";
    cout << "  Listado de errores: ERRORES.TXT\n";

    return 0;
}