/*
Id.Programa: G3Ej02.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Pub con tres sabores: Naranja (N), Frutilla (F) y Ananá (A).
    Cada persona tiene un número de consumisión (1..250). Se ingresa
    para cada persona qué sabores pidió: uno, dos, los tres o ninguno.
    Se contabiliza en las áreas del diagrama de Venn:

        A1: solo N
        A2: solo A
        A3: solo F
        A4: N ∩ A (sin F)
        A5: N ∩ F (sin A)
        A6: F ∩ A (sin N)
        A7: N ∩ F ∩ A
        A8: sin consumo

    Al finalizar (nro=0) se muestran cantidades, porcentajes y
    promedios (promedio del número de consumisión) por área, y el total
    de personas que ingresaron al pub.
*/

#include <bits/stdc++.h>
using namespace std;

struct AreaStats {
    long long cnt = 0;     // cantidad de personas
    long long sum = 0;     // suma de números de consumisión (para promedio)
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int LIMITE_MAX = 250;
    AreaStats A[9]; // A[1]..A[8]

    cout << "=== Pub: Naranja (N), Frutilla (F), Anana (A) ===\n";
    cout << "Ingrese personas por 'numero de consumision' (1.." << LIMITE_MAX
         << ").\nUse 0 para finalizar.\n\n";

    while (true) {
        int nro;
        cout << "Numero de consumision (0 para terminar): ";
        if (!(cin >> nro)) return 0;          // fin de entrada
        if (nro == 0) break;
        if (nro < 1 || nro > LIMITE_MAX) {
            cout << "  Valor invalido. Debe ser 1.." << LIMITE_MAX << ".\n";
            continue;
        }

        cout << "Seleccione opcion de sabores:\n";
        cout << "  1) Solo Naranja (N)\n";
        cout << "  2) Solo Frutilla (F)\n";
        cout << "  3) Solo Anana (A)\n";
        cout << "  4) Naranja + Frutilla (NF)\n";
        cout << "  5) Naranja + Anana (NA)\n";
        cout << "  6) Frutilla + Anana (FA)\n";
        cout << "  7) Naranja + Frutilla + Anana (NFA)\n";
        cout << "  8) Sin consumo\n";
        cout << "Opcion: ";

        int op; cin >> op;
        if (op < 1 || op > 8) {
            cout << "  Opcion invalida.\n";
            continue;
        }

        // Mapear opcion -> área A1..A8
        int area = 0;
        switch (op) {
            case 1: area = 1; break; // solo N
            case 2: area = 3; break; // solo F
            case 3: area = 2; break; // solo A
            case 4: area = 5; break; // N∩F
            case 5: area = 4; break; // N∩A
            case 6: area = 6; break; // F∩A
            case 7: area = 7; break; // N∩F∩A
            case 8: area = 8; break; // sin consumo
        }

        A[area].cnt++;
        A[area].sum += nro;
        cout << "  Registrado en A" << area << ".\n\n";
    }

    // Totales
    long long total = 0;
    for (int i = 1; i <= 8; ++i) total += A[i].cnt;

    cout << "\n================= RESULTADOS =================\n";
    cout << fixed << setprecision(2);

    auto nombre = [&](int i)->string{
        switch(i){
            case 1: return "A1 (solo Naranja)           ";
            case 2: return "A2 (solo Anana)             ";
            case 3: return "A3 (solo Frutilla)          ";
            case 4: return "A4 (Naranja ∩ Anana)        ";
            case 5: return "A5 (Naranja ∩ Frutilla)     ";
            case 6: return "A6 (Frutilla ∩ Anana)       ";
            case 7: return "A7 (Naranja ∩ Frutilla ∩ Anana)";
            case 8: return "A8 (sin consumo)            ";
        }
        return "";
    };

    cout << "Area                               Cant   % sobre total   Promedio nro\n";
    cout << "------------------------------------------------------------------------\n";
    for (int i = 1; i <= 8; ++i) {
        double pct = (total ? (100.0 * A[i].cnt / total) : 0.0);
        double prom = (A[i].cnt ? (double)A[i].sum / A[i].cnt : 0.0);
        cout << nombre(i) << "  "
             << setw(4) << A[i].cnt << "      "
             << setw(6) << pct << "%        "
             << setw(8) << prom << "\n";
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "TOTAL PERSONAS INGRESADAS: " << total << "\n";
    cout << "(Límite máximo permitido: " << LIMITE_MAX << ")\n";
    return 0;
}