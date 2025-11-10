
/*
Id.Programa: G2Ej17Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Cuadrado magico de orden impar (metodo siames). Reglas del enunciado.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main(){
    int n;
    cout << "Ingrese n impar (>0): ";
    cin >> n;
    if (n<=0 || n%2==0){ cout << "n invalido.\n"; return 0; }

    vector<vector<int>> a(n, vector<int>(n, 0));
    int i=0, j=n/2; // (1) fila superior, col central
    for (int k=1; k<=n*n; ++k){
        a[i][j]=k;
        int ni = (i-1 + n) % n;
        int nj = (j+1) % n;
        if (a[ni][nj] != 0){
            i = (i+2) % n; // (5)
            j = (j-1 + n) % n;
        } else {
            i = ni; j = nj;
        }
    }

    int magic = n*(n*n+1)/2;
    cout << "Cuadrado magico (suma = " << magic << "):\n";
    for (int r=0;r<n;++r){
        for (int c=0;c<n;++c) cout << setw(4) << a[r][c];
        cout << "\n";
    }
    return 0;
}
