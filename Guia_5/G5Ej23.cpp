/*
Id.Programa: G5Ej23.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Programa para facturación MoviTel.
    - Lee CATEGORIAS.DAT, CLIENTES.DAT y COMUNICACIONES.DAT.
    - Imprime la factura de cada cliente (ordenado por nroCliente) con este formato:
        Nro.Cliente: 9(9)    Razon Social: X(35)
        Domicilio: X(50)
        ABONO    ( <pulsos sin cargo> pulsos sin cargo )        <importeAbono>
        ADICIONAL( <pulsos adicionales> x imp. p/ pulso )     + <importeAdicional>
        T O T A L                                            <total>
    - Al final imprime listado ordenado por categoria y nroCliente de los clientes
      que tuvieron ALGÚN día con más de 50 pulsos. Para cada cliente muestra el día
      y la cantidad máxima de pulsos en un día.
    Suposición: "ABONO" es un cargo fijo mensual; pulsos sin cargo son pulsos incluidos;
    pulsos adicionales = max(0, totalMes - pulsosSinCargo).
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

struct Comunic {
    char nroCliente[10];
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

int main() {
    cout << fixed << setprecision(2);

    // Cargar categorias
    map<int, Categoria> categorias;
    {
        ifstream f("CATEGORIAS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir CATEGORIAS.DAT\n"; return 1; }
        Categoria c;
        while (f.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            categorias[c.codigo] = c;
        }
        f.close();
    }

    // Cargar clientes (ordenado por cliente según enunciado)
    map<string, Cliente> clientes;
    vector<string> ordenClientes;
    {
        ifstream f("CLIENTES.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir CLIENTES.DAT\n"; return 1; }
        Cliente cl;
        while (f.read(reinterpret_cast<char*>(&cl), sizeof(cl))) {
            string key = string(cl.nroCliente);
            clientes[key] = cl;
            ordenClientes.push_back(key);
        }
        f.close();
    }

    // Agregar estructuras para acumulados por cliente
    struct Acc {
        int totalPulsos = 0;
        int maxPulsosDia = 0;
        int diaMax = 0;
        map<int,int> porDia; // dia -> total pulsos that day
    };
    map<string, Acc> acum;

    // Leer comunicaciones (ordenado por cliente)
    {
        ifstream f("COMUNICACIONES.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir COMUNICACIONES.DAT\n"; return 1; }
        Comunic s;
        while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
            string cli = string(s.nroCliente);
            acum[cli].totalPulsos += s.pulsos;
            acum[cli].porDia[s.dia] += s.pulsos;
            if (acum[cli].porDia[s.dia] > acum[cli].maxPulsosDia) {
                acum[cli].maxPulsosDia = acum[cli].porDia[s.dia];
                acum[cli].diaMax = s.dia;
            }
        }
        f.close();
    }

    // Imprimir facturas por cliente (en el orden de CLIENTES.DAT, ordenClientes)
    cout << "\n===== FACTURAS MENSUALES MOVITEL =====\n\n";
    for (auto &k : ordenClientes) {
        Cliente cl = clientes[k];
        Acc a = acum[k]; // if not present, default Acc
        // category info
        int cat = cl.categoria;
        if (categorias.find(cat) == categorias.end()) {
            cerr << "Categoria no encontrada para cliente " << k << "\n";
            continue;
        }
        Categoria C = categorias[cat];

        int pulsosIncluidos = C.pulsosSinCargo;
        int adicionales = max(0, a.totalPulsos - pulsosIncluidos);
        double importeAdic = adicionales * C.importePulso;
        double importeAbono = C.importeAbono;
        double total = importeAbono + importeAdic;

        // Formato pedido
        cout << "Nro.Cliente: " << k << "    Razon Social: " << cl.razon << "\n";
        cout << "Domicilio: " << cl.domicilio << "\n";
        // ABONO line
        cout << left << setw(8) << "ABONO" 
             << " ( " << setw(3) << pulsosIncluidos << " pulsos sin cargo ) "
             << right << setw(10) << importeAbono << "\n";
        // ADICIONAL line
        cout << left << setw(8) << "ADICIONAL"
             << " ( " << setw(5) << adicionales << " x imp.pulso ) "
             << right << setw(10) << importeAdic << "\n";
        // TOTAL
        cout << setw(40) << " " << "T O T A L " << setw(10) << total << "\n";
        cout << "-----------------------------------------------\n\n";
    }

    // Lista final: clientes que tuvieron algun dia con mas de 50 pulsos
    struct Row {
        string nro;
        int categoria;
        int dia;
        int maxPulsos;
    };
    vector<Row> filas;
    for (auto &p : acum) {
        if (p.second.maxPulsosDia > 50) {
            // find client's category (if exists)
            if (clientes.find(p.first) == clientes.end()) continue;
            Row r;
            r.nro = p.first;
            r.categoria = clientes[p.first].categoria;
            r.dia = p.second.diaMax;
            r.maxPulsos = p.second.maxPulsosDia;
            filas.push_back(r);
        }
    }

    // ordenar por categoria y luego por nroCliente
    sort(filas.begin(), filas.end(), [](const Row &a, const Row &b){
        if (a.categoria != b.categoria) return a.categoria < b.categoria;
        return a.nro < b.nro;
    });

    cout << "\n===== LISTADO DE CLIENTES (ALGUN DIA > 50 PULSOS) =====\n";
    cout << left << setw(12) << "Categoria" << left << setw(12) << "Nro.Cliente" 
         << left << setw(8) << "Dia" << left << setw(10) << "MaxPulsos" << "\n";
    for (auto &r : filas) {
        cout << left << setw(12) << r.categoria << left << setw(12) << r.nro 
             << left << setw(8) << r.dia << left << setw(10) << r.maxPulsos << "\n";
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
