/*
Id.Programa: G5Ej15.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Simula la compra de doña Rosa recorriendo góndolas (ARTICULOS.DAT)
    y tacha requerimientos (REQUERIMIENTOS.DAT). Genera:
      1) Lista de productos comprados (cantidad y direccion en ARTICULOS.DAT)
      2) Ticket de la compra
      3) Ranking top-10 por importe total (descendente)
      4) Actualiza stock en ARTICULOS.DAT
      5) Genera REPOSICIONES.DAT (articulos con stockActual < stockMin),
         ordenado por (stockMin - stockActual) descendente.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

struct Art {
    int codigo;
    char descripcion[31];
    int stockActual;
    int stockMin;
    double precio;
    char unidad[11];
};

struct Req {
    char descripcion[31];
    int cantidad;
    int restante; // used during processing
};

struct CompraAgg {
    int artIndex;         // index in vector art
    long direccion;       // offset in ARTICULOS.DAT
    int cantidadComprada;
    double importeTotal;
};

struct Repos {
    int codigo;
    int stockActual;
    int stockMin;
    int diferencia;
};

// helpers: lowercase copy and substring search (case-insensitive)
string toLower(const char *s) {
    string res;
    for (int i = 0; s[i]; ++i) res.push_back(tolower((unsigned char)s[i]));
    return res;
}

bool containsInsensitive(const char *haystack, const char *needle) {
    string h = toLower(haystack);
    string n = toLower(needle);
    return (h.find(n) != string::npos);
}

int main() {
    cout << fixed << setprecision(2);

    // --- 1) Leer ARTICULOS.DAT (y almacenar offsets) ---
    ifstream fArt("ARTICULOS.DAT", ios::binary);
    if (!fArt) {
        cout << "No se pudo abrir ARTICULOS.DAT\n";
        return 1;
    }

    vector<Art> articulos;
    vector<long> offsets;
    while (true) {
        long pos = fArt.tellg();
        Art a;
        if (!fArt.read(reinterpret_cast<char*>(&a), sizeof(Art))) break;
        articulos.push_back(a);
        offsets.push_back(pos);
    }
    fArt.close();

    if (articulos.empty()) {
        cout << "ARTICULOS.DAT vacio.\n";
        return 1;
    }

    // --- 2) Leer REQUERIMIENTOS.DAT (lista anotada) ---
    vector<Req> reqs;
    ifstream fReq("REQUERIMIENTOS.DAT", ios::binary);
    if (!fReq) {
        cout << "No se encontro REQUERIMIENTOS.DAT. Termine el programa o cree un archivo con el generador.\n";
        return 1;
    }
    while (true) {
        Req r;
        if (!fReq.read(reinterpret_cast<char*>(&r), sizeof(Req))) break;
        r.restante = r.cantidad;
        reqs.push_back(r);
    }
    fReq.close();

    // --- 3) Simular recorrido por las góndolas: recorremos articulos en el orden del archivo ---
    // Para cada articulo, se comprueba si coincide (por substring) con alguna req pendiente.
    // Compramos lo que haga falta (hasta restante) o hasta agotar stock.
    vector<CompraAgg> comprasAgg; // aggregated per article (one entry per article that was bought)
    vector<int> compradoFlag(articulos.size(), 0); // to track first time purchase and preserve order
    vector<int> order; // indices in the order they were first purchased

    for (size_t ia = 0; ia < articulos.size(); ++ia) {
        Art &art = articulos[ia];
        bool anyBoughtThisArticle = false;

        for (size_t ir = 0; ir < reqs.size(); ++ir) {
            if (reqs[ir].restante <= 0) continue;
            if (art.stockActual <= 0) break;
            // match by substring case-insensitive
            if (containsInsensitive(art.descripcion, reqs[ir].descripcion)) {
                int qty = min(reqs[ir].restante, art.stockActual);
                if (qty > 0) {
                    // mark purchase
                    if (!compradoFlag[ia]) {
                        compradoFlag[ia] = 1;
                        order.push_back((int)ia);
                        CompraAgg ca;
                        ca.artIndex = (int)ia;
                        ca.direccion = offsets[ia];
                        ca.cantidadComprada = qty;
                        ca.importeTotal = qty * art.precio;
                        comprasAgg.push_back(ca);
                    } else {
                        // find existing agregation and update
                        for (auto &ca : comprasAgg) {
                            if (ca.artIndex == (int)ia) {
                                ca.cantidadComprada += qty;
                                ca.importeTotal += qty * art.precio;
                                break;
                            }
                        }
                    }

                    art.stockActual -= qty;
                    reqs[ir].restante -= qty;
                    anyBoughtThisArticle = true;
                }
            }
        }
        // continue to next article (next gondola)
    }

    // --- 4) Generar Lista de productos comprados (cantidad + direccion) ---
    cout << "\nLista de productos comprados (direccion = offset en ARTICULOS.DAT):\n";
    cout << "Cantidad  Direccion\n";
    for (auto &ca : comprasAgg) {
        cout << setw(8) << ca.cantidadComprada << "  " << setw(10) << ca.direccion << "\n";
    }

    // --- 5) Emitir Ticket de la compra ---
    double totalAPagar = 0.0;
    int cantidadArticulosDistintos = (int)comprasAgg.size();
    int cantidadTotalUnidades = 0;
    cout << "\n--- TICKET DE COMPRA ---\n";
    cout << left << setw(12) << "Codigo" << left << setw(30) << "Descripcion" << right << setw(8) << "Cant"
         << right << setw(12) << "Precio" << right << setw(14) << "Total" << "\n";

    for (auto &ca : comprasAgg) {
        Art &a = articulos[ca.artIndex];
        double totalArt = ca.cantidadComprada * a.precio;
        cantidadTotalUnidades += ca.cantidadComprada;
        totalAPagar += totalArt;
        cout << left << setw(12) << a.codigo
             << left << setw(30) << a.descripcion
             << right << setw(8)  << ca.cantidadComprada
             << right << setw(12) << a.precio
             << right << setw(14) << totalArt << "\n";
    }

    cout << "\nCantidad de articulos (distintos): " << cantidadArticulosDistintos << "\n";
    cout << "Cantidad total de unidades: " << cantidadTotalUnidades << "\n";
    cout << "Total a Pagar : $ " << totalAPagar << "\n";

    // --- 6) Ranking de las 10 compras de mayor importe (por articulo) ---
    vector<CompraAgg> ranking = comprasAgg;
    sort(ranking.begin(), ranking.end(), [](const CompraAgg &x, const CompraAgg &y) {
        return x.importeTotal > y.importeTotal;
    });

    cout << "\nRanking de los " << (int)ranking.size() << " articulos de mayor importe (top 10):\n";
    cout << left << setw(12) << "Codigo" << right << setw(16) << "Importe\n";
    int topN = min((size_t)10, ranking.size());
    for (int i = 0; i < topN; ++i) {
        Art &a = articulos[ranking[i].artIndex];
        cout << left << setw(12) << a.codigo << right << setw(16) << ranking[i].importeTotal << "\n";
    }

    // --- 7) Actualizar stock en ARTICULOS.DAT ---
    // Reabrimos el archivo en modo lectura/escritura y escribimos registros actualizados en sus offsets
    fstream fArtUpd("ARTICULOS.DAT", ios::binary | ios::in | ios::out);
    if (!fArtUpd) {
        cout << "No se pudo abrir ARTICULOS.DAT para actualizar\n";
        return 1;
    }

    for (size_t i = 0; i < articulos.size(); ++i) {
        long pos = offsets[i];
        fArtUpd.seekp(pos, ios::beg);
        fArtUpd.write(reinterpret_cast<char*>(&articulos[i]), sizeof(Art));
    }
    fArtUpd.close();
    cout << "\nARTICULOS.DAT actualizado con nuevos stocks.\n";

    // --- 8) Generar REPOSICIONES.DAT: stockActual < stockMin, ordenado desc por (stockMin - stockActual) ---
    vector<Repos> repos;
    for (auto &a : articulos) {
        if (a.stockActual < a.stockMin) {
            Repos r;
            r.codigo = a.codigo;
            r.stockActual = a.stockActual;
            r.stockMin = a.stockMin;
            r.diferencia = a.stockMin - a.stockActual;
            repos.push_back(r);
        }
    }

    sort(repos.begin(), repos.end(), [](const Repos &x, const Repos &y) {
        return x.diferencia > y.diferencia;
    });

    if (!repos.empty()) {
        ofstream fRepos("REPOSICIONES.DAT", ios::binary);
        if (!fRepos) {
            cout << "No se pudo crear REPOSICIONES.DAT\n";
            return 1;
        }
        for (auto &r : repos) {
            fRepos.write(reinterpret_cast<char*>(&r), sizeof(Repos));
        }
        fRepos.close();
        cout << "REPOSICIONES.DAT creado con " << repos.size() << " registros.\n";
    } else {
        cout << "No hay articulos que requieran reposicion.\n";
    }

    // --- Fin ---
    cout << "\nProceso terminado.\n";

    return 0;
}
