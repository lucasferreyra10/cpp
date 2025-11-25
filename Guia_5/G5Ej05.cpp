/*
Id.Programa: G5Ej05.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: octubre-2025
Comentario.:
    Programa que administra una lista mediante un menú.
    Permite:
      - Agregar elemento
      - Suprimir elemento
      - Listar elementos
    Lista implementada con vector estático y contador.
*/

#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
    int lista[MAX];
    int cant = 0;
    int opcion;

    do {
        cout << "\n------ MENU LISTA ------\n";
        cout << "1. Agregar elemento\n";
        cout << "2. Suprimir elemento\n";
        cout << "3. Listar elementos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (cant == MAX) {
                cout << "La lista esta llena.\n";
            } else {
                int x;
                cout << "Ingrese elemento a agregar: ";
                cin >> x;
                lista[cant++] = x;
                cout << "Elemento agregado.\n";
            }
            break;
        }

        case 2: {
            if (cant == 0) {
                cout << "La lista esta vacia.\n";
            } else {
                int pos;
                cout << "Ingrese posicion a suprimir (1-" << cant << "): ";
                cin >> pos;

                if (pos < 1 || pos > cant) {
                    cout << "Posicion invalida.\n";
                } else {
                    for (int i = pos - 1; i < cant - 1; i++)
                        lista[i] = lista[i + 1];
                    cant--;
                    cout << "Elemento suprimido.\n";
                }
            }
            break;
        }

        case 3: {
            if (cant == 0) {
                cout << "La lista esta vacia.\n";
            } else {
                cout << "\nLista de elementos:\n";
                for (int i = 0; i < cant; i++)
                    cout << "[" << i + 1 << "] " << lista[i] << endl;
            }
            break;
        }

        case 0:
            cout << "Fin del programa.\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}
