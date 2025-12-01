/*
Id.Programa: G5Ej27Generador.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: noviembre-2025
Comentario.:
    Generador de datos para G5Ej27.
    Crea archivos binarios de prueba:
      - CATEGORIA.DAT (sin orden)
      - USUARIOS.DAT  (ordenado por nroUsuario)
      - CONEXIONES.DAT (orden cronológico por dia)
    Formatos binarios usados:
      CATEGORIA: categoria (int), minutosSinCargo (int), importeAbono (double), importeMinAdic (double)
      USUARIO: nroUsuario (char[9]), apeNom (35), domicilio (50), categoria (int)
      CONEXION: dia (int), nroUsuario (char[9]), codigoDestino (char[17]), minutos (int)
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct CategoriaRec {
    int categoria;
    int minutosSinCargo;
    double importeAbono;
    double importeMinAdic;
};

struct UsuarioRec {
    char nroUsuario[9]; // 8 + '\0'
    char apeNom[35];
    char domicilio[50];
    int categoria;
};

struct ConexionRec {
    int dia;
    char nroUsuario[9];
    char codigoDestino[17];
    int minutos;
};

void setStr(char* dst, const char* src, size_t n){ strncpy(dst, src, n-1); dst[n-1] = '\0'; }

int main(){
    // CATEGORIA.DAT
    {
        ofstream f("CATEGORIA.DAT", ios::binary | ios::trunc);
        if(!f){ cerr<<"No puedo crear CATEGORIA.DAT\n"; return 1; }
        CategoriaRec c;
        c.categoria = 1; c.minutosSinCargo = 300; c.importeAbono = 500.0; c.importeMinAdic = 2.0; f.write((char*)&c, sizeof(c));
        c.categoria = 2; c.minutosSinCargo = 600; c.importeAbono = 800.0; c.importeMinAdic = 1.5; f.write((char*)&c, sizeof(c));
        c.categoria = 3; c.minutosSinCargo = 1000; c.importeAbono = 1200.0; c.importeMinAdic = 1.0; f.write((char*)&c, sizeof(c));
        f.close();
        cout<<"CATEGORIA.DAT generado.\n";
    }

    // USUARIOS.DAT (ordenado por nroUsuario)
    {
        ofstream f("USUARIOS.DAT", ios::binary | ios::trunc);
        if(!f){ cerr<<"No puedo crear USUARIOS.DAT\n"; return 1; }
        UsuarioRec u;
        setStr(u.nroUsuario, "00000001", sizeof(u.nroUsuario)); setStr(u.apeNom, "Gomez Juan", sizeof(u.apeNom)); setStr(u.domicilio, "Calle A 123", sizeof(u.domicilio)); u.categoria = 1; f.write((char*)&u, sizeof(u));
        setStr(u.nroUsuario, "00000002", sizeof(u.nroUsuario)); setStr(u.apeNom, "Perez Ana", sizeof(u.apeNom)); setStr(u.domicilio, "Av. B 45", sizeof(u.domicilio)); u.categoria = 2; f.write((char*)&u, sizeof(u));
        setStr(u.nroUsuario, "00000003", sizeof(u.nroUsuario)); setStr(u.apeNom, "Lopez Carlos", sizeof(u.apeNom)); setStr(u.domicilio, "Ruta 5 km 1", sizeof(u.domicilio)); u.categoria = 1; f.write((char*)&u, sizeof(u));
        setStr(u.nroUsuario, "00000004", sizeof(u.nroUsuario)); setStr(u.apeNom, "Martinez Lucia", sizeof(u.apeNom)); setStr(u.domicilio, "Pza Central 10", sizeof(u.domicilio)); u.categoria = 3; f.write((char*)&u, sizeof(u));
        f.close();
        cout<<"USUARIOS.DAT generado.\n";
    }

    // CONEXIONES.DAT (orden cronologico por dia)
    {
        ofstream f("CONEXIONES.DAT", ios::binary | ios::trunc);
        if(!f){ cerr<<"No puedo crear CONEXIONES.DAT\n"; return 1; }
        ConexionRec c;
        // dia1
        c.dia = 1; setStr(c.nroUsuario, "00000001", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_AAAAAAAA001", sizeof(c.codigoDestino)); c.minutos = 120; f.write((char*)&c, sizeof(c));
        c.dia = 1; setStr(c.nroUsuario, "00000002", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_BBBBBBBB002", sizeof(c.codigoDestino)); c.minutos = 400; f.write((char*)&c, sizeof(c)); // >360
        // dia2
        c.dia = 2; setStr(c.nroUsuario, "00000003", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_AAAAAAAA001", sizeof(c.codigoDestino)); c.minutos = 370; f.write((char*)&c, sizeof(c)); // >360
        c.dia = 2; setStr(c.nroUsuario, "00000001", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_CCCCCCCC003", sizeof(c.codigoDestino)); c.minutos = 45; f.write((char*)&c, sizeof(c));
        // day 10
        c.dia = 10; setStr(c.nroUsuario, "00000004", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_BBBBBBBB002", sizeof(c.codigoDestino)); c.minutos = 480; f.write((char*)&c, sizeof(c)); // >360
        c.dia = 10; setStr(c.nroUsuario, "00000002", sizeof(c.nroUsuario)); setStr(c.codigoDestino, "DEST_DDDDDDDD004", sizeof(c.codigoDestino)); c.minutos = 50; f.write((char*)&c, sizeof(c));
        f.close();
        cout<<"CONEXIONES.DAT generado.\n";
    }

    cout<<"Generador G5Ej27 finalizado.\n";
    return 0;
}