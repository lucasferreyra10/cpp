/*
Id.Programa: G5Ej27.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Programa que genera facturas por usuario y listado de conexiones >360 minutos
    - Lee CATEGORIA.DAT, USUARIOS.DAT, CONEXIONES.DAT
    - Imprime factura por usuario (ordenado por nroUsuario, usa datos en USUARIOS.DAT)
    - Imprime conexiones individuales con minutos>360 ordenadas por codigoDestino y dia
    Restricciones: no usar disco auxiliar.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;

struct CategoriaRec { int categoria; int minutosSinCargo; double importeAbono; double importeMinAdic; };
struct UsuarioRec { char nroUsuario[9]; char apeNom[35]; char domicilio[50]; int categoria; };
struct ConexionRec { int dia; char nroUsuario[9]; char codigoDestino[17]; int minutos; };

int main(){
    cout<<fixed<<setprecision(2);
    // 1) cargar categorías en map<int,CategoriaRec>
    unordered_map<int, CategoriaRec> categorias;
    {
        ifstream f("CATEGORIA.DAT", ios::binary);
        if(!f){ cerr<<"No se pudo abrir CATEGORIA.DAT\n"; return 1; }
        CategoriaRec c;
        while(f.read(reinterpret_cast<char*>(&c), sizeof(c))){ categorias[c.categoria]=c; }
        f.close();
    }

    // 2) cargar usuarios (ordenado) en map<string,UsuarioRec>
    map<string, UsuarioRec> usuarios; // ordered by key
    {
        ifstream f("USUARIOS.DAT", ios::binary);
        if(!f){ cerr<<"No se pudo abrir USUARIOS.DAT\n"; return 1; }
        UsuarioRec u;
        while(f.read(reinterpret_cast<char*>(&u), sizeof(u))){ usuarios[string(u.nroUsuario)] = u; }
        f.close();
    }

    // 3) recorrer CONEXIONES: acumular minutos por usuario; y recolectar conexiones >360
    unordered_map<string, long> minutosPorUsuario; // key nroUsuario -> total minutos
    struct ConnHuge { string codigoDestino; int dia; string nroUsuario; int minutos; };
    vector<ConnHuge> conexionesLargas; conexionesLargas.reserve(1000);

    {
        ifstream f("CONEXIONES.DAT", ios::binary);
        if(!f){ cerr<<"No se pudo abrir CONEXIONES.DAT\n"; return 1; }
        ConexionRec c;
        while(f.read(reinterpret_cast<char*>(&c), sizeof(c))){
            string key = string(c.nroUsuario);
            minutosPorUsuario[key] += c.minutos;
            if(c.minutos > 360){
                ConnHuge ch; ch.codigoDestino = string(c.codigoDestino); ch.dia = c.dia; ch.nroUsuario = key; ch.minutos = c.minutos;
                conexionesLargas.push_back(move(ch));
            }
        }
        f.close();
    }

    // 4) Imprimir factura de cada usuario ordenado por nroUsuario (usuarios map already ordered)
    cout<<"\n===== FACTURAS POR USUARIO =====\n";
    for(auto &par : usuarios){
        string nro = par.first; UsuarioRec u = par.second;
        long totalMin = minutosPorUsuario.count(nro) ? minutosPorUsuario[nro] : 0;
        int cat = u.categoria;
        CategoriaRec catR;
        if(categorias.find(cat) != categorias.end()) catR = categorias[cat]; else { catR.categoria = cat; catR.minutosSinCargo = 0; catR.importeAbono = 0; catR.importeMinAdic = 0.0; }
        long incluidos = catR.minutosSinCargo;
        long adicionales = (totalMin > incluidos) ? (totalMin - incluidos) : 0;
        double importeAdic = adicionales * catR.importeMinAdic;
        double importeAbono = catR.importeAbono;
        double total = importeAbono + importeAdic;

        cout<<"USUARIO NRO.: "<<nro<<" APELLIDO Y NOMBRE : "<<u.apeNom<<"\n";
        cout<<"DOMICILIO : "<<u.domicilio<<"\n";
        cout<<" ABONO ("<<incluidos<<" minutos sin cargo) "<<setw(8)<<importeAbono<<"\n";
        cout<<" ADICIONAL "<<adicionales<<" x imp.adic. "<<" + "<<setw(8)<<importeAdic<<"\n";
        cout<<"TOTAL "<<setw(12)<<total<<"\n";
        cout<<"----------------------------------------\n";
    }

    // 5) Imprimir conexiones largas (>360) ordenadas por codigoDestino y dia
    sort(conexionesLargas.begin(), conexionesLargas.end(), [](const ConnHuge &a, const ConnHuge &b){ if(a.codigoDestino!=b.codigoDestino) return a.codigoDestino < b.codigoDestino; if(a.dia!=b.dia) return a.dia < b.dia; return a.nroUsuario < b.nroUsuario; });

    cout<<"\n===== CONEXIONES > 360 MINUTOS (ordenadas por destino y dia) =====\n";
    string currentDest = "";
    for(auto &c : conexionesLargas){
        if(c.codigoDestino != currentDest){ currentDest = c.codigoDestino; cout<<"\nCODIGO DE DESTINO: "<<currentDest<<"\n"; cout<<left<<setw(4)<<"DIA"<<left<<setw(35)<<"APELLIDO Y NOMBRE"<<left<<setw(12)<<"USUARIO"<<left<<setw(8)<<"MINUTOS"<<"\n"; }
        string name = "(Desconocido)";
        if(usuarios.find(c.nroUsuario) != usuarios.end()) name = usuarios[c.nroUsuario].apeNom;
        cout<<left<<setw(4)<<c.dia<<left<<setw(35)<<name<<left<<setw(12)<<c.nroUsuario<<left<<setw(8)<<c.minutos<<"\n";
    }

    cout<<"\nProceso finalizado.\n";
    return 0;
}
