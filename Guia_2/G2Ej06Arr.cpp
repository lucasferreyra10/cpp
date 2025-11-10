/*
Id.Programa: G2Ej06Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Inscripcion de ingresantes con asignacion por orden de llegada.
             - Divisiones 1..N (N <= 50) con vacantes.
             - Hasta 3000 solicitudes (legajo, apellido y nombre, division elegida).
             - 1ra pasada: asignar a la division elegida mientras haya vacantes.
             - 2da pasada: reubicar no asignados en cualquier division con vacantes.
             - Emitir vacantes sobrantes y/o legajos sin asignacion.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_ALUMNOS = 3000;
const int MAX_DIV = 50;

int main() {
    int N;                          // cantidad de divisiones (1..50)
    int vac[MAX_DIV + 1] = {0};     // vacantes por division (1..N)
    int M;                          // cantidad de solicitudes (<= 3000)

    // Datos de alumnos (arreglos paralelos)
    string legajo[MAX_ALUMNOS];
    string nombre[MAX_ALUMNOS];
    int    prefDiv[MAX_ALUMNOS];    // division elegida
    int    asignado[MAX_ALUMNOS];   // division asignada (-1 sin asignar)

    cout << "Asignacion de divisiones para ingresantes (arreglos)\n";

    // Leer N y vacantes
    do {
        cout << "Ingrese N (cantidad de divisiones, 1..50): ";
        cin >> N;
        if (N < 1 || N > MAX_DIV) cout << "Valor invalido.\n";
    } while (N < 1 || N > MAX_DIV);

    cout << "Ingrese vacantes por division (1..N):\n";
    for (int d = 1; d <= N; ++d) {
        cout << "  Vacantes division " << d << ": ";
        cin >> vac[d];
        if (vac[d] < 0) vac[d] = 0;
    }

    // Leer cantidad de solicitudes
    do {
        cout << "Ingrese cantidad de solicitudes (0.." << MAX_ALUMNOS << "): ";
        cin >> M;
        if (M < 0 || M > MAX_ALUMNOS) cout << "Valor invalido.\n";
    } while (M < 0 || M > MAX_ALUMNOS);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Leer solicitudes (en orden de llegada)
    for (int i = 0; i < M; ++i) {
        cout << "\nSolicitud #" << (i + 1) << "\n";
        cout << "  Legajo (5 car): ";
        getline(cin, legajo[i]);
        cout << "  Apellido y Nombre (30 car): ";
        getline(cin, nombre[i]);
        cout << "  Division elegida (1.." << N << "): ";
        cin >> prefDiv[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (prefDiv[i] < 1 || prefDiv[i] > N) {
            cout << "  Advertencia: division elegida fuera de rango.\n";
        }
        asignado[i] = -1;
    }

    // Primera pasada: asignar a la preferencia
    for (int i = 0; i < M; ++i) {
        int d = prefDiv[i];
        if (d >= 1 && d <= N && vac[d] > 0) {
            asignado[i] = d;
            vac[d]--;
        }
    }

    // Segunda pasada: reubicar los no asignados
    for (int i = 0; i < M; ++i) {
        if (asignado[i] == -1) {
            for (int d = 1; d <= N; ++d) {
                if (vac[d] > 0) {
                    asignado[i] = d;
                    vac[d]--;
                    break;
                }
            }
        }
    }

    // Mostrar resultados
    cout << "\n===== RESULTADOS =====\n\n";
    cout << left << setw(8) << "Legajo" << " | "
         << left << setw(30) << "Apellido y Nombre" << " | "
         << "Pref" << " -> " << "Asig\n";
    cout << string(8 + 3 + 30 + 5 + 4, '-') << "\n";

    int sinAsignacion = 0;
    for (int i = 0; i < M; ++i) {
        cout << left << setw(8) << legajo[i] << " | "
             << left << setw(30) << nombre[i] << " | "
             << setw(4) << prefDiv[i] << " -> ";
        if (asignado[i] == -1) {
            cout << "SIN";
            sinAsignacion++;
        } else {
            cout << setw(3) << asignado[i];
        }
        cout << "\n";
    }

    bool hayVacantes = false;
    for (int d = 1; d <= N; ++d) if (vac[d] > 0) hayVacantes = true;

    if (hayVacantes) {
        cout << "\nVacantes sobrantes por division:\n";
        for (int d = 1; d <= N; ++d)
            cout << "  Division " << d << ": " << vac[d] << " vacantes\n";
    }

    if (sinAsignacion > 0) {
        cout << "\nAlumnos sin asignacion (legajos):\n";
        for (int i = 0; i < M; ++i)
            if (asignado[i] == -1)
                cout << "  - " << legajo[i] << "\n";
    }

    if (!hayVacantes && sinAsignacion == 0)
        cout << "\nSin vacantes sobrantes ni alumnos sin asignacion.\n";

    return 0;
}
