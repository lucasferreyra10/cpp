/*
Id.Programa: G4Ej17.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025
Comentario.:
    Control de pagos mensuales de pólizas de seguros.

    Archivos:
      a) POLIZAS.DAT  (ordenado por Nro. de póliza)
         - NroPoliza (8 chars)
         - NroCliente (8 chars)
         - Rubro (3 chars)
         - ImporteMensual (double)

      b) CLIENTES.DAT (ordenado por NroCliente, máx. 7000)
         - NroCliente (8 chars)
         - ApellidoNombre (40 chars)
         - Domicilio (50 chars)

      c) PAGOS.DAT (sin orden)
         - NroPoliza (8 chars)
         - MesPagado (1..12)
         - ImportePagado (double)

    Se pide:
      1) Emitir un listado ORDENADO POR CLIENTE y PÓLIZA,
         mostrando los meses pagados ("P") y los impagos ("A").

      2) Mostrar recaudación por rubro:
            - Recaudación real (pagos efectivamente hechos)
            - Recaudación prevista (importe mensual * 12 por póliza)
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Poliza {
    char nroPol[9];
    char nroCli[9];
    char rubro[4];
    double importe;
};

struct Cliente {
    char nroCli[9];
    char apeNom[41];
    char dom[51];
};

struct Pago {
    char nroPol[9];
    int mes;            // 1..12
    double importe;
};

struct RubroAcum {
    char rubro[4];
    double real;
    double prevista;
};

const int MAX_CLIENTES = 7000;
const int MAX_POLIZAS  = 20000;
const int MAX_RUBROS   = 500;

// Comparación para ordenar por cliente y luego póliza
int cmpPolizaCliente(const Poliza& a, const Poliza& b) {
    int r = strcmp(a.nroCli, b.nroCli);
    if (r != 0) return r;
    return strcmp(a.nroPol, b.nroPol);
}

// Búsqueda binaria de cliente
int buscarCliente(Cliente v[], int n, const char *clave) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int m = (izq + der) / 2;
        int cmp = strcmp(v[m].nroCli, clave);
        if (cmp == 0) return m;
        if (cmp < 0) izq = m + 1;
        else der = m - 1;
    }
    return -1;
}

// Encontrar o crear rubro
int buscarOCrearRubro(RubroAcum vr[], int &cant, const char *rubro) {
    for (int i = 0; i < cant; i++)
        if (strcmp(vr[i].rubro, rubro) == 0)
            return i;

    strcpy(vr[cant].rubro, rubro);
    vr[cant].real = 0;
    vr[cant].prevista = 0;
    cant++;
    return cant - 1;
}

int main() {

    // --- CARGA DE ARCHIVOS ---

    // Clientes
    Cliente vecCli[MAX_CLIENTES];
    int cantCli = 0;

    ifstream fCli("CLIENTES.DAT", ios::binary);
    while (fCli.read((char*)&vecCli[cantCli], sizeof(Cliente)))
        cantCli++;
    fCli.close();

    // Polizas
    Poliza vecPol[MAX_POLIZAS];
    int cantPol = 0;

    ifstream fPol("POLIZAS.DAT", ios::binary);
    while (fPol.read((char*)&vecPol[cantPol], sizeof(Poliza)))
        cantPol++;
    fPol.close();

    // Pagos → matriz de 0/1
    bool pagado[MAX_POLIZAS][13] = {false};

    ifstream fPag("PAGOS.DAT", ios::binary);
    Pago reg;
    while (fPag.read((char*)&reg, sizeof(Pago))) {
        for (int i = 0; i < cantPol; i++) {
            if (strcmp(vecPol[i].nroPol, reg.nroPol) == 0 &&
                reg.mes >= 1 && reg.mes <= 12)
                pagado[i][reg.mes] = true;
        }
    }
    fPag.close();

    // --- ORDENAR POLIZAS POR CLIENTE Y PÓLIZA ---
    for (int i = 0; i < cantPol - 1; i++)
        for (int j = i + 1; j < cantPol; j++)
            if (cmpPolizaCliente(vecPol[i], vecPol[j]) > 0)
                swap(vecPol[i], vecPol[j]);

    // --- LISTADO 1 ---
    cout << "Listado de clientes con cuotas impagas" << endl;

    char clienteActual[9] = "XXXXXXXX";
    for (int i = 0; i < cantPol; i++) {

        if (strcmp(clienteActual, vecPol[i].nroCli) != 0) {
            strcpy(clienteActual, vecPol[i].nroCli);
            int pos = buscarCliente(vecCli, cantCli, clienteActual);

            cout << "\nCliente : " << clienteActual << endl;
            cout << "Apellido y Nombre: " 
                 << ((pos != -1) ? vecCli[pos].apeNom : "----") << endl;

            cout << "Poliza  Rubro   ----Meses Pagados----" << endl;
        }

        cout << vecPol[i].nroPol << "  " << vecPol[i].rubro << "   ";

        for (int m = 1; m <= 12; m++)
            cout << (pagado[i][m] ? "P " : "A ");

        cout << endl;
    }

    // --- LISTADO 2: RECAUDACION POR RUBRO ---
    RubroAcum vecRub[MAX_RUBROS];
    int cantRub = 0;

    for (int i = 0; i < cantPol; i++) {
        int r = buscarOCrearRubro(vecRub, cantRub, vecPol[i].rubro);

        vecRub[r].prevista += vecPol[i].importe * 12;

        for (int m = 1; m <= 12; m++)
            if (pagado[i][m])
                vecRub[r].real += vecPol[i].importe;
    }

    cout << "\nRecaudacion por Rubro" << endl;
    cout << "Rubro    Real        Prevista" << endl;

    for (int r = 0; r < cantRub; r++) {
        cout << setw(4) << vecRub[r].rubro << "   "
             << setw(10) << fixed << setprecision(2) << vecRub[r].real << "   "
             << setw(10) << vecRub[r].prevista << endl;
    }

    return 0;
}
