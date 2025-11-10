/*
Id.Programa: G3Ej09.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Dado un conjunto (sin repetidos) de n valores enteros, calcular
    por menú: promedio, máximo, mínimo y sumatoria.
*/

#include <iostream>
#include <set>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cout << "Cantidad de elementos del conjunto N0: ";
    cin >> n;
    set<long long> S;
    cout << "Ingrese " << n << " enteros: \n";
    for(int i=0;i<n;++i){
        long long x; cin >> x;
        S.insert(x); // set evita duplicados
    }

    char op;
    do{
        cout << "\n--- MENU ---\n";
        cout << "P - Promedio\n";
        cout << "X - Maximo\n";
        cout << "M - Minimo\n";
        cout << "S - Sumatoria\n";
        cout << "F - Finalizar\n";
        cout << "Opcion: ";
        cin >> op; op = toupper(op);

        if(S.empty()){
            cout << "El conjunto esta vacio.\n";
            continue;
        }

        switch(op){
            case 'P': {
                long double sum = accumulate(S.begin(), S.end(), 0.0L);
                long double prom = sum / (long double)S.size();
                cout << fixed << setprecision(2);
                cout << "Promedio: " << prom << "\n";
                break;
            }
            case 'X':
                cout << "Maximo: " << *S.rbegin() << "\n";
                break;
            case 'M':
                cout << "Minimo: " << *S.begin() << "\n";
                break;
            case 'S': {
                long long sum = accumulate(S.begin(), S.end(), 0LL);
                cout << "Sumatoria: " << sum << "\n";
                break;
            }
            case 'F':
                cout << "Fin.\n"; break;
            default:
                cout << "Opcion invalida.\n";
        }

    }while(op!='F');

    return 0;
}
