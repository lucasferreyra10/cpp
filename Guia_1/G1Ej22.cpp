/*
Id.Programa: G1Ej22.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: En un curso se toman examenes sobre perimetro y tipo de triangulo.
             Se generan al azar las medidas de los lados. Por cada alumno se
             informa su nombre y si respondio bien o mal (acierto total en ambas
             preguntas). Al final se muestran las cantidades de respuestas
             correctas e incorrectas. Valor centinela: "FIN".
*/

#include <iostream>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <cmath>
#include <string>
using namespace std;

// Determina si los lados forman un triangulo valido
bool EsTriangulo(int a, int b, int c) {
    return (a < b + c) && (b < a + c) && (c < a + b);
}

// Determina el tipo de triangulo segun sus lados
string TipoTriangulo(int a, int b, int c) {
    if (a == b && b == c)
        return "Equilatero";
    else if (a == b || a == c || b == c)
        return "Isosceles";
    else
        return "Escaleno";
}

// Calcula el perimetro de un triangulo
int Perimetro(int a, int b, int c) {
    return a + b + c;
}

int main() {
    srand(time(nullptr));

    string nombre;
    int correctas = 0, incorrectas = 0;

    cout << "Sistema de examenes de triangulos (ingrese 'FIN' para terminar)" << endl;

    while (true) {
        cout << "\nIngrese el nombre del alumno: ";
        getline(cin, nombre);

        // Valor centinela
        if (nombre == "FIN" || nombre == "fin")
            break;

        // Generar lados aleatorios
        int a = rand() % 20 + 1;
        int b = rand() % 20 + 1;
        int c = rand() % 20 + 1;

        cout << "Lados generados: a=" << a << "  b=" << b << "  c=" << c << endl;

        // Validar que formen un triangulo
        if (!EsTriangulo(a, b, c)) {
            cout << "Los lados NO forman un triangulo valido. Respuesta incorrecta." << endl;
            incorrectas++;
            continue;
        }

        // Calculos reales
        int perimetro_correcto = Perimetro(a, b, c);
        string tipo_correcto = TipoTriangulo(a, b, c);

        // Simulacion de respuestas del alumno
        int perimetro_respuesta;
        string tipo_respuesta;

        cout << "Ingrese el perimetro calculado por el alumno: ";
        cin >> perimetro_respuesta;
        cin.ignore(); // limpiar buffer

        cout << "Ingrese el tipo de triangulo segun el alumno (Equilatero / Isosceles / Escaleno): ";
        getline(cin, tipo_respuesta);

        // Comparar respuestas
        bool perimetro_ok = (perimetro_respuesta == perimetro_correcto);
        bool tipo_ok = (tipo_respuesta == tipo_correcto);

        if (perimetro_ok && tipo_ok) {
            cout << "El alumno " << nombre << " respondio BIEN." << endl;
            correctas++;
        } else {
            cout << "El alumno " << nombre << " respondio MAL." << endl;
            cout << "Perimetro correcto: " << perimetro_correcto
                 << " | Tipo correcto: " << tipo_correcto << endl;
            incorrectas++;
        }
    }

    cout << "\n---- RESUMEN FINAL ----" << endl;
    cout << "Cantidad de respuestas correctas: " << correctas << endl;
    cout << "Cantidad de respuestas incorrectas: " << incorrectas << endl;

    return 0;
}