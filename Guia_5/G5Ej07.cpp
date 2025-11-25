/*
Id.Programa: G5Ej07.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Programa que administra una COLA mediante un menú.
    Permite:
      - Encolar (agregar al final)
      - Desencolar (quitar del frente)
      - Listar elementos (desde frente a fin)
      - Ver frente (peek)
    Implementación:
      - Cola estática circular con capacidad MAX.
      - Operaciones seguras (chequeo de overflow/underflow).
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 100;

int main() {
    int cola[MAX];
    int frente = 0;      // índice del primer elemento válido
    int cantidad = 0;    // cantidad de elementos en la cola

    int opcion;
    do {
        cout << "\n------ MENU COLA (FIFO) ------\n";
        cout << "1. Encolar (agregar)\n";
        cout << "2. Desencolar (quitar)\n";
        cout << "3. Listar elementos\n";
        cout << "4. Ver frente (peek)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {

        case 1: { // Encolar
            if (cantidad == MAX) {
                cout << "La cola esta llena (overflow).\n";
            } else {
                int x;
                cout << "Ingrese valor a encolar: ";
                cin >> x;
                int pos = (frente + cantidad) % MAX;
                cola[pos] = x;
                cantidad++;
                cout << "Elemento encolado.\n";
            }
            break;
        }

        case 2: { // Desencolar
            if (cantidad == 0) {
                cout << "La cola esta vacia (underflow).\n";
            } else {
                int val = cola[frente];
                frente = (frente + 1) % MAX;
                cantidad--;
                cout << "Elemento desencolado: " << val << endl;
            }
            break;
        }

        case 3: { // Listar
            if (cantidad == 0) {
                cout << "La cola esta vacia.\n";
            } else {
                cout << "\nElementos en la cola (frente -> fin):\n";
                for (int i = 0; i < cantidad; i++) {
                    int idx = (frente + i) % MAX;
                    cout << "[" << i+1 << "] " << cola[idx] << "\n";
                }
            }
            break;
        }

        case 4: { // Peek
            if (cantidad == 0) {
                cout << "La cola esta vacia.\n";
            } else {
                cout << "Frente: " << cola[frente] << endl;
            }
            break;
        }

        case 0:
            cout << "Fin del programa.\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
