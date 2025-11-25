#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> pila;   // Estructura de pila
    int opcion, valor;

    do {
        cout << "\n----- MENU PILA -----\n";
        cout << "1. Agregar elemento (push)\n";
        cout << "2. Suprimir elemento (pop)\n";
        cout << "3. Listar elementos\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese valor a apilar: ";
            cin >> valor;
            pila.push_back(valor);
            cout << "Elemento agregado.\n";
            break;

        case 2:
            if (!pila.empty()) {
                cout << "Elemento eliminado: " << pila.back() << endl;
                pila.pop_back();
            } else {
                cout << "La pila esta vacia.\n";
            }
            break;

        case 3:
            if (pila.empty()) {
                cout << "La pila esta vacia.\n";
            } else {
                cout << "Elementos en la pila (tope a base):\n";
                for (int i = pila.size() - 1; i >= 0; i--) {
                    cout << pila[i] << endl;
                }
            }
            break;

        case 0:
            cout << "Fin del programa.\n";
            break;

        default:
            cout << "Opción incorrecta.\n";
        }

    } while (opcion != 0);

    return 0;
}
