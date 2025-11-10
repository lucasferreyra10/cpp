/*
Id.Programa: G3Ej06.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Archivo de alumnos (sin orden) con: Nro.Leg (7 dígitos) y 3 notas (0..10)
    en el siguiente orden: 
      1) Algoritmos y Estructuras de Datos (AED)
      2) Física I
      3) Lógica y Estructuras Discretas (LED)
    Criterios:
      - "Firmaron"  : nota > 0  (figura en acta)
      - "Aprobaron" : nota >= 6
      - 0 significa "no consta en acta" (máximo en 2 asignaturas).
    Pedidos:
      a) Alumnos que NO firmaron ninguna (todos 0): legajos y notas.
      b) Alumnos que firmaron SOLAMENTE Física I: legajos y notas.
      c) Alumnos que aprobaron AED: legajos y nota obtenida.
      d) Cardinalidad de los que aprobaron AED.
      e) Cardinalidad de los que aprobaron SOLAMENTE cada materia 
         (AED, LED, Física I).
      f) { x | x ∈ LED − Física I } → legajos y SU nota de LED.
      g) Cardinalidad de los que aprobaron LED SOLAMENTE; además listar
         legajo y nota.
*/

#include <bits/stdc++.h>
using namespace std;

struct Alumno {
    string leg; // puede incluir ceros a la izquierda
    int aed{}, fis{}, led{};
};

bool nota_valida(int n) { return 0 <= n && n <= 10; }
bool aprueba(int n)     { return n >= 6; }
bool firmo(int n)       { return n > 0;  }

void print_header(const string& t) {
    cout << "\n=== " << t << " ===\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- Lectura del archivo ---
    string ruta;
    cout << "Ruta del archivo de alumnos (ej: alumnos.txt): ";
    if (!(cin >> ruta)) return 0;

    ifstream in(ruta);
    if (!in) {
        cerr << "No se pudo abrir el archivo: " << ruta << "\n";
        return 1;
    }

    vector<Alumno> v;
    Alumno al;
    while (in >> al.leg >> al.aed >> al.fis >> al.led) {
        if (!nota_valida(al.aed) || !nota_valida(al.fis) || !nota_valida(al.led)) {
            cerr << "Linea descartada por nota invalida (0..10): " 
                 << al.leg << "\n";
            continue;
        }
        v.push_back(al);
    }

    // --- Conjuntos de APROBADOS (para operaciones en e, f, g, d) ---
    set<string> A, F, L; // A=AED, F=FisicaI, L=LED
    for (const auto& x : v) {
        if (aprueba(x.aed)) A.insert(x.leg);
        if (aprueba(x.fis)) F.insert(x.leg);
        if (aprueba(x.led)) L.insert(x.leg);
    }

    // --- a) No firmaron ninguna (los tres = 0) ---
    print_header("a) Alumnos que NO firmaron ninguna (legajo y notas)");
    int cntNoFirmo = 0;
    for (const auto& x : v) {
        if (!firmo(x.aed) && !firmo(x.fis) && !firmo(x.led)) {
            cout << x.leg << " -> AED:" << x.aed 
                 << "  FIS:" << x.fis << "  LED:" << x.led << "\n";
            cntNoFirmo++;
        }
    }
    cout << "Total: " << cntNoFirmo << "\n";

    // --- b) Firmaron SOLAMENTE Física I (nota>0 en FIS y 0 en las otras) ---
    print_header("b) Firmaron SOLAMENTE Fisica I (legajo y notas)");
    int cntSolFirmFis = 0;
    for (const auto& x : v) {
        if ( firmo(x.fis) && !firmo(x.aed) && !firmo(x.led) ) {
            cout << x.leg << " -> AED:" << x.aed 
                 << "  FIS:" << x.fis << "  LED:" << x.led << "\n";
            cntSolFirmFis++;
        }
    }
    cout << "Total: " << cntSolFirmFis << "\n";

    // --- c) Aprobaron AED (listar legajo y nota de AED) ---
    print_header("c) Aprobaron Algoritmos y Estructuras de Datos (AED)");
    for (const auto& x : v) {
        if (aprueba(x.aed)) {
            cout << x.leg << " -> AED:" << x.aed << "\n";
        }
    }

    // --- d) Cardinalidad de los que aprobaron AED ---
    print_header("d) Cardinalidad de aprobados en AED");
    cout << "Cantidad: " << A.size() << "\n";

    // --- e) Cardinalidad de los que aprobaron SOLAMENTE cada materia ---
    //     (A solo), (L solo), (F solo) sobre aprobados
    print_header("e) Cardinalidad de APROBADOS solamente en cada materia");
    // A solo: A − (F ∪ L)
    set<string> FUL;
    set_union(F.begin(), F.end(), L.begin(), L.end(), inserter(FUL, FUL.begin()));
    set<string> A_solo, L_solo, F_solo;

    set_difference(A.begin(), A.end(), FUL.begin(), FUL.end(),
                   inserter(A_solo, A_solo.begin()));
    // L solo: L − (A ∪ F)
    set<string> AUF;
    set_union(A.begin(), A.end(), F.begin(), F.end(), inserter(AUF, AUF.begin()));
    set_difference(L.begin(), L.end(), AUF.begin(), AUF.end(),
                   inserter(L_solo, L_solo.begin()));
    // F solo: F − (A ∪ L)
    set<string> AUL;
    set_union(A.begin(), A.end(), L.begin(), L.end(), inserter(AUL, AUL.begin()));
    set_difference(F.begin(), F.end(), AUL.begin(), AUL.end(),
                   inserter(F_solo, F_solo.begin()));

    cout << "Aprobados SOLO AED: " << A_solo.size() << "\n";
    cout << "Aprobados SOLO LED: " << L_solo.size() << "\n";
    cout << "Aprobados SOLO Fisica I: " << F_solo.size() << "\n";

    // --- f) LED − Fisica I (listar legajo y SU nota de LED) ---
    print_header("f) Alumnos en (LED − Fisica I) con SU nota de LED");
    set<string> LmenosF;
    set_difference(L.begin(), L.end(), F.begin(), F.end(),
                   inserter(LmenosF, LmenosF.begin()));
    for (const auto& leg : LmenosF) {
        // buscar su nota LED para mostrarla
        auto it = find_if(v.begin(), v.end(), [&](const Alumno& s){ return s.leg == leg; });
        if (it != v.end())
            cout << it->leg << " -> LED:" << it->led << "\n";
    }
    cout << "Cantidad: " << LmenosF.size() << "\n";

    // --- g) Aprobados LED SOLAMENTE: mostrar legajo y nota + cardinalidad ---
    print_header("g) Aprobados LED SOLAMENTE (listar + cantidad)");
    for (const auto& leg : L_solo) {
        auto it = find_if(v.begin(), v.end(), [&](const Alumno& s){ return s.leg == leg; });
        if (it != v.end())
            cout << it->leg << " -> LED:" << it->led << "\n";
    }
    cout << "Cantidad: " << L_solo.size() << "\n";

    cout << "\nFin.\n";
    return 0;
}