/*
Id.Programa: G3Ej01.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Encuesta de 100 personas, 3 preguntas (Q1,Q2,Q3) correctas (si/no).
             Resuelve:
               1) Asignacion externa por CONTEOS (solo cantidades).
               2) Asignacion interna (valores del enunciado).
               3) Asignacion externa por CONJUNTOS (IDs de personas).
               4) Carga cruda de RESPUESTAS (Y/N) por persona 1..100.
             Emite todas las cardinalidades pedidas (a..n) y, si aplica, las listas de IDs.
*/

#include <bits/stdc++.h>
using namespace std;

struct Resultados {
    int A, B, C;
    int onlyA, onlyB, onlyC;
    int AB_only, AC_only, BC_only;
    int ABC;
    int ninguno;
    int dos;
    int no_tres;
    int una;
};

// ======================= util de conteos (inciso 1 y 2) =======================
Resultados resolverPorConteos(
    int total,
    int A, int B, int C,
    int AB_only, int AC_only, int BC_only,
    int ABC
){
    Resultados r{};
    r.A = A; r.B = B; r.C = C;
    r.AB_only = AB_only; r.AC_only = AC_only; r.BC_only = BC_only;
    r.ABC = ABC;

    r.onlyA = max(0, A - AB_only - AC_only - ABC);
    r.onlyB = max(0, B - AB_only - BC_only - ABC);
    r.onlyC = max(0, C - AC_only - BC_only - ABC);

    r.dos = AB_only + AC_only + BC_only;
    r.una = r.onlyA + r.onlyB + r.onlyC;

    int unionABC = r.una + r.dos + r.ABC;
    r.ninguno = max(0, total - unionABC);
    r.no_tres = total - r.ABC;

    return r;
}

void imprimirCardinalidades(const Resultados& r) {
    cout << "\n=== Resultados (cardinalidades) ===\n";
    cout << "a) |A| (Q1 al menos): " << r.A << "\n";
    cout << "b) |B| (Q2 al menos): " << r.B << "\n";
    cout << "c) |C| (Q3 al menos): " << r.C << "\n";
    cout << "d) Ninguna pregunta: " << r.ninguno << "\n";
    cout << "e) Exactamente dos preguntas: " << r.dos << "\n";
    cout << "f) No contestaron las tres: " << r.no_tres << "\n";
    cout << "g) Exactamente una pregunta: " << r.una << "\n";
    cout << "h) Las tres preguntas: " << r.ABC << "\n";
    cout << "i) Solo Q1: " << r.onlyA << "\n";
    cout << "j) Solo Q2: " << r.onlyB << "\n";
    cout << "k) Solo Q3: " << r.onlyC << "\n";
    cout << "l) Solo Q1 y Q2: " << r.AB_only << "\n";
    cout << "m) Solo Q1 y Q3: " << r.AC_only << "\n";
    cout << "n) Solo Q2 y Q3: " << r.BC_only << "\n";
}

// ======================= util de conjuntos (inciso 3 y 4) =======================
template<class T>
set<T> inter(const set<T>& a, const set<T>& b) {
    set<T> r;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}
template<class T>
set<T> unio(const set<T>& a, const set<T>& b) {
    set<T> r;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}
template<class T>
set<T> diff(const set<T>& a, const set<T>& b) {
    set<T> r;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}

void imprimirSet(const set<int>& s, const string& nombre) {
    cout << left << setw(16) << (nombre + ":") << " { ";
    bool first = true;
    for (int x : s) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
    }
    cout << " } (|" << s.size() << ")\n";
}

void resolverYListar(const set<int>& Aset, const set<int>& Bset, const set<int>& Cset, int total=100) {
    set<int> ABC   = inter(inter(Aset,Bset), Cset);
    set<int> AB    = inter(Aset, Bset);
    set<int> AC    = inter(Aset, Cset);
    set<int> BC    = inter(Bset, Cset);
    set<int> onlyA = diff(Aset, unio(Bset, Cset));
    set<int> onlyB = diff(Bset, unio(Aset, Cset));
    set<int> onlyC = diff(Cset, unio(Aset, Bset));
    set<int> AB_only = diff(AB, Cset);
    set<int> AC_only = diff(AC, Bset);
    set<int> BC_only = diff(BC, Aset);
    set<int> uni = unio(unio(Aset,Bset), Cset);

    imprimirSet(Aset, "A (Q1)");
    imprimirSet(Bset, "B (Q2)");
    imprimirSet(Cset, "C (Q3)");
    imprimirSet(onlyA, "Solo Q1");
    imprimirSet(onlyB, "Solo Q2");
    imprimirSet(onlyC, "Solo Q3");
    imprimirSet(AB_only, "Solo Q1&Q2");
    imprimirSet(AC_only, "Solo Q1&Q3");
    imprimirSet(BC_only, "Solo Q2&Q3");
    imprimirSet(ABC, "Q1&Q2&Q3");
    set<int> ninguno;
    for (int i=1;i<=100;i++) if (!uni.count(i)) ninguno.insert(i);
    imprimirSet(ninguno, "Ninguna");

    Resultados r{};
    r.A = (int)Aset.size();
    r.B = (int)Bset.size();
    r.C = (int)Cset.size();
    r.onlyA = (int)onlyA.size();
    r.onlyB = (int)onlyB.size();
    r.onlyC = (int)onlyC.size();
    r.AB_only = (int)AB_only.size();
    r.AC_only = (int)AC_only.size();
    r.BC_only = (int)BC_only.size();
    r.ABC = (int)ABC.size();
    r.dos = r.AB_only + r.AC_only + r.BC_only;
    r.una = r.onlyA + r.onlyB + r.onlyC;
    r.ninguno = total - (int)uni.size();
    r.no_tres = total - r.ABC;
    imprimirCardinalidades(r);
}

// ============================== modos ==============================
void modo1_conteos() {
    cout << "\n[Modo 1] Asignacion EXTERNA por CONTEOS\n";
    int total = 100;
    int A,B,C, AB_only, AC_only, BC_only, ABC;
    cout << "Ingrese |A| (Q1 al menos): "; cin >> A;
    cout << "Ingrese |B| (Q2 al menos): "; cin >> B;
    cout << "Ingrese |C| (Q3 al menos): "; cin >> C;
    cout << "Ingrese solo Q1&Q2: "; cin >> AB_only;
    cout << "Ingrese solo Q1&Q3: "; cin >> AC_only;
    cout << "Ingrese solo Q2&Q3: "; cin >> BC_only;
    cout << "Ingrese Q1&Q2&Q3: "; cin >> ABC;

    Resultados r = resolverPorConteos(total, A,B,C, AB_only,AC_only,BC_only, ABC);
    imprimirCardinalidades(r);
}

void modo2_interno() {
    cout << "\n[Modo 2] Asignacion INTERNA (datos del enunciado)\n";
    const int total = 100;
    int ABC = 8, AB_only = 9, AC_only = 11, BC_only = 6;
    int A = 55, B = 32, C = 49;

    Resultados r = resolverPorConteos(total, A,B,C, AB_only,AC_only,BC_only, ABC);
    imprimirCardinalidades(r);
}

void leerConjunto(set<int>& S, const string& nombre) {
    cout << "Ingrese IDs para " << nombre << " (1..100). Termine con 0:\n";
    while (true) {
        int x; cin >> x;
        if (x==0) break;
        if (1<=x && x<=100) S.insert(x);
        else cout << "  fuera de rango, ignore\n";
    }
}
void modo3_sets() {
    cout << "\n[Modo 3] Asignacion por CONJUNTOS (IDs)\n";
    set<int> A, B, C;
    leerConjunto(A, "A (Q1)");
    leerConjunto(B, "B (Q2)");
    leerConjunto(C, "C (Q3)");
    resolverYListar(A,B,C,100);
}

void modo4_respuestas() {
    cout << "\n[Modo 4] Carga de RESPUESTAS crudas (Y/N) por persona 1..100\n";
    set<int> A,B,C;
    for (int id=1; id<=100; ++id) {
        char r1,r2,r3;
        cout << "Persona " << id << " - Q1 (Y/N), Q2 (Y/N), Q3 (Y/N): ";
        cin >> r1 >> r2 >> r3;
        if (r1=='Y'||r1=='y') A.insert(id);
        if (r2=='Y'||r2=='y') B.insert(id);
        if (r3=='Y'||r3=='y') C.insert(id);
    }
    resolverYListar(A,B,C,100);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "\n================ MENU G3Ej01 (Conjuntos) ================\n";
        cout << "1) Asignacion externa por CONTEOS (ingresar cantidades)\n";
        cout << "2) Asignacion interna (usar datos del enunciado)\n";
        cout << "3) Asignacion por CONJUNTOS (cargar IDs de A,B,C)\n";
        cout << "4) Carga cruda de RESPUESTAS (100 personas, Y/N)\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        int op; if (!(cin >> op)) break;
        if (op==0) break;
        if (op==1) modo1_conteos();
        else if (op==2) modo2_interno();
        else if (op==3) modo3_sets();
        else if (op==4) modo4_respuestas();
        else cout << "Opcion invalida.\n";
    }
    return 0;
}