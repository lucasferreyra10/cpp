/*
Id.Programa: G1Ej14.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: De cada participante del Rally Paris-Dakar se conocen:
             codigo (0: fin, 1: auto, 2: camion, 3: moto),
             numero del vehiculo, piloto, copiloto, escuderia y tiempo.
             Informar el ganador (menor tiempo) por cada tipo de vehiculo.
*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    int codigo;
    int numero;
    string piloto, copiloto, escuderia;
    double tiempo;

    // Variables para guardar ganadores
    double min_auto = numeric_limits<double>::max();
    double min_camion = numeric_limits<double>::max();
    double min_moto = numeric_limits<double>::max();

    string ganador_auto, ganador_camion, ganador_moto;
    int num_auto = -1, num_camion = -1, num_moto = -1;
    string esc_auto, esc_camion, esc_moto;

    cout << "Registro de participantes del Rally Paris-Dakar" << endl;
    cout << "(codigo: 1=auto, 2=camion, 3=moto, 0=fin)" << endl;

    // Entrada repetitiva hasta codigo 0
    while (true) {
        cout << "\nIngrese codigo del vehiculo: ";
        cin >> codigo;
        if (codigo == 0) break;

        if (codigo < 1 || codigo > 3) {
            cout << "Codigo invalido. Debe ser 1, 2 o 3." << endl;
            continue;
        }

        cout << "Numero del vehiculo: ";
        cin >> numero;
        cin.ignore(); // limpiar salto de linea

        cout << "Apellido y nombre del piloto: ";
        getline(cin, piloto);

        cout << "Apellido y nombre del copiloto: ";
        getline(cin, copiloto);

        cout << "Nombre de la escuderia: ";
        getline(cin, escuderia);

        cout << "Tiempo utilizado (en horas): ";
        cin >> tiempo;

        // Determinar ganadores por categoria
        switch (codigo) {
            case 1: // auto
                if (tiempo < min_auto) {
                    min_auto = tiempo;
                    ganador_auto = piloto + " / " + copiloto;
                    num_auto = numero;
                    esc_auto = escuderia;
                }
                break;
            case 2: // camion
                if (tiempo < min_camion) {
                    min_camion = tiempo;
                    ganador_camion = piloto + " / " + copiloto;
                    num_camion = numero;
                    esc_camion = escuderia;
                }
                break;
            case 3: // moto
                if (tiempo < min_moto) {
                    min_moto = tiempo;
                    ganador_moto = piloto;
                    num_moto = numero;
                    esc_moto = escuderia;
                }
                break;
        }
    }

    cout << "\n---- GANADORES POR CATEGORIA ----" << endl;

    if (min_auto < numeric_limits<double>::max()) {
        cout << "\nAuto ganador:" << endl;
        cout << "Vehiculo Nro: " << num_auto << endl;
        cout << "Piloto/Copiloto: " << ganador_auto << endl;
        cout << "Escuderia: " << esc_auto << endl;
        cout << "Tiempo: " << min_auto << " hs" << endl;
    } else cout << "\nNo hubo participantes en categoria Auto." << endl;

    if (min_camion < numeric_limits<double>::max()) {
        cout << "\nCamion ganador:" << endl;
        cout << "Vehiculo Nro: " << num_camion << endl;
        cout << "Piloto/Copiloto: " << ganador_camion << endl;
        cout << "Escuderia: " << esc_camion << endl;
        cout << "Tiempo: " << min_camion << " hs" << endl;
    } else cout << "\nNo hubo participantes en categoria Camion." << endl;

    if (min_moto < numeric_limits<double>::max()) {
        cout << "\nMoto ganadora:" << endl;
        cout << "Vehiculo Nro: " << num_moto << endl;
        cout << "Piloto: " << ganador_moto << endl;
        cout << "Escuderia: " << esc_moto << endl;
        cout << "Tiempo: " << min_moto << " hs" << endl;
    } else cout << "\nNo hubo participantes en categoria Moto." << endl;

    return 0;
}