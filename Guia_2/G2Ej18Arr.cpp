
/*
Id.Programa: G2Ej18Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Localidades (max 100) y rutas directas entre pares (no duplicadas).
             Carga en memoria y consultas varias con menu. Usa arreglos y busqueda binaria.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct Ruta { int a, b; short nro; short dist; }; // indices a,b de localidades ordenadas alfabeticamente

int main(){
    int L;
    cout << "Cantidad de localidades (1..100): ";
    cin >> L;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (L<1||L>100){ cout<<"Valor invalido\n"; return 0; }

    vector<string> loc(L);
    cout << "Ingrese nombres de localidades (una por linea):\n";
    for (int i=0;i<L;++i) getline(cin, loc[i]);

    // ordenar y mantener mapeo original a indice
    sort(loc.begin(), loc.end());
    auto idxOf = [&](const string& s)->int{
        auto it = lower_bound(loc.begin(), loc.end(), s);
        if (it==loc.end() || *it!=s) return -1;
        return (int)(it - loc.begin());
    };

    int R;
    cout << "Cantidad de rutas (pares directos): ";
    cin >> R;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<Ruta> rutas;
    rutas.reserve(R);

    cout << "Ingrese cada ruta: localA, localB, nroRuta, distancia\n";
    for (int i=0;i<R;++i){
        string A,B; short nro, dist;
        cout << "#" << (i+1) << ": ";
        getline(cin, A);
        getline(cin, B);
        cin >> nro >> dist;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int ia = idxOf(A), ib = idxOf(B);
        if (ia==-1||ib==-1){ cout<<"Localidad desconocida, ruta ignorada\n"; continue; }
        if (ia==ib){ cout<<"Ruta ignorada (misma localidad)\n"; continue; }
        if (ia>ib) swap(ia,ib);
        rutas.push_back({ia,ib,nro,dist});
    }

    // ordenar rutas por (a,b)
    sort(rutas.begin(), rutas.end(), [](const Ruta& x, const Ruta& y){
        if (x.a!=y.a) return x.a<y.a;
        return x.b<y.b;
    });

    auto buscarDirecta = [&](int ia, int ib)->int{
        if (ia>ib) swap(ia,ib);
        int lo=0, hi=(int)rutas.size()-1;
        while (lo<=hi){
            int mid=(lo+hi)/2;
            if (rutas[mid].a==ia && rutas[mid].b==ib) return mid;
            if (make_pair(rutas[mid].a,rutas[mid].b) < make_pair(ia,ib)) lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    };

    int op;
    do{
        cout << "\nMENU CONSULTAS\n";
        cout << "1) Dos localidades unidas directamente? mostrar distancia y nro de ruta\n";
        cout << "2) Vecinos directos de una localidad\n";
        cout << "3) Vecinos directos dentro de un radio de distancia\n";
        cout << "4) Nexo entre dos localidades (camino de longitud 2)\n";
        cout << "5) Vecino directo mas cercano\n";
        cout << "6) Preguntas adicionales (grado, rutas totales, promedio distancia, aisladas, vecino mas lejano)\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (op==1){
            string A,B; cout<<"Localidad A: "; getline(cin,A); cout<<"Localidad B: "; getline(cin,B);
            int ia=idxOf(A), ib=idxOf(B);
            if (ia==-1||ib==-1){ cout<<"Alguna localidad no existe\n"; continue; }
            int k=buscarDirecta(ia,ib);
            if (k==-1) cout<<"No estan unidas directamente\n";
            else cout<<"Si, ruta "<<rutas[k].nro<<" distancia "<<rutas[k].dist<<"\n";
        } else if (op==2){
            string A; cout<<"Localidad: "; getline(cin,A);
            int ia=idxOf(A); if (ia==-1){ cout<<"No existe\n"; continue; }
            cout<<"Vecinos directos de "<<A<<": ";
            bool alguno=false;
            for (auto &rt: rutas){
                if (rt.a==ia){ cout<<loc[rt.b]<<"("<<rt.dist<<") "; alguno=true; }
                else if (rt.b==ia){ cout<<loc[rt.a]<<"("<<rt.dist<<") "; alguno=true; }
            }
            if (!alguno) cout<<"(ninguno)";
            cout<<"\n";
        } else if (op==3){
            string A; int rad; cout<<"Localidad: "; getline(cin,A);
            cout<<"Radio de distancia: "; cin>>rad; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int ia=idxOf(A); if (ia==-1){ cout<<"No existe\n"; continue; }
            cout<<"Vecinos dentro de "<<rad<<": ";
            bool alguno=false;
            for (auto &rt: rutas){
                if (rt.a==ia && rt.dist<=rad){ cout<<loc[rt.b]<<" "; alguno=true; }
                else if (rt.b==ia && rt.dist<=rad){ cout<<loc[rt.a]<<" "; alguno=true; }
            }
            if (!alguno) cout<<"(ninguno)";
            cout<<"\n";
        } else if (op==4){
            string A,B; cout<<"Localidad A: "; getline(cin,A); cout<<"Localidad B: "; getline(cin,B);
            int ia=idxOf(A), ib=idxOf(B);
            if (ia==-1||ib==-1){ cout<<"No existe\n"; continue; }
            if (buscarDirecta(ia,ib)!=-1){ cout<<"Ya estan unidas directamente\n"; continue; }
            bool hallado=false;
            for (int nx=0; nx<L; ++nx){
                int k1 = buscarDirecta(ia,nx);
                int k2 = buscarDirecta(nx,ib);
                if (k1!=-1 && k2!=-1){
                    cout<<"Nexo: "<<loc[nx]<<"\n";
                    cout<<"  "<<loc[ia]<<" --("<<rutas[k1].nro<<","<<rutas[k1].dist<<")-> "<<loc[nx]<<"\n";
                    cout<<"  "<<loc[nx]<<" --("<<rutas[k2].nro<<","<<rutas[k2].dist<<")-> "<<loc[ib]<<"\n";
                    hallado=true;
                    break;
                }
            }
            if (!hallado) cout<<"No se encontro nexo de longitud 2\n";
        } else if (op==5){
            string A; cout<<"Localidad: "; getline(cin,A);
            int ia=idxOf(A); if (ia==-1){ cout<<"No existe\n"; continue; }
            int bestD=1e9, bestIdx=-1, bestRuta=-1;
            for (auto &rt: rutas){
                if (rt.a==ia && rt.dist<bestD){ bestD=rt.dist; bestIdx=rt.b; bestRuta=rt.nro; }
                else if (rt.b==ia && rt.dist<bestD){ bestD=rt.dist; bestIdx=rt.a; bestRuta=rt.nro; }
            }
            if (bestIdx==-1) cout<<"Sin vecinos\n";
            else cout<<"Mas cercano: "<<loc[bestIdx]<<", dist "<<bestD<<", ruta "<<bestRuta<<"\n";
        } else if (op==6){
            cout<<"1) Grado de una localidad\n";
            cout<<"2) Total de rutas\n";
            cout<<"3) Distancia promedio de rutas\n";
            cout<<"4) Localidades aisladas\n";
            cout<<"5) Vecino directo mas lejano de una localidad\n";
            int s; cin>>s; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (s==1){
                string A; cout<<"Localidad: "; getline(cin,A);
                int ia=idxOf(A); if (ia==-1){ cout<<"No existe\n"; continue; }
                int grado=0;
                for (auto& rt: rutas) if (rt.a==ia||rt.b==ia) grado++;
                cout<<"Grado de "<<A<<": "<<grado<<"\n";
            } else if (s==2){
                cout<<"Total de rutas: "<<rutas.size()<<"\n";
            } else if (s==3){
                if (rutas.empty()){ cout<<"No hay rutas\n"; continue; }
                long sum=0; for (auto& rt: rutas) sum+=rt.dist;
                cout<<"Distancia promedio: "<<(double)sum/rutas.size()<<"\n";
            } else if (s==4){
                cout<<"Localidades aisladas: ";
                bool alguno=false;
                for (int i=0;i<L;++i){
                    bool aisl=true;
                    for (auto& rt: rutas) if (rt.a==i||rt.b==i){ aisl=false; break; }
                    if (aisl){ cout<<loc[i]<<" "; alguno=true; }
                }
                if (!alguno) cout<<"(ninguna)";
                cout<<"\n";
            } else if (s==5){
                string A; cout<<"Localidad: "; getline(cin,A);
                int ia=idxOf(A); if (ia==-1){ cout<<"No existe\n"; continue; }
                int bestD=-1, bestIdx=-1, bestRuta=-1;
                for (auto &rt: rutas){
                    if (rt.a==ia && rt.dist>bestD){ bestD=rt.dist; bestIdx=rt.b; bestRuta=rt.nro; }
                    else if (rt.b==ia && rt.dist>bestD){ bestD=rt.dist; bestIdx=rt.a; bestRuta=rt.nro; }
                }
                if (bestIdx==-1) cout<<"Sin vecinos\n";
                else cout<<"Mas lejano: "<<loc[bestIdx]<<", dist "<<bestD<<", ruta "<<bestRuta<<"\n";
            }
        } else if (op!=0){
            cout<<"Opcion invalida\n";
        }
    } while (op!=0);

    return 0;
}
