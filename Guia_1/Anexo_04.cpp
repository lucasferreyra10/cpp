/*
Id.Programa: Anexo_04.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: abril-2025
Comentario.: 
   Parte A) Dibuja la grafica ASCII de y = sen(x) en el intervalo [0, 2*pi].
   Parte B) Clasifica un triangulo segun sus angulos (rectangulo, acutangulo u obtusangulo)
            aplicando las relaciones: 
            A = b^2 + c^2 - a^2
            B = a^2 + c^2 - b^2
            C = a^2 + b^2 - c^2
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

/* -------------------- PARTE A: GRAFICA DE y = sen(x) -------------------- */
void GraficarSeno() {
    const int cols = 80;
    const int rows = 21;
    const double xmin = 0.0;
    const double xmax = 2.0 * M_PI;
    const double ymin = -1.0;
    const double ymax =  1.0;

    vector<string> grid(rows, string(cols, ' '));

    // Eje X (y = 0)
    int xAxisRow = (int)round((0.0 - ymin) * (rows - 1) / (ymax - ymin));
    if (xAxisRow >= 0 && xAxisRow < rows)
        for (int j = 0; j < cols; ++j) grid[xAxisRow][j] = '-';

    // Eje Y (x = 0)
    int yAxisCol = (int)round((0.0 - xmin) * (cols - 1) / (xmax - xmin));
    if (yAxisCol >= 0 && yAxisCol < cols)
        for (int i = 0; i < rows; ++i) grid[i][yAxisCol] = '|';

    // Trazar sen(x)
    for (int j = 0; j < cols; ++j) {
        double x = xmin + (xmax - xmin) * j / (cols - 1);
        double y = sin(x);
        int i = (int)round((y - ymin) * (rows - 1) / (ymax - ymin));
        int row = rows - 1 - i;
        if (row >= 0 && row < rows && j >= 0 && j < cols)
            grid[row][j] = '*';
    }

    // Marcar origen
    if (xAxisRow >= 0 && xAxisRow < rows && yAxisCol >= 0 && yAxisCol < cols)
        grid[xAxisRow][yAxisCol] = '+';

    cout << "\nGrafica ASCII de y = sen(x) en [0, 2*pi]\n\n";
    for (const auto &line : grid) cout << line << "\n";
    cout << "\nLeyenda: * = sen(x), eje X = -, eje Y = |\n\n";
}

/* -------------------- PARTE B: CLASIFICACION DE TRIANGULOS -------------------- */
void ClasificarTriangulo() {
    double a, b, c;
    const double EPS = 1e-9;

    cout << "Clasificacion de triangulos segun sus angulos\n";
    cout << "Ingrese a: "; cin >> a;
    cout << "Ingrese b: "; cin >> b;
    cout << "Ingrese c: "; cin >> c;

    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "No es triangulo: lados no positivos.\n";
        return;
    }
    if (!(a < b + c && b < a + c && c < a + b)) {
        cout << "No es triangulo: no cumple desigualdades triangulares.\n";
        return;
    }

    double A = b*b + c*c - a*a;
    double B = a*a + c*c - b*b;
    double C = a*a + b*b - c*c;

    bool esRect = (fabs(A) <= EPS) || (fabs(B) <= EPS) || (fabs(C) <= EPS);
    bool todosPos = (A > EPS) && (B > EPS) && (C > EPS);
    bool algunoNeg = (A < -EPS) || (B < -EPS) || (C < -EPS);

    cout << fixed << setprecision(6);
    cout << "\nValores: A=" << A << ", B=" << B << ", C=" << C << endl;

    if (esRect)
        cout << "El triangulo es RECTANGULO.\n";
    else if (todosPos)
        cout << "El triangulo es ACUTANGULO.\n";
    else if (algunoNeg)
        cout << "El triangulo es OBTUSANGULO.\n";
    else
        cout << "Clasificacion no concluyente por redondeo numerico.\n";
}

/* -------------------- PROGRAMA PRINCIPAL -------------------- */
int main() {
    cout << "ANEXO 04 - Grafica de sen(x) y clasificacion de triangulos\n";
    cout << "-----------------------------------------------------------\n";

    GraficarSeno();
    ClasificarTriangulo();

    return 0;
}