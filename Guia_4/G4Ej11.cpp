/*
Id.Programa: G4Ej11.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: septiembre-2025 
Comentario.:
    Playa de estacionamiento por hora (18 pisos, 1800 cocheras).

    Archivos:
      - TARIFAS.DAT   : un registro con tarifas por hora (P, M, G).
      - COCHERAS.DAT  : 1800 registros, uno por cochera.
      - HISTORICO.DAT : ocupaciones completas (entrada/salida + importe).

    Durante el día se leen movimientos desde teclado:
      Codigo (E/S/F), Patente, Tipo (P/M/G), Piso (0..17), Hora (hh.mm)

    Se pide:
      1) Imprimir ticket por cada movimiento.
      2) Grabar un registro en HISTORICO.DAT por cada salida.
      3) Al final, imprimir listado por piso de autos que quedaron dentro.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
using namespace std;

// -------------------- Constantes --------------------

const int PISOS      = 18;
const int COCH_X_PISO = 100;
const int TOTAL_COCH  = PISOS * COCH_X_PISO;

// Suposición: cierre de día a las 24.00
const float HORA_CIERRE = 24.00f;

// -------------------- Estructuras --------------------

struct Tarifa {
    float peq;  // pequeño
    float med;  // mediano
    float gra;  // grande
};

struct Cochera {
    char patente[7];  // "" si está libre
    float horaOcup;   // hh.mm
    char tipo;        // 'P','M','G' o ' ' libre
};

struct Hist {
    char patente[7];
    float horaEntrada;
    float horaSalida;
    int   piso;
    float importe;
    char  tipo;
};

// -------------------- Helpers --------------------

float horasEntre(float h1, float h2) {
    // Convierte hh.mm a minutos y devuelve diferencia en horas (float)
    int h = static_cast<int>(h1);
    int m = static_cast<int>((h1 - h) * 100 + 0.5f);
    int min1 = h * 60 + m;

    h = static_cast<int>(h2);
    m = static_cast<int>((h2 - h) * 100 + 0.5f);
    int min2 = h * 60 + m;

    int diff = min2 - min1;
    if (diff < 0) diff = 0;  // por seguridad

    return diff / 60.0f;
}

const char* tipoLargo(char t) {
    switch (toupper(t)) {
        case 'P': return "Pequeno";
        case 'M': return "Mediano";
        case 'G': return "Grande";
        default:  return "Desconoc";
    }
}

float tarifaPorTipo(const Tarifa& tf, char t) {
    switch (toupper(t)) {
        case 'P': return tf.peq;
        case 'M': return tf.med;
        case 'G': return tf.gra;
        default:  return 0.0f;
    }
}

void normalizarPatente(char dst[7], const string& src) {
    // Copia en mayúsculas y asegura cierre con '\0'
    char temp[7] = {0};
    size_t n = src.size() < 6 ? src.size() : 6;
    for (size_t i = 0; i < n; ++i) {
        temp[i] = static_cast<char>(toupper(static_cast<unsigned char>(src[i])));
    }
    temp[6] = '\0';
    strcpy(dst, temp);
}

bool patenteVacia(const Cochera& c) {
    return c.patente[0] == '\0' || c.patente[0] == ' ';
}

// -------------------- Manejo de archivos base --------------------

bool cargarTarifas(Tarifa& tf) {
    ifstream ft("TARIFAS.DAT", ios::binary);
    if (!ft) {
        cout << "No existe TARIFAS.DAT. Ingrese tarifas por hora:\n";
        cout << "Pequeno: ";
        cin >> tf.peq;
        cout << "Mediano: ";
        cin >> tf.med;
        cout << "Grande : ";
        cin >> tf.gra;

        ofstream fo("TARIFAS.DAT", ios::binary | ios::trunc);
        if (!fo) {
            cerr << "No se pudo crear TARIFAS.DAT\n";
            return false;
        }
        fo.write(reinterpret_cast<char*>(&tf), sizeof(tf));
        fo.close();
        return true;
    } else {
        ft.read(reinterpret_cast<char*>(&tf), sizeof(tf));
        ft.close();
        return true;
    }
}

void inicializarCocheras(Cochera v[]) {
    for (int i = 0; i < TOTAL_COCH; ++i) {
        v[i].patente[0] = '\0';
        v[i].horaOcup   = 0.0f;
        v[i].tipo       = ' ';
    }
}

void cargarCocheras(Cochera v[]) {
    fstream fc("COCHERAS.DAT", ios::in | ios::binary);
    if (!fc) {
        // No existe: creamos vacías
        inicializarCocheras(v);
        ofstream fo("COCHERAS.DAT", ios::binary | ios::trunc);
        for (int i = 0; i < TOTAL_COCH; ++i) {
            fo.write(reinterpret_cast<char*>(&v[i]), sizeof(Cochera));
        }
        fo.close();
    } else {
        for (int i = 0; i < TOTAL_COCH; ++i) {
            if (!fc.read(reinterpret_cast<char*>(&v[i]), sizeof(Cochera))) {
                // Si el archivo era más chico, el resto se inicializa vacío
                for (int j = i; j < TOTAL_COCH; ++j) {
                    v[j].patente[0] = '\0';
                    v[j].horaOcup   = 0.0f;
                    v[j].tipo       = ' ';
                }
                break;
            }
        }
        fc.close();
    }
}

void guardarCocheras(Cochera v[]) {
    ofstream fo("COCHERAS.DAT", ios::binary | ios::trunc);
    if (!fo) {
        cerr << "No se pudo actualizar COCHERAS.DAT\n";
        return;
    }
    for (int i = 0; i < TOTAL_COCH; ++i) {
        fo.write(reinterpret_cast<char*>(&v[i]), sizeof(Cochera));
    }
    fo.close();
}

// -------------------- Búsquedas --------------------

int encontrarLibreEnPiso(Cochera v[], int piso) {
    if (piso < 0 || piso >= PISOS) return -1;
    for (int c = 0; c < COCH_X_PISO; ++c) {
        int idx = piso * COCH_X_PISO + c;
        if (patenteVacia(v[idx])) return idx;
    }
    return -1;
}

int encontrarLibreEnCualquierPiso(Cochera v[]) {
    for (int idx = 0; idx < TOTAL_COCH; ++idx) {
        if (patenteVacia(v[idx])) return idx;
    }
    return -1;
}

int buscarCocheraPorPatente(Cochera v[], const char patente[7]) {
    for (int i = 0; i < TOTAL_COCH; ++i) {
        if (!patenteVacia(v[i]) && strcmp(v[i].patente, patente) == 0) {
            return i;
        }
    }
    return -1;
}

// -------------------- Tickets --------------------

void imprimirTicketEntrada(float hora, int piso, char tipo, const char patente[7]) {
    cout << "\nDe ENTRADA\n";
    cout << "ENTRADA : " << fixed << setprecision(2) << hora << "\n";
    cout << "PISO    : " << setw(2) << piso << "\n";
    cout << "TIPO    : " << tipoLargo(tipo) << "\n";
    cout << "PATENTE : " << patente << "\n";
}

void imprimirTicketSalida(float horaEnt, float horaSal, int piso,
                          char tipo, const char patente[7], float importe) {
    cout << "\nDe SALIDA\n";
    cout << "ENTRADA : " << fixed << setprecision(2) << horaEnt << "\n";
    cout << "PISO    : " << setw(2) << piso << "\n";
    cout << "TIPO    : " << tipoLargo(tipo) << "\n";
    cout << "PATENTE : " << patente << "\n";
    cout << "SALIDA  : " << fixed << setprecision(2) << horaSal << "\n";
    cout << "IMPORTE : " << fixed << setprecision(2) << importe << "\n";
}

// -------------------- Procesos de entrada/salida --------------------

void procesarEntrada(Cochera v[], const Tarifa& tf,
                     const string& patStr, char tipo, int piso, float hora) {
    char patente[7];
    normalizarPatente(patente, patStr);

    // Buscar una cochera libre en el piso solicitado
    int idx = encontrarLibreEnPiso(v, piso);
    if (idx == -1) {
        // Buscar en cualquier piso
        idx = encontrarLibreEnCualquierPiso(v);
        if (idx == -1) {
            cout << "No hay cocheras disponibles para la patente " << patente << "\n";
            return;
        } else {
            piso = idx / COCH_X_PISO; // ajustar piso real
        }
    }

    // Ocupamos cochera
    strcpy(v[idx].patente, patente);
    v[idx].horaOcup = hora;
    v[idx].tipo     = tipo;

    imprimirTicketEntrada(hora, piso, tipo, patente);
}

void procesarSalida(Cochera v[], const Tarifa& tf, ofstream& histFile,
                    const string& patStr, char tipoMov, int pisoIngresado, float horaSalida) {
    (void)pisoIngresado; // no lo usamos, buscamos por patente
    char patente[7];
    normalizarPatente(patente, patStr);

    int idx = buscarCocheraPorPatente(v, patente);
    if (idx == -1) {
        cout << "No se encontro la patente " << patente << " dentro del estacionamiento.\n";
        return;
    }

    int piso = idx / COCH_X_PISO;
    float horaEnt = v[idx].horaOcup;
    char tipo = v[idx].tipo;

    float horas = horasEntre(horaEnt, horaSalida);
    float tarifaHora = tarifaPorTipo(tf, tipo);
    float importe = horas * tarifaHora;

    imprimirTicketSalida(horaEnt, horaSalida, piso, tipo, patente, importe);

    // Grabar en historico
    Hist h;
    strcpy(h.patente, patente);
    h.horaEntrada = horaEnt;
    h.horaSalida  = horaSalida;
    h.piso        = piso;
    h.importe     = importe;
    h.tipo        = tipo;
    histFile.write(reinterpret_cast<char*>(&h), sizeof(h));

    // Liberar cochera
    v[idx].patente[0] = '\0';
    v[idx].horaOcup   = 0.0f;
    v[idx].tipo       = ' ';
}

// -------------------- Listado final --------------------

void listarAutosRestantes(Cochera v[], const Tarifa& tf) {
    cout << "\nListado final de autos que quedaron dentro:\n";

    for (int piso = 0; piso < PISOS; ++piso) {
        bool hayEnPiso = false;

        for (int c = 0; c < COCH_X_PISO; ++c) {
            int idx = piso * COCH_X_PISO + c;
            if (!patenteVacia(v[idx])) {
                if (!hayEnPiso) {
                    cout << "\nPiso: " << piso << "\n";
                    cout << "Patente Tipo     ImporteEstimado\n";
                    hayEnPiso = true;
                }
                float horas = horasEntre(v[idx].horaOcup, HORA_CIERRE);
                float imp   = horas * tarifaPorTipo(tf, v[idx].tipo);
                cout << setw(7) << v[idx].patente << " "
                     << setw(8) << tipoLargo(v[idx].tipo) << " "
                     << fixed << setprecision(2) << imp << "\n";
            }
        }
    }
}

// -------------------- main --------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Tarifa tf;
    if (!cargarTarifas(tf)) {
        cerr << "Error cargando tarifas.\n";
        return 1;
    }

    Cochera cocheras[TOTAL_COCH];
    cargarCocheras(cocheras);

    ofstream hist("HISTORICO.DAT", ios::binary | ios::app);
    if (!hist) {
        cerr << "No se pudo abrir HISTORICO.DAT\n";
        return 1;
    }

    cout << "Ingrese movimientos (E/S/F). Formato:\n";
    cout << "E patente tipo piso hora   (ej: E ABC123 P 5 08.30)\n";
    cout << "S patente tipo piso hora   (ej: S ABC123 P 5 10.15)\n";
    cout << "F para finalizar.\n\n";

    char cod;
    while (true) {
        cout << "\nMovimiento: ";
        if (!(cin >> cod)) break;
        cod = static_cast<char>(toupper(static_cast<unsigned char>(cod)));
        if (cod == 'F') break;

        string pat;
        char tipo;
        int piso;
        float hora;

        cin >> pat >> tipo >> piso >> hora;

        tipo = static_cast<char>(toupper(static_cast<unsigned char>(tipo)));

        if (cod == 'E') {
            procesarEntrada(cocheras, tf, pat, tipo, piso, hora);
        } else if (cod == 'S') {
            procesarSalida(cocheras, tf, hist, pat, tipo, piso, hora);
        } else {
            cout << "Codigo de movimiento invalido (use E, S o F).\n";
        }
    }

    hist.close();

    listarAutosRestantes(cocheras, tf);
    guardarCocheras(cocheras);

    cout << "\nProceso finalizado.\n";
    return 0;
}