/*
Id.Programa: G5Ej26.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Procesa VENTAS.DAT y CLIENTES.DAT para:
    1) Listar vendedores que en un mes superaron el promedio mensual de ventas,
       mostrando detalle de ventas ese mes (ordenado por dia asc, nroCliente asc).
    2) Listar clientes que compraron a 2 o mas vendedores, con total comprado,
       ordenado por apellidoNombre.
    Formatos binarios esperados:
      VENTA   : nroCliente[8], fecha(int MMDD), vendedor[7], importe(double)
      CLIENTE : nroCliente[8], domicilio[41], apellidoNombre[31], cuit[12]
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

struct VentaRec {
    char nroCliente[8];
    int fecha; // MMDD
    char vendedor[7];
    double importe;
};

struct ClienteRec {
    char nroCliente[8];
    char domicilio[41];
    char apellidoNombre[31];
    char cuit[12];
};

int mesFromFecha(int f){ return f/100; }

void loadClientes(const string &fname, unordered_map<string, ClienteRec> &mapCli){
    ifstream f(fname, ios::binary);
    if(!f) return;
    ClienteRec c;
    while(f.read(reinterpret_cast<char*>(&c), sizeof(c))){
        mapCli[string(c.nroCliente)] = c;
    }
    f.close();
}

int main(){
    cout<<fixed<<setprecision(2);
    // 1) Primera pasada: calcular totales y conteos por mes
    double totalMes[13]; long cntMes[13];
    for(int i=0;i<13;i++){ totalMes[i]=0.0; cntMes[i]=0; }

    ifstream fVentas("VENTAS.DAT", ios::binary);
    if(!fVentas){ cerr<<"No puedo abrir VENTAS.DAT\n"; return 1; }
    VentaRec vr;
    while(fVentas.read(reinterpret_cast<char*>(&vr), sizeof(vr))){
        int m = mesFromFecha(vr.fecha);
        if(m>=1 && m<=12){ totalMes[m]+=vr.importe; cntMes[m]++; }
    }
    fVentas.close();

    double promMes[13];
    for(int m=1;m<=12;m++) promMes[m] = (cntMes[m]>0) ? (totalMes[m]/cntMes[m]) : 0.0;

    // cargar clientes en memoria para lookup
    unordered_map<string, ClienteRec> clientes;
    loadClientes("CLIENTES.DAT", clientes);

    // 2) Procesar mes por mes: agrupar por vendedor dentro del mes
    for(int mes=1; mes<=12; ++mes){
        // read file and collect sales of this month
        vector<VentaRec> monthSales;
        ifstream f2("VENTAS.DAT", ios::binary);
        if(!f2) break;
        while(f2.read(reinterpret_cast<char*>(&vr), sizeof(vr))){ if(mesFromFecha(vr.fecha)==mes) monthSales.push_back(vr); }
        f2.close();

        if(monthSales.empty()) continue;

        // group by vendor
        map<string, vector<VentaRec>> byVendor;
        map<string, double> totalByVendor;
        for(auto &s : monthSales){ string vend(s.vendedor); byVendor[vend].push_back(s); totalByVendor[vend]+=s.importe; }

        // for each vendor check if total > promMes
        for(auto &par : totalByVendor){
            string vend = par.first; double totalVend = par.second;
            if(totalVend > promMes[mes]){
                cout<<"\nVENDEDOR : "<<vend<<" MES : "<<setw(2)<<setfill('0')<<mes<<setfill(' ')<<"\n";
                // sort vendor sales by day then show
                auto vec = byVendor[vend];
                sort(vec.begin(), vec.end(), [](const VentaRec &a, const VentaRec &b){ if(a.fecha!=b.fecha) return a.fecha<b.fecha; return strcmp(a.nroCliente,b.nroCliente)<0; });
                for(auto &sale : vec){ string key(sale.nroCliente); string name = (clientes.count(key))? string(clientes[key].apellidoNombre) : string("(Nombre desconocido)");
                    int dia = sale.fecha % 100;
                    cout<<setw(3)<<dia<<" "<<left<<setw(30)<<name<<right<<" "<<setw(10)<<sale.importe<<"\n";
                }
                cout<<"IMPORTE TOTAL : "<<totalVend<<"\n";
            }
        }
    }

    // 3) Parte 2: clientes que compraron a 2 o mas vendedores
    // map cliente -> set vendedores + total importe
    unordered_map<string, set<string>> clientesVendedores;
    unordered_map<string, double> clientesTotal;

    ifstream f3("VENTAS.DAT", ios::binary);
    if(f3){
        while(f3.read(reinterpret_cast<char*>(&vr), sizeof(vr))){ string cli(vr.nroCliente); string vend(vr.vendedor); clientesVendedores[cli].insert(vend); clientesTotal[cli]+=vr.importe; }
        f3.close();
    }

    cout<<"\nCLIENTES QUE COMPRARON A 2 O MAS VENDEDORES:\n";
    // collect and print
    vector<pair<string,double>> resultado;
    for(auto &par : clientesVendedores){ if(par.second.size()>=2){ resultado.push_back({par.first, clientesTotal[par.first]}); } }
    // sort by apellidoNombre (lookup in clientes)
    sort(resultado.begin(), resultado.end(), [&](const pair<string,double> &a, const pair<string,double> &b){ string na = (clientes.count(a.first)?string(clientes[a.first].apellidoNombre):a.first); string nb = (clientes.count(b.first)?string(clientes[b.first].apellidoNombre):b.first); return na < nb; });

    for(auto &r : resultado){ string key = r.first; string name = (clientes.count(key))? string(clientes[key].apellidoNombre) : string(key); cout<<left<<setw(30)<<name<<right<<" "<<setw(12)<<r.second<<"\n"; }

    cout<<"\nProceso finalizado.\n";
    return 0;
}
