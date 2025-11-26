/*
Id.Programa: G5Ej14.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Procesa archivos relativos a Bienes Personales:
      - DJ.DAT     : Declaraciones juradas (ordenadas por Apellido-Nombre)
      - BIENES.DAT : Registros de bienes (cabeceras con tipo '*' + bienes)
      - IMPUESTOS.DAT : Tabla de rangos (monto, porcentaje) ordenada por monto asc.

    Genera:
      1) Listado de Bienes Personales que pagan impuesto (si total >= monto minimo)
      2) Archivo GRANDES.DAT con personas cuyo total > mayor monto de IMPUESTOS.DAT
         (registro: Apellido-Nombre, T-Nro.Doc., Importe Total)
      3) Actualiza el campo totalBienes en DJ.DAT

    Supuestos / notas:
      - Estructuras binarias simples y tamaños fijos según enunciado.
      - BIENES.DAT: registro cabecera tiene tipoBien == "*" y documento igual al de DJ.
      - Si no hay impuesto aplicable (total < primer monto), el % = 0.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

struct DJ {
    char nombre[30];
    char direccion[30];
    char localidad[20];
    char cp[5];
    char telefono[15];
    char documento[12];
    double totalBienes; // se actualizará
};

struct Bien {
    char documento[12];
    char tipoBien[20];
    double importe;
    char descripcion[50];
};

struct Impuesto {
    double monto;
    int porcentaje;
};

struct Grande {
    char nombre[30];
    char documento[12];
    double total;
};

int main() {
    // --- 1) Cargar IMPUESTOS.DAT ---
    vector<Impuesto> impuestos;
    {
        ifstream fImp("IMPUESTOS.DAT", ios::binary);
        if (!fImp) {
            cout << "No se pudo abrir IMPUESTOS.DAT" << endl;
            return 1;
        }
        Impuesto imp;
        while (fImp.read(reinterpret_cast<char*>(&imp), sizeof(Impuesto))) {
            impuestos.push_back(imp);
        }
        fImp.close();
        if (impuestos.empty()) {
            cout << "IMPUESTOS.DAT vacio. Abortando." << endl;
            return 1;
        }
    }

    double minMonto = impuestos.front().monto;
    double maxMonto = impuestos.back().monto;

    // --- 2) Cargar DJ.DAT en memoria (para actualizar luego) ---
    vector<DJ> vDJ;
    {
        ifstream fDJ("DJ.DAT", ios::binary);
        if (!fDJ) {
            cout << "No se pudo abrir DJ.DAT" << endl;
            return 1;
        }
        DJ rec;
        while (fDJ.read(reinterpret_cast<char*>(&rec), sizeof(DJ))) {
            vDJ.push_back(rec);
        }
        fDJ.close();
    }

    // --- 3) Procesar BIENES.DAT, persona por persona ---
    vector<Grande> grandes; // para almacenar quienes superan maxMonto

    ifstream fBien("BIENES.DAT", ios::binary);
    if (!fBien) {
        cout << "No se pudo abrir BIENES.DAT" << endl;
        return 1;
    }

    cout << fixed << setprecision(2);

    cout << "Listado de Bienes Personales que pagan Impuesto\n";
    cout << "------------------------------------------------\n\n";

    Bien buf;
    while (fBien.read(reinterpret_cast<char*>(&buf), sizeof(Bien))) {
        // Detectamos registro cabecera por tipoBien == "*" (primer registro de persona)
        if (strcmp(buf.tipoBien, "*") != 0) {
            // Si el archivo no respeta el formato, omitimos hasta encontrar cabecera
            continue;
        }

        // Documento de la persona
        char doc[12];
        strcpy(doc, buf.documento);

        // Acumular bienes hasta próxima cabecera o EOF
        vector<Bien> bienesPersona;
        streampos pos = fBien.tellg();

        // Leer siguientes registros (pueden ser 0 o varios) sin pasar cabeceras de otras personas
        while (fBien.read(reinterpret_cast<char*>(&buf), sizeof(Bien))) {
            // Si es cabecera de otra persona, retroceder y terminar lectura
            if (strcmp(buf.tipoBien, "*") == 0) {
                // retroceder al inicio de este registro para que el while exterior lo lea
                fBien.seekg(pos, ios::beg);
                break;
            }
            // Si el documento coincide (normalmente sí), agregar
            if (strcmp(buf.documento, doc) == 0) {
                bienesPersona.push_back(buf);
            }
            pos = fBien.tellg();
        }

        // Calcular total de bienes de la persona
        double suma = 0.0;
        for (size_t i = 0; i < bienesPersona.size(); ++i)
            suma += bienesPersona[i].importe;

        // Actualizar DJ en memoria (buscar por documento)
        bool encontradoDJ = false;
        for (size_t i = 0; i < vDJ.size(); ++i) {
            if (strcmp(vDJ[i].documento, doc) == 0) {
                vDJ[i].totalBienes = suma;
                encontradoDJ = true;
                break;
            }
        }

        // Si la suma >= minMonto, emitimos listado
        if (suma >= minMonto) {
            // Determinar porcentaje aplicable: mayor monto <= suma
            int pct = 0;
            for (size_t k = 0; k < impuestos.size(); ++k) {
                if (suma >= impuestos[k].monto) pct = impuestos[k].porcentaje;
            }

            // Buscar nombre en DJ para imprimir encabezado
            const char* nombreImp = "(SIN NOMBRE)";
            const char* docImp = doc;
            for (size_t i = 0; i < vDJ.size(); ++i) {
                if (strcmp(vDJ[i].documento, doc) == 0) {
                    nombreImp = vDJ[i].nombre;
                    break;
                }
            }

            cout << "Apellido, Nombres : " << nombreImp << "\n";
            cout << "T-Nro.Documento    : " << docImp << "\n";
            cout << left << setw(15) << "T.Bien"
                 << left << setw(40) << "Descripcion"
                 << right << setw(12) << "Valor"
                 << right << setw(6) << "  %"
                 << right << setw(12) << "  Impuesto" << "\n";

            double totalImpuesto = 0.0;
            for (size_t i = 0; i < bienesPersona.size(); ++i) {
                double impBien = bienesPersona[i].importe;
                double impuestoBien = impBien * pct / 100.0;
                totalImpuesto += impuestoBien;

                cout << left << setw(15) << bienesPersona[i].tipoBien
                     << left << setw(40) << bienesPersona[i].descripcion
                     << right << setw(12) << impBien
                     << right << setw(6)  << pct
                     << right << setw(12) << impuestoBien << "\n";
            }

            cout << "\n";
            cout << "** Total : " << setw(10) << suma
                 << "  " << setw(3) << pct << "\n";
            cout << setw(12) << right << "Impuesto total : " << setw(12) << totalImpuesto << "\n\n";
        }

        // Si suma > maxMonto -> agregar a archivo GRANDES (lo recolectamos para escribir después)
        if (suma > maxMonto) {
            Grande g;
            // buscar nombre
            bool found = false;
            for (size_t i = 0; i < vDJ.size(); ++i) {
                if (strcmp(vDJ[i].documento, doc) == 0) {
                    strncpy(g.nombre, vDJ[i].nombre, sizeof(g.nombre));
                    g.nombre[sizeof(g.nombre)-1] = '\0';
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(g.nombre, "(SIN NOMBRE)");
            }
            strcpy(g.documento, doc);
            g.total = suma;
            grandes.push_back(g);
        }
    } // fin while BIENES

    fBien.close();

    // --- 4) Escribir archivo GRANDES.DAT con los registros recolectados ---
    if (!grandes.empty()) {
        ofstream fG("GRANDES.DAT", ios::binary);
        if (!fG) {
            cout << "No se pudo crear GRANDES.DAT" << endl;
            return 1;
        }
        for (size_t i = 0; i < grandes.size(); ++i) {
            fG.write(reinterpret_cast<char*>(&grandes[i]), sizeof(Grande));
        }
        fG.close();
        cout << "Archivo GRANDES.DAT generado con " << grandes.size() << " registros.\n";
    } else {
        cout << "No hubo Grandes Bienes (nadie supero el mayor monto).\n";
    }

    // --- 5) Reescribir DJ.DAT con los totales actualizados ---
    {
        ofstream fDJout("DJ.DAT", ios::binary | ios::trunc);
        if (!fDJout) {
            cout << "No se pudo reescribir DJ.DAT" << endl;
            return 1;
        }
        for (size_t i = 0; i < vDJ.size(); ++i) {
            fDJout.write(reinterpret_cast<char*>(&vDJ[i]), sizeof(DJ));
        }
        fDJout.close();
        cout << "DJ.DAT actualizado con importes totales de bienes.\n";
    }

    return 0;
}
