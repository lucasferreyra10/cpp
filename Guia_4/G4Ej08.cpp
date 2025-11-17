/*
Id.Programa: G4Ej08.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Proceso de facturación por relación entre archivos:
    Articulos, Clientes, Pedidos, Vendedores, Facturas y NrosInic.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

// ------------------ ESTRUCTURAS ------------------

struct Articulo {
    int  codArt;                // 1..100
    char marca[21];
    char desc[21];
    float precio;
    int stockActual;
    int stockMinimo;
    int puntoReposicion;
    char unidadMedida[11];
    char estado;                // 'A', 'I', etc.
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
    char tipoDoc[6];
    int  nroDoc;
};

// ------------------ FUNCIONES AUXILIARES ------------------

// Busca en NROSINIC.DAT el registro de tipo "FAC" y devuelve
// nro de documento + posición de ese registro en el archivo.
bool obtenerNroFacturaInicial(fstream &fNros, int &nroFact, streampos &posRegistro) {
    fNros.clear();
    fNros.seekg(0, ios::beg);

    NroInicial n;
    while (fNros.read(reinterpret_cast<char*>(&n), sizeof(n))) {
        if (strcmp(n.tipoDoc, "FAC") == 0) {
            posRegistro = fNros.tellg() - static_cast<streamoff>(sizeof(n));
            nroFact = n.nroDoc + 1;
            return true;
        }
    }
    return false;
}

// Carga vendedores en un vector desde VENDEDORES.DAT
void cargarVendedores(const char* nombreArch, vector<Vendedor> &vec) {
    ifstream fv(nombreArch, ios::binary);
    if (!fv) return;
    Vendedor v;
    while (fv.read(reinterpret_cast<char*>(&v), sizeof(v))) {
    vec.push_back(v);
    }
    fv.close();
}

// Busca vendedor por código en el vector
Vendedor* buscarVendedor(vector<Vendedor> &vec, int codVend) {
    for (auto &v : vec)
        if (v.codVend == codVend) return &v;
    return nullptr;
}

// ------------------ PROGRAMA PRINCIPAL ------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Archivos
    fstream fArt("ARTICULOS.DAT", ios::in | ios::out | ios::binary);
    if (!fArt) {
        cerr << "No se pudo abrir ARTICULOS.DAT\n";
        return 1;
    }

    ifstream fCli("CLIENTES.DAT", ios::binary);
    if (!fCli) {
        cerr << "No se pudo abrir CLIENTES.DAT\n";
        return 1;
    }

    ifstream fPed("PEDIDOS.DAT", ios::binary);
    if (!fPed) {
        cerr << "No se pudo abrir PEDIDOS.DAT\n";
        return 1;
    }

    // Vendedores se cargan a memoria
    vector<Vendedor> vendedores;
    cargarVendedores("VENDEDORES.DAT", vendedores);

    ofstream fFact("FACTURAS.DAT", ios::binary | ios::app);
    if (!fFact) {
        cerr << "No se pudo abrir FACTURAS.DAT\n";
        return 1;
    }

    fstream fNros("NROSINIC.DAT", ios::in | ios::out | ios::binary);
    if (!fNros) {
        cerr << "No se pudo abrir NROSINIC.DAT\n";
        return 1;
    }

    // Obtener número inicial de factura
    int nroFact;
    streampos posNroFact;
    if (!obtenerNroFacturaInicial(fNros, nroFact, posNroFact)) {
        cerr << "No se pudo obtener tipoDoc FAC en NROSINIC.DAT\n";
        return 1;
    }

    int fechaFact;
    cout << "Ingrese fecha de facturacion (ddmmaa): ";
    cin >> fechaFact;

    // Lectura inicial de pedidos
    Pedido ped;
    bool hayPed = static_cast<bool>(fPed.read(reinterpret_cast<char*>(&ped), sizeof(ped)));

    // (Opcional) Cargar clientes a memoria para acceso rápido
    vector<Cliente> clientes;
    {
        Cliente c;
        while (fCli.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            clientes.push_back(c);
        }
        fCli.close();
    }

    auto buscarCliente = [&](int codCli) -> Cliente* {
        for (auto &c : clientes)
            if (c.codCli == codCli) return &c;
        return nullptr;
    };

    Articulo art;

    // ------------ PROCESO PRINCIPAL (POR CLIENTE) ------------

    while (hayPed) {
        int cliAct = ped.codCli;
        Cliente* cli = buscarCliente(cliAct);
        if (!cli) {
            // En un ejercicio completo, acá deberías registrar error de inconsistencia
            cout << "Cliente " << cliAct << " no encontrado. Se saltean sus pedidos.\n";
        }

        float totalFactura = 0.0f;

        cout << "\nProcesando cliente " << cliAct << "...\n";

        // Pedidos de este cliente
        while (hayPed && ped.codCli == cliAct) {
            int codArt = ped.codArt;
            int cant   = ped.cantidad;

            // Leer artículo desde archivo relativo
            // Posición física ~ codArt
            fArt.clear();
            fArt.seekg(codArt * sizeof(Articulo), ios::beg);
            if (!fArt.read(reinterpret_cast<char*>(&art), sizeof(art))) {
                cout << "Articulo " << codArt << " inexistente.\n";
            } else {
                float importeLinea = cant * art.precio;
                totalFactura += importeLinea;

                // Actualizar stock
                art.stockActual -= cant;
                fArt.seekp(codArt * sizeof(Articulo), ios::beg);
                fArt.write(reinterpret_cast<char*>(&art), sizeof(art));
            }

            // Siguiente pedido
            hayPed = static_cast<bool>(fPed.read(reinterpret_cast<char*>(&ped), sizeof(ped)));
        }

        if (cli) {
            // Emitir factura para este cliente (si tuvo pedidos)
            if (totalFactura > 0.0f) {
                Factura fac{};
                fac.nroFactura = nroFact++;
                fac.fecha = fechaFact;
                fac.codCli = cliAct;
                fac.importe = totalFactura;
                fac.estado = 'A'; // adeuda

                fFact.write(reinterpret_cast<char*>(&fac), sizeof(fac));

                // Actualizar saldo del cliente
                cli->saldo += totalFactura;

                // Actualizar vendedor
                Vendedor* vend = buscarVendedor(vendedores, cli->codVendedor);
                if (vend) {
                    float comision = totalFactura * vend->porcComision / 100.0f;
                    vend->importeAcumulado += comision;
                }
            }
        }
    }

    // ------------ ACTUALIZAR CLIENTES Y VENDEDORES ------------

    // Regrabar CLIENTES.DAT actualizado
    {
        ofstream fCliOut("CLIENTES_ACT.DAT", ios::binary | ios::trunc);
        for (const auto &c : clientes) {
            fCliOut.write(reinterpret_cast<const char*>(&c), sizeof(c));
        }
        fCliOut.close();
        // Podrías luego renombrar CLIENTES_ACT.DAT a CLIENTES.DAT manualmente
    }

    // Regrabar VENDEDORES.DAT actualizado
    {
        ofstream fVendOut("VENDEDORES_ACT.DAT", ios::binary | ios::trunc);
        for (const auto &v : vendedores) {
            fVendOut.write(reinterpret_cast<const char*>(&v), sizeof(v));
        }
        fVendOut.close();
    }

    // ------------ ACTUALIZAR NROSINIC.DAT ------------

    // Volvemos a la posición del registro "FAC" y grabamos el último nro usado
    NroInicial n;
    fNros.clear();
    fNros.seekg(posNroFact, ios::beg);
    fNros.read(reinterpret_cast<char*>(&n), sizeof(n));
    n.nroDoc = nroFact - 1; // último emitido
    fNros.seekp(posNroFact, ios::beg);
    fNros.write(reinterpret_cast<char*>(&n), sizeof(n));
    fNros.close();

    cout << "\nProceso de facturacion finalizado.\n";
    return 0;
}
