/*
Id.Programa: G4Ej10.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: agosto-2025 
Comentario.:
    Direccion de Rentas: Proceso de deuda actualizada por contribuyente.

    Archivos:
      DEUDA.DAT:
        - RegDeuda (cabecera + cuotas)
        - Ordenado por nroCbte, anio, mes.
      INDICES.DAT:
        - RegIndice (anio, mes, coef)
      CONTRIBUYENTES.DAT:
        - Nros de contribuyentes que solicitaron su deuda

    Se emite:
      1) Listado de deuda actualizada por contribuyente solicitado.
      2) DEUDA_NUEVA.DAT: misma estructura que DEUDA.DAT pero solo con
         cuotas adeudadas para usar al dia siguiente (no incluye los que pagaron).
      3) COBRANZA.DAT: por cada contribuyente que pago, se graba:
         nroCbte, ApellidoNombre, Importe total pagado (actualizado).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <cstring>
using namespace std;

// ----------------- ESTRUCTURAS -----------------

struct RegDeuda {
    int  nroCbte;         // Nro contribuyente
    char apeNom[31];      // Apellido y Nombre
    int  mes;             // 0 = cabecera
    int  anio;            // 0 = cabecera
    float importeOrig;    // 0 en cabecera
    char estado;          // 'A' adeuda, 'P' pagada
};

struct RegIndice {
    int  anio;
    int  mes;
    float coef;           // Coeficiente para actualizar al mes actual
};

struct RegContribSolic {
    int nroCbte;
};

struct RegCobranza {
    int  nroCbte;
    char apeNom[31];
    float importeTotalPagado;
};

// ----------------- FUNCIONES AUXILIARES -----------------

// Carga indices en memoria
void cargarIndices(const char* nombreArch, vector<RegIndice> &indices) {
    ifstream fi(nombreArch, ios::binary);
    if (!fi) return;
    RegIndice r;
    while (fi.read(reinterpret_cast<char*>(&r), sizeof(r))) {
        indices.push_back(r);
    }
    fi.close();
}

// Busca coeficiente para (anio, mes). Si no lo encuentra, devuelve 1.0
float buscarCoef(const vector<RegIndice> &indices, int anio, int mes) {
    for (const auto &r : indices) {
        if (r.anio == anio && r.mes == mes) {
            return r.coef;
        }
    }
    return 1.0f; // sin indice -> sin actualizacion
}

// Carga numeros de contribuyentes solicitantes en un set
void cargarContribuyentes(const char* nombreArch, unordered_set<int> &contribs) {
    ifstream fc(nombreArch, ios::binary);
    if (!fc) return;
    RegContribSolic r;
    while (fc.read(reinterpret_cast<char*>(&r), sizeof(r))) {
        contribs.insert(r.nroCbte);
    }
    fc.close();
}

// ----------------- PROGRAMA PRINCIPAL -----------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Cargar indices
    vector<RegIndice> indices;
    cargarIndices("INDICES.DAT", indices);

    // Cargar contribuyentes solicitantes
    unordered_set<int> contribSolic;
    cargarContribuyentes("CONTRIBUYENTES.DAT", contribSolic);

    // Abrir archivos de deuda
    ifstream fDeuda("DEUDA.DAT", ios::binary);
    if (!fDeuda) {
        cerr << "❌ No se pudo abrir DEUDA.DAT\n";
        return 1;
    }

    ofstream fDeudaNueva("DEUDA_NUEVA.DAT", ios::binary | ios::trunc);
    if (!fDeudaNueva) {
        cerr << "❌ No se pudo crear DEUDA_NUEVA.DAT\n";
        return 1;
    }

    ofstream fCob("COBRANZA.DAT", ios::binary | ios::trunc);
    if (!fCob) {
        cerr << "❌ No se pudo crear COBRANZA.DAT\n";
        return 1;
    }

    RegDeuda reg;
    bool hayReg = static_cast<bool>(fDeuda.read(reinterpret_cast<char*>(&reg), sizeof(reg)));

    cout << "LISTADO DE DEUDA ACTUALIZADA POR CONTRIBUYENTE\n\n";

    // Corte de control por nroCbte
    while (hayReg) {
        int cbteAct = reg.nroCbte;
        char nombre[31];
        strcpy(nombre, reg.apeNom); // el header tiene el nombre

        bool esSolicitante = (contribSolic.find(cbteAct) != contribSolic.end());
        float totalPagadoAct = 0.0f;

        // El primer registro del grupo DEBE ser cabecera (mes/anio 0/0)
        if (reg.mes == 0 && reg.anio == 0) {
            if (!esSolicitante) {
                // Este contribuyente no vino a pagar -> copiamos cabecera a deuda nueva
                fDeudaNueva.write(reinterpret_cast<char*>(&reg), sizeof(reg));
            } else {
                // Cabecera: imprimir encabezado del listado
                cout << "Nro.Cbte.: " << setw(8) << setfill('0') << cbteAct
                     << "  Apellido, Nombre: " << setfill(' ') << nombre << "\n";
                cout << " AÑO MES IMPORTE ORIGEN IMPORTE ACTUAL\n";
            }

            // Avanzamos al siguiente registro (primera cuota o siguiente contribuyente)
            hayReg = static_cast<bool>(fDeuda.read(reinterpret_cast<char*>(&reg), sizeof(reg)));
        }

        // Procesar cuotas de este contribuyente
        while (hayReg && reg.nroCbte == cbteAct) {

            if (!esSolicitante) {
                // No vino a pagar: copiamos las cuotas tal cual al archivo nuevo
                fDeudaNueva.write(reinterpret_cast<char*>(&reg), sizeof(reg));
            } else {
                // Vino a pagar → calculamos importe actualizado para cada cuota ADEUDADA
                if (reg.estado == 'A') {
                    float coef = buscarCoef(indices, reg.anio, reg.mes);
                    float impAct = reg.importeOrig * coef;
                    totalPagadoAct += impAct;

                    cout << " "
                         << setw(4) << reg.anio << " "
                         << setw(2) << setfill('0') << reg.mes << setfill(' ')
                         << " "
                         << setw(12) << fixed << setprecision(2) << reg.importeOrig
                         << " "
                         << setw(12) << fixed << setprecision(2) << impAct
                         << "\n";
                } else {
                    // estado 'P': ya estaba pagada -> no se incluye en deuda ni cobranza
                }
            }

            // siguiente registro del archivo DEUDA
            hayReg = static_cast<bool>(fDeuda.read(reinterpret_cast<char*>(&reg), sizeof(reg)));
        }

        if (esSolicitante) {
            // Al final del contribuyente, si vino a pagar, grabamos la cobranza
            RegCobranza cob;
            cob.nroCbte = cbteAct;
            strcpy(cob.apeNom, nombre);
            cob.importeTotalPagado = totalPagadoAct;
            fCob.write(reinterpret_cast<char*>(&cob), sizeof(cob));

            cout << "  --> Importe total pagado: "
                 << fixed << setprecision(2) << totalPagadoAct << "\n\n";
        }
    }

    fDeuda.close();
    fDeudaNueva.close();
    fCob.close();

    cout << "\nProceso finalizado.\n";
    cout << "Archivo de deuda para el dia siguiente: DEUDA_NUEVA.DAT\n";
    cout << "Archivo de cobranza del dia: COBRANZA.DAT\n";

    return 0;
}
