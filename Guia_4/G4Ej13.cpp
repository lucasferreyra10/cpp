/*
Id.Programa: G4Ej13.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Ejercicio 13 - Deportes

    Archivo de entrada: Deportes.dat (sin orden)
      - Codigo de Deporte (3 digitos)
      - Nombre del Deporte (cad30)

    El programa:
      1) Lee todos los deportes, los ordena por codigo en memoria,
         emite el listado y graba Deportes_Ord.dat en forma ordenada.
      2) Emite el mismo listado pero en forma invertida por tres metodos:
         a) Lectura hacia atras.
         b) Direccionamiento directo (seekg por numero de registro).
         c) Copia inversa en archivo auxiliar.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

// -------------------- Estructuras --------------------

#pragma pack(push,1)   // ⬅️ Desactiva padding de struct
struct Deporte {
    int codigo;         // 4 bytes
    char nombre[31];    // 31 bytes
};
#pragma pack(pop)       // ⬅️ Reactiva alignment normal


// -------------------- Utilidades --------------------

void mostrarRegistro(const Deporte& d) {
    cout << "Codigo: " << setw(3) << setfill('0') << d.codigo
         << "  Nombre: " << setfill(' ') << d.nombre << "\n";
}

// -------------------- Paso 1: leer y ordenar --------------------

bool leerYOrdenar(vector<Deporte>& vec) {
    ifstream f("Deportes.dat", ios::binary);
    if (!f) {
        cerr << "ERROR: No se pudo abrir Deportes.dat\n";
        return false;
    }

    Deporte d;
    while (f.read(reinterpret_cast<char*>(&d), sizeof(Deporte))) {
        vec.push_back(d);
    }
    f.close();

    if (vec.empty()) {
        cerr << "No hay registros en Deportes.dat\n";
        return false;
    }

    // Ordenar por codigo
    sort(vec.begin(), vec.end(),
         [](const Deporte& a, const Deporte& b) {
             return a.codigo < b.codigo;
         });

    return true;
}

bool grabarOrdenado(const vector<Deporte>& vec, const char* nombre) {
    ofstream f(nombre, ios::binary | ios::trunc);
    if (!f) {
        cerr << "ERROR: No se pudo crear " << nombre << "\n";
        return false;
    }

    for (const auto& d : vec) {
        f.write(reinterpret_cast<const char*>(&d), sizeof(Deporte));
    }

    f.close();
    return true;
}

// -------------------- Listados invertidos --------------------

void listadoInvertido_lecturaAtras(const char* nombre) {
    cout << "\n=== Listado invertido - Lectura hacia atras ===\n";

    ifstream f(nombre, ios::binary);
    if (!f) {
        cerr << "No se pudo abrir " << nombre << "\n";
        return;
    }

    f.seekg(0, ios::end);
    streamoff tam = f.tellg();
    streamoff tamReg = sizeof(Deporte);

    if (tam <= 0) {
        f.close();
        return;
    }

    // Posicionarse en el ultimo registro
    streamoff pos = tam - tamReg;

    Deporte d;
    while (pos >= 0) {
        f.seekg(pos, ios::beg);
        f.read(reinterpret_cast<char*>(&d), sizeof(Deporte));
        mostrarRegistro(d);
        pos -= tamReg;
    }

    f.close();
}

void listadoInvertido_direccionamientoDirecto(const char* nombre) {
    cout << "\n=== Listado invertido - Direccionamiento directo ===\n";

    ifstream f(nombre, ios::binary);
    if (!f) {
        cerr << "No se pudo abrir " << nombre << "\n";
        return;
    }

    f.seekg(0, ios::end);
    streamoff tam = f.tellg();
    streamoff tamReg = sizeof(Deporte);
    int cant = static_cast<int>(tam / tamReg);

    if (cant <= 0) {
        f.close();
        return;
    }

    Deporte d;
    for (int i = cant - 1; i >= 0; --i) {
        f.seekg(static_cast<streamoff>(i) * tamReg, ios::beg);
        f.read(reinterpret_cast<char*>(&d), sizeof(Deporte));
        mostrarRegistro(d);
    }

    f.close();
}

void listadoInvertido_archivoAuxiliar(const char* nombre) {
    cout << "\n=== Listado invertido - Copia en archivo auxiliar ===\n";

    ifstream f(nombre, ios::binary);
    if (!f) {
        cerr << "No se pudo abrir " << nombre << "\n";
        return;
    }

    // Creamos un auxiliar con los registros en orden inverso
    ofstream aux("Deportes_Aux.dat", ios::binary | ios::trunc);
    if (!aux) {
        cerr << "No se pudo crear Deportes_Aux.dat\n";
        f.close();
        return;
    }

    f.seekg(0, ios::end);
    streamoff tam = f.tellg();
    streamoff tamReg = sizeof(Deporte);
    int cant = static_cast<int>(tam / tamReg);

    if (cant <= 0) {
        f.close();
        aux.close();
        return;
    }

    Deporte d;

    // Copiamos desde el ultimo al primero en el auxiliar
    for (int i = cant - 1; i >= 0; --i) {
        f.seekg(static_cast<streamoff>(i) * tamReg, ios::beg);
        f.read(reinterpret_cast<char*>(&d), sizeof(Deporte));
        aux.write(reinterpret_cast<char*>(&d), sizeof(Deporte));
    }

    f.close();
    aux.close();

    // Ahora mostramos leyendo normalmente el auxiliar
    ifstream fa("Deportes_Aux.dat", ios::binary);
    if (!fa) {
        cerr << "No se pudo reabrir Deportes_Aux.dat\n";
        return;
    }

    while (fa.read(reinterpret_cast<char*>(&d), sizeof(Deporte))) {
        mostrarRegistro(d);
    }

    fa.close();
}

// -------------------- main --------------------

int main() {
    vector<Deporte> deportes;

    // 1) Leer Deportes.dat y ordenar en memoria
    if (!leerYOrdenar(deportes)) {
        return 1;
    }

    cout << "=== Listado ordenado por codigo de Deporte ===\n";
    for (const auto& d : deportes) {
        mostrarRegistro(d);
    }

    // Grabar archivo ordenado (optimiza espacio: un solo archivo ordenado)
    const char* nombreOrd = "Deportes_Ord.dat";
    if (!grabarOrdenado(deportes, nombreOrd)) {
        return 1;
    }

    // 2) Listados invertidos por tres metodos

    listadoInvertido_lecturaAtras(nombreOrd);
    listadoInvertido_direccionamientoDirecto(nombreOrd);
    listadoInvertido_archivoAuxiliar(nombreOrd);

    cout << "\nProceso finalizado.\n";
    return 0;
}
