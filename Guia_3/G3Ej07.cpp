/*
Id.Programa: G3Ej07.cpp 
Autor......: Dev. Lucas Ferreyra
Fecha......: junio-2025 
Comentario.:
    Operaciones de conjuntos A y B por menú: Unión, Intersección,
    Diferencia (A - B), Diferencia Simétrica (A Δ B) y Complemento de A
    y de B respecto del universal U = {1..1000}.
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

const int U_MIN = 1;
const int U_MAX = 1000;

set<int> leerConjunto(const string& nombre){
    set<int> S;
    int n; 
    cout << "Cantidad de elementos de " << nombre << ": ";
    cin >> n;
    cout << "Ingrese " << n << " enteros en [" << U_MIN << "," << U_MAX << "]:\n";
    for(int i=0;i<n;++i){
        int x; cin >> x;
        if(x>=U_MIN && x<=U_MAX) S.insert(x);
        else cout << "  Valor fuera de rango, omitido.\n";
    }
    return S;
}

set<int> universal(){
    set<int> U;
    for(int i=U_MIN;i<=U_MAX;++i) U.insert(i);
    return U;
}

void mostrar(const set<int>& S, const string& nombre){
    cout << nombre << " = { ";
    for(auto it=S.begin(); it!=S.end(); ++it){
        cout << *it;
        if(next(it)!=S.end()) cout << ", ";
    }
    cout << " }\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> A = leerConjunto("A");
    set<int> B = leerConjunto("B");
    set<int> U = universal();

    char op;
    do{
        cout << "\n===== MENU =====\n";
        cout << "U - Union (A ∪ B)\n";
        cout << "I - Interseccion (A ∩ B)\n";
        cout << "D - Diferencia (A - B)\n";
        cout << "S - Diferencia Simetrica (A Δ B)\n";
        cout << "C - Complementos (U - A) y (U - B)\n";
        cout << "F - Finalizar\n";
        cout << "Opcion: ";
        cin >> op;
        op = toupper(op);

        set<int> R;
        switch(op){
            case 'U':
                set_union(A.begin(),A.end(),B.begin(),B.end(),inserter(R,R.begin()));
                mostrar(R,"A ∪ B");
                break;
            case 'I':
                set_intersection(A.begin(),A.end(),B.begin(),B.end(),inserter(R,R.begin()));
                mostrar(R,"A ∩ B");
                break;
            case 'D':
                set_difference(A.begin(),A.end(),B.begin(),B.end(),inserter(R,R.begin()));
                mostrar(R,"A - B");
                break;
            case 'S':
                set_symmetric_difference(A.begin(),A.end(),B.begin(),B.end(),inserter(R,R.begin()));
                mostrar(R,"A Δ B");
                break;
            case 'C': {
                set<int> CA, CB;
                set_difference(U.begin(),U.end(),A.begin(),A.end(),inserter(CA,CA.begin()));
                set_difference(U.begin(),U.end(),B.begin(),B.end(),inserter(CB,CB.begin()));
                mostrar(CA,"U - A");
                mostrar(CB,"U - B");
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
