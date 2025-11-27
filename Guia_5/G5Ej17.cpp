/*
Id.Programa: G5Ej17.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    arma listas enlazadas de Rubros -> Articulos (listas por rubro)
    Imprime:
      - Listado por rubros y articulos (fecha y hoja)
      - Rubro con mayor cantidad de items
      - Valores porcentuales por rubro (valor = stockActual * precio)
    Genera:
      - ARTICULO.IDX con entradas ordenadas por rubro y por codigo de articulo:
         { clave (codigo articulo), referencia (offset en ARTICULOS.DAT) }
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>

using namespace std;

// Estructuras de disco (coinciden con el generador)
struct Articulo {
    char codigo[8];       // 7 + '\0'
    char descripcion[31];
    int stockActual;
    int stockMin;
    char codigoRubro[6];  // 5 + '\0'
    char unidad[11];
    double precio;
};

struct Rubro {
    char codigo[6];       // 5 + '\0'
    char descripcion[31];
};

// Nodos en memoria
struct ArtNode {
    char codigo[8];
    long long offset;      // referencia en ARTICULOS.DAT
    ArtNode* sig;
};

struct RubNode {
    char codigo[6];
    char descripcion[31];
    ArtNode* primera;      // puntero a la lista de articulos de este rubro
    RubNode* sig;
};

// Entrada de indice
struct IndexEntry {
    char clave[8];
    long long offset;
};

// Helpers
string fechaHoy() {
    time_t t = time(nullptr);
    tm *lt = localtime(&t);
    char buf[16];
    sprintf(buf, "%02d-%02d-%02d", lt->tm_mday, lt->tm_mon+1, (lt->tm_year+1900)%100);
    return string(buf);
}

// Inserta rubro al final (RUBROS.DAT ya viene ordenado)
void insertarRubroFinal(RubNode*& cabeza, const Rubro& r) {
    RubNode* nodo = new RubNode;
    strncpy(nodo->codigo, r.codigo, sizeof(nodo->codigo));
    nodo->codigo[sizeof(nodo->codigo)-1] = '\0';
    strncpy(nodo->descripcion, r.descripcion, sizeof(nodo->descripcion));
    nodo->descripcion[sizeof(nodo->descripcion)-1] = '\0';
    nodo->primera = nullptr;
    nodo->sig = nullptr;

    if (!cabeza) {
        cabeza = nodo;
    } else {
        RubNode* p = cabeza;
        while (p->sig) p = p->sig;
        p->sig = nodo;
    }
}

// Inserta artículo en lista del rubro en orden por codigo (asc)
void insertarArticuloOrdenado(ArtNode*& head, const char* codigo, long long offset) {
    ArtNode* nuevo = new ArtNode;
    strncpy(nuevo->codigo, codigo, sizeof(nuevo->codigo));
    nuevo->codigo[sizeof(nuevo->codigo)-1] = '\0';
    nuevo->offset = offset;
    nuevo->sig = nullptr;

    if (!head || strcmp(nuevo->codigo, head->codigo) < 0) {
        nuevo->sig = head;
        head = nuevo;
        return;
    }
    ArtNode* p = head;
    while (p->sig && strcmp(p->sig->codigo, nuevo->codigo) < 0) p = p->sig;
    nuevo->sig = p->sig;
    p->sig = nuevo;
}

// Buscar nodo rubro por codigo (devuelve puntero o nullptr)
RubNode* buscarRubro(RubNode* cabeza, const char* codigo) {
    RubNode* p = cabeza;
    while (p) {
        if (strcmp(p->codigo, codigo) == 0) return p;
        p = p->sig;
    }
    return nullptr;
}

// Cuenta articulos en un rubro
int contarArticulos(ArtNode* head) {
    int c = 0;
    while (head) { c++; head = head->sig; }
    return c;
}

// Obtiene valor monetario del rubro (sum stockActual * precio) leyendo ARTICULOS.DAT en offset
double valorRubroDesdeArticulos(ArtNode* head, ifstream &fArt) {
    double total = 0.0;
    ArtNode* p = head;
    Articulo a;
    while (p) {
        fArt.seekg(p->offset, ios::beg);
        if (fArt.read(reinterpret_cast<char*>(&a), sizeof(Articulo))) {
            total += static_cast<double>(a.stockActual) * a.precio;
        }
        p = p->sig;
    }
    return total;
}

int main() {
    cout << fixed << setprecision(2);

    // 1) Leer RUBROS.DAT y crear lista de rubros (debiera estar ordenado)
    RubNode* rubros = nullptr;
    {
        ifstream fR("RUBROS.DAT", ios::binary);
        if (!fR) {
            cout << "No se pudo abrir RUBROS.DAT\n";
            return 1;
        }
        Rubro r;
        while (fR.read(reinterpret_cast<char*>(&r), sizeof(Rubro))) {
            insertarRubroFinal(rubros, r);
        }
        fR.close();
    }

    if (!rubros) {
        cout << "RUBROS.DAT vacio o no existe.\n";
        return 1;
    }

    // 2) Leer ARTICULOS.DAT y crear nodos por rubro (lista por rubro, insertando ordenado por codigo)
    ifstream fA("ARTICULOS.DAT", ios::binary);
    if (!fA) {
        cout << "No se pudo abrir ARTICULOS.DAT\n";
        return 1;
    }

    // Recorremos ARTICULOS.DAT y obtenemos offset de cada registro
    while (true) {
        long long pos = static_cast<long long>(fA.tellg());
        Articulo art;
        if (!fA.read(reinterpret_cast<char*>(&art), sizeof(Articulo))) break;

        // buscar rubro correspondiente
        RubNode* rnode = buscarRubro(rubros, art.codigoRubro);
        if (rnode) {
            // insertar en lista de articulos del rubro en orden por codigo
            insertarArticuloOrdenado(rnode->primera, art.codigo, pos);
        } else {
            // Si rubro no existe en lista de rubros, lo podemos ignorar o agregarlo.
            // Aquí lo ignoramos pero mostramos aviso
            cerr << "Advertencia: articulo " << art.codigo << " con rubro " << art.codigoRubro << " sin rubro definido.\n";
        }
    }

    // 3) Generar listado por rubros y artículos (imprime fecha y "Hoja: 1")
    string fecha = fechaHoy();
    cout << "Fecha : " << fecha << "  Hoja : 001\n";
    cout << "Listado por Rubros y Artículos\n\n";

    // Recorremos rubros y listamos articulos
    int maxItems = 0;
    char rubMaxCodigo[6] = "";
    char rubMaxNombre[31] = "";

    // Para calculos de porcentaje: sum total valor
    double totalValorGlobal = 0.0;

    // Primero calculemos valores por rubro leyendo ARTICULOS.DAT (abrir otro ifstream para lectura random)
    ifstream fA2("ARTICULOS.DAT", ios::binary);
    if (!fA2) {
        cout << "No se pudo abrir ARTICULOS.DAT (segunda lectura)\n";
        return 1;
    }

    // Recorremos rubros para calcular total global
    for (RubNode* r = rubros; r; r = r->sig) {
        double val = valorRubroDesdeArticulos(r->primera, fA2);
        totalValorGlobal += val;
    }

    // Ahora imprimimos detalle por rubro
    cout << left;
    for (RubNode* r = rubros; r; r = r->sig) {
        cout << "Cód.Rubro : " << r->codigo << "  Nombre : " << r->descripcion << "\n";
        cout << left << setw(12) << "Cód.Art." << left << setw(32) << "Nombre" << right << setw(12) << "Precio\n";

        // Recorremos articulos del rubro y leemos su descripcion y precio desde ARTICULOS.DAT
        ArtNode* aN = r->primera;
        int cnt = 0;
        while (aN) {
            Articulo a;
            fA2.seekg(aN->offset, ios::beg);
            if (fA2.read(reinterpret_cast<char*>(&a), sizeof(Articulo))) {
                cout << left << setw(12) << a.codigo << left << setw(32) << a.descripcion << right << setw(12) << a.precio << "\n";
                cnt++;
            }
            aN = aN->sig;
        }
        cout << "Cantidad de ítem : " << cnt << "\n\n";

        if (cnt > maxItems) {
            maxItems = cnt;
            strncpy(rubMaxCodigo, r->codigo, sizeof(rubMaxCodigo));
            strncpy(rubMaxNombre, r->descripcion, sizeof(rubMaxNombre));
        }
    }

    // 4) Rubro con mayor cantidad de items
    if (maxItems > 0) {
        cout << "Rubro con mayor cantidad de items: " << rubMaxCodigo << " - " << rubMaxNombre << " ( " << maxItems << " items )\n\n";
    } else {
        cout << "No se encontraron articulos en los rubros.\n\n";
    }

    // 5) Listado de valores porcentuales por Rubro (usar totalValorGlobal)
    cout << "Listado de valores porcentuales por Rubro\n";
    cout << left << setw(8) << "Cód.Rubro" << right << setw(12) << "Valor" << right << setw(10) << "  %\n";

    // Re-usa fA2 (pos actual no importa)
    for (RubNode* r = rubros; r; r = r->sig) {
        double val = valorRubroDesdeArticulos(r->primera, fA2);
        double pct = (totalValorGlobal > 0.0) ? (val * 100.0 / totalValorGlobal) : 0.0;
        cout << left << setw(8) << r->codigo << right << setw(12) << val << right << setw(10) << pct << "\n";
    }

    fA2.close();

    // 6) Generar archivo de índice ARTICULO.IDX
    // El índice debe seguir orden lógico: por rubro (en el orden de RUBROS.DAT) y dentro por código de artículo
    ofstream fIdx("ARTICULO.IDX", ios::binary);
    if (!fIdx) {
        cout << "No se pudo crear ARTICULO.IDX\n";
    } else {
        // Recorremos rubros y sus listas de articulos (ya ordenadas por codigo)
        for (RubNode* r = rubros; r; r = r->sig) {
            ArtNode* aN = r->primera;
            while (aN) {
                IndexEntry ie;
                strncpy(ie.clave, aN->codigo, sizeof(ie.clave));
                ie.clave[sizeof(ie.clave)-1] = '\0';
                ie.offset = aN->offset;
                fIdx.write(reinterpret_cast<char*>(&ie), sizeof(IndexEntry));
                aN = aN->sig;
            }
        }
        fIdx.close();
        cout << "\nArchivo ARTICULO.IDX generado.\n";
    }

    // 7) Liberar memoria
    for (RubNode* r = rubros; r; ) {
        ArtNode* a = r->primera;
        while (a) {
            ArtNode* t = a;
            a = a->sig;
            delete t;
        }
        RubNode* t = r;
        r = r->sig;
        delete t;
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
