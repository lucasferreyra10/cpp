/*
Id.Programa: G5Ej22.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    - Detecta e imprime errores en NOTAS.DAT:
        * parcial desaprobado (nota1 < 6 o nota2 < 6),
        * sin fecha de firma (fechaFirma == 0),
        * sin regularidad (no figura en ASISTENCIAS.DAT para esa materia).
    - Genera TRABPRAC_APROB.DAT combinando TRABPRAC.DAT y los registros correctos de NOTAS.DAT,
      ordenado por legajo asc y codMateria asc.
    - Evita duplicados si ya existe registro en TRABPRAC.DAT.
    Notas:
      - Umbral de aprobación parcial: 6 (>=6 aprobado).
      - Archivos binarios esperados: ASISTENCIAS.DAT, NOTAS.DAT, TRABPRAC.DAT
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

struct Asistencia {
    char legajo[7];
    char codMateria[5];
};

struct Nota {
    short nroCurso;
    char codMateria[5];
    char legajo[7];
    int nota1;
    int nota2;
    int fechaFirma;
};

struct TrabPrac {
    char legajo[7];
    char codMateria[5];
    int fechaFirma;
    short nroCurso;
};

bool keyEqual(const TrabPrac &a, const TrabPrac &b) {
    return (string(a.legajo) == string(b.legajo) && string(a.codMateria) == string(b.codMateria));
}

bool compareTrabPrac(const TrabPrac &a, const TrabPrac &b) {
    int cmp = strcmp(a.legajo, b.legajo);
    if (cmp != 0) return cmp < 0;
    return strcmp(a.codMateria, b.codMateria) < 0;
}

int main() {
    cout << fixed;

    // 1) Cargar ASISTENCIAS en set<string> de clave legajo+materia
    set<string> asistSet;
    {
        ifstream f("ASISTENCIAS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir ASISTENCIAS.DAT\n"; return 1; }
        Asistencia a;
        while (f.read(reinterpret_cast<char*>(&a), sizeof(a))) {
            string key = string(a.legajo) + "|" + string(a.codMateria);
            asistSet.insert(key);
        }
        f.close();
        cout << "ASISTENCIAS cargadas: " << asistSet.size() << "\n";
    }

    // 2) Cargar TRABPRAC.DAT existente
    vector<TrabPrac> trabExist;
    {
        ifstream f("TRABPRAC.DAT", ios::binary);
        if (f) {
            TrabPrac t;
            while (f.read(reinterpret_cast<char*>(&t), sizeof(t))) trabExist.push_back(t);
            f.close();
        }
        cout << "TRABPRAC existentes: " << trabExist.size() << "\n";
    }

    // crear conjunto de claves existentes para evitar duplicados
    set<string> trabKeys;
    for (auto &t : trabExist) {
        string k = string(t.legajo) + "|" + string(t.codMateria);
        trabKeys.insert(k);
    }

    // 3) Procesar NOTAS.DAT: detectar errores y recolectar correctos
    vector<TrabPrac> nuevosAprob; // registros para agregar
    {
        ifstream f("NOTAS.DAT", ios::binary);
        if (!f) { cerr << "No se pudo abrir NOTAS.DAT\n"; return 1; }
        Nota n;
        cout << "\nErrores detectados en NOTAS.DAT:\n";
        cout << "Tipo\tLegajo\tMateria\tCurso\tNota1\tNota2\tFechaFirma\n";

        while (f.read(reinterpret_cast<char*>(&n), sizeof(n))) {
            string leg = string(n.legajo);
            string mat = string(n.codMateria);
            string keyAsist = leg + "|" + mat;

            bool desaprobo = (n.nota1 < 6 || n.nota2 < 6);
            bool sinFecha = (n.fechaFirma == 0);
            bool sinReg = (asistSet.find(keyAsist) == asistSet.end());

            if (desaprobo) {
                cout << "DESAPROBADO\t" << leg << "\t" << mat << "\t" << n.nroCurso
                     << "\t" << n.nota1 << "\t" << n.nota2 << "\t" << n.fechaFirma << "\n";
                continue;
            }
            if (sinFecha) {
                cout << "SIN_FECHA\t" << leg << "\t" << mat << "\t" << n.nroCurso
                     << "\t" << n.nota1 << "\t" << n.nota2 << "\t" << n.fechaFirma << "\n";
                continue;
            }
            if (sinReg) {
                cout << "SIN_REGULARIDAD\t" << leg << "\t" << mat << "\t" << n.nroCurso
                     << "\t" << n.nota1 << "\t" << n.nota2 << "\t" << n.fechaFirma << "\n";
                continue;
            }

            // si llega acá: registro correcto -> preparar TRABPRAC
            string k = leg + "|" + mat;
            if (trabKeys.find(k) == trabKeys.end()) {
                TrabPrac t;
                strncpy(t.legajo, n.legajo, sizeof(t.legajo)); t.legajo[6] = '\0';
                strncpy(t.codMateria, n.codMateria, sizeof(t.codMateria)); t.codMateria[4] = '\0';
                t.fechaFirma = n.fechaFirma;
                t.nroCurso = n.nroCurso;
                nuevosAprob.push_back(t);
                trabKeys.insert(k); // marcar para no insertar duplicado más adelante
            } else {
                // ya aprobado previamente; podemos ignorar o mostrar info
                cout << "YA_APROBADO\t" << leg << "\t" << mat << "\n";
            }
        }
        f.close();
    }

    cout << "\nRegistros correctos a agregar: " << nuevosAprob.size() << "\n";

    // 4) Merge: trabExist + nuevosAprob -> resultado ordenado por legajo + codMateria
    vector<TrabPrac> resultado = trabExist;
    resultado.insert(resultado.end(), nuevosAprob.begin(), nuevosAprob.end());

    sort(resultado.begin(), resultado.end(), compareTrabPrac);

    // 5) Grabar TRABPRAC_APROB.DAT
    {
        ofstream fout("TRABPRAC_APROB.DAT", ios::binary | ios::trunc);
        if (!fout) { cerr << "No se pudo crear TRABPRAC_APROB.DAT\n"; return 1; }
        for (auto &t : resultado) fout.write(reinterpret_cast<char*>(&t), sizeof(t));
        fout.close();
        cout << "TRABPRAC_APROB.DAT generado con " << resultado.size() << " registros.\n";
    }

    // 6) Imprimir resumen (breve) de aprobaciones
    cout << "\nListado de Trabajos Prácticos Aprobados (legajo - materia - fecha - curso):\n";
    for (auto &t : resultado) {
        cout << t.legajo << "  " << t.codMateria << "  " << t.fechaFirma << "  " << t.nroCurso << "\n";
    }

    cout << "\nProceso finalizado.\n";
    return 0;
}
